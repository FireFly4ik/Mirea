import sys
import secrets
import math
import json
import base64
import re
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QTabWidget, QPushButton,
    QTextEdit, QLabel, QLineEdit, QFileDialog, QComboBox, QGroupBox, QMessageBox, QSplitter,
    QSpinBox, QMenuBar, QSlider, QProgressBar, QScrollArea, QCheckBox, QDialog
)
from PySide6.QtCore import Qt, QTimer
from PySide6.QtGui import QFont, QPalette, QColor, QAction
from cryptography.hazmat.primitives.asymmetric import rsa as crypto_rsa, padding as crypto_padding
from cryptography.hazmat.primitives import hashes, serialization

# -------------------- Константы --------------------
METHOD_MAX_BITS = {"miller-rabin": 2048, "trial": 32, "sieve": 20, "genpr": 10000}


# -------------------- Утилиты --------------------
def extended_gcd(a, b):
    if a == 0:
        return b, 0, 1
    d, x1, y1 = extended_gcd(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return d, x, y


def mod_inverse(a, m):
    d, x, _ = extended_gcd(a, m)
    if d != 1:
        raise ValueError("Нет обратного элемента для данного e по модулю φ(N).")
    return x % m


def parse_numbers(s: str):
    s = re.sub(r'[\[\](){},;\s]+', ' ', s.strip())
    out = []
    for token in s.split():
        if re.fullmatch(r'[+]?\d+', token):
            out.append(int(token))
    return out


def encode_text_to_blocks(text: str, n: int):
    data = text.encode('utf-8')
    block_bytes = max(1, (n.bit_length() - 1) // 8)

    blocks = []
    plain_lengths = []

    for i in range(0, len(data), block_bytes):
        chunk = data[i:i + block_bytes]
        blocks.append(int.from_bytes(chunk, 'big'))
        plain_lengths.append(len(chunk))
    return blocks, block_bytes, plain_lengths, len(data)


def decode_blocks_to_text_precise(blocks, block_bytes, plain_lengths=None, total_plain_bytes=None):
    raw = bytearray()
    if plain_lengths and len(plain_lengths) == len(blocks):
        for b, plen in zip(blocks, plain_lengths):
            try:
                full = b.to_bytes(block_bytes, 'big')
                raw.extend(full[-plen:])
            except OverflowError:
                actual_len = (b.bit_length() + 7) // 8
                full = b.to_bytes(actual_len, 'big')
                raw.extend(full)
    else:
        for b in blocks:
            try:
                chunk = b.to_bytes(block_bytes, 'big').lstrip(b'\x00')
            except OverflowError:
                actual_len = (b.bit_length() + 7) // 8
                chunk = b.to_bytes(actual_len, 'big').lstrip(b'\x00')
            raw.extend(chunk)

    if total_plain_bytes is not None and len(raw) > total_plain_bytes:
        raw = raw[:total_plain_bytes]
    try:
        return raw.decode('utf-8')
    except UnicodeDecodeError:
        return raw.decode('utf-8', 'replace')


def decode_blocks_to_text(blocks, block_bytes):
    raw = bytearray()
    for b in blocks:
        try:
            chunk = b.to_bytes(block_bytes, 'big').lstrip(b'\x00')
        except OverflowError:
            actual_len = (b.bit_length() + 7) // 8
            chunk = b.to_bytes(actual_len, 'big').lstrip(b'\x00')
        raw.extend(chunk)
    try:
        return raw.decode('utf-8')
    except UnicodeDecodeError:
        return raw.decode('utf-8', 'replace')


def blocks_to_compact_hex(blocks, N):
    cipher_block_bytes = (N.bit_length() + 7) // 8
    return ''.join(b.to_bytes(cipher_block_bytes, 'big').hex() for b in blocks)


def compact_hex_to_blocks(hex_str, N):
    hex_str = hex_str.strip()
    cipher_block_bytes = (N.bit_length() + 7) // 8
    one_len = cipher_block_bytes * 2
    if len(hex_str) % one_len != 0:
        raise ValueError("Длина компактной HEX-строки не кратна размеру блока.")
    blocks = []
    for i in range(0, len(hex_str), one_len):
        chunk_hex = hex_str[i:i + one_len]
        if not re.fullmatch(r'[0-9a-fA-F]+', chunk_hex):
            raise ValueError("Строка содержит не HEX символы.")
        val = int.from_bytes(bytes.fromhex(chunk_hex), 'big')
        if val >= N:
            raise ValueError("Блок >= N (некорректные данные).")
        blocks.append(val)
    return blocks


def byte_to_char_repr(b: int) -> str:
    return chr(b) if 32 <= b <= 126 else '.'


def bytes_to_printable_utf8(block: bytes) -> str:
    return block.decode('utf-8', errors='replace')


# -------------------- Генераторы --------------------
class LCG:
    def __init__(self, seed, a=1664525, b=1013904223, m=2 ** 32):
        self.state = seed % m
        self.a = a
        self.b = b
        self.m = m

    def next(self):
        self.state = (self.a * self.state + self.b) % self.m
        return self.state

    def get_formula_info(self):
        return f"Y_i = ({self.a} • {self.state} + {self.b}) mod {self.m}"

    def get_params_description(self):
        return (f"Пояснение: a={self.a} (множитель), b={self.b} (приращение), "
                f"m={self.m} (модуль), Y_i-1={self.state} (пред. число)")


class Multiplicative:
    def __init__(self, seed, a=16807, m=2 ** 31 - 1):
        self.state = seed % m
        self.a = a
        self.m = m

    def next(self):
        self.state = (self.a * self.state) % self.m
        return self.state

    def get_formula_info(self):
        return f"Y_i = ({self.a} • {self.state}) mod {self.m}"

    def get_params_description(self):
        return (f"Пояснение: a={self.a} (множитель), m={self.m} (модуль), "
                f"Y_i-1={self.state} (пред. число). Приращение b=0.")


class Additive:
    def __init__(self, seed1, seed2=None, m=2 ** 32):
        self.x = seed1 % m
        self.y = (seed2 or (seed1 * 1103515245 + 12345)) % m
        self.m = m

    def next(self):
        z = (self.x + self.y) % self.m
        self.x, self.y = self.y, z
        return z

    def get_formula_info(self):
        return f"Y_i = ({self.x} + {self.y}) mod {self.m}"

    def get_params_description(self):
        return (f"Пояснение: m={self.m} (модуль), Y_i-1={self.x} (пред. число), "
                f"Y_i-2={self.y} (пред-пред. число). Множителя нет.")


# -------------------- Простые числа --------------------
_SMALL_PRIMES = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]
for n in range(101, 1000, 2):
    if all(n % p for p in _SMALL_PRIMES if p * p <= n):
        _SMALL_PRIMES.append(n)


def is_prime_deterministic(n):
    if n < 2: return False
    for p in _SMALL_PRIMES:
        if n % p == 0: return n == p
    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1
    for a in [2, 325, 9375, 28178, 450775, 9780504, 1795265022]:
        if a % n == 0: continue
        x = pow(a, d, n)
        if x == 1 or x == n - 1: continue
        for _ in range(s - 1):
            x = (x * x) % n
            if x == n - 1: break
        else:
            return False
    return True


def is_prime_miller_rabin(n, k=10):
    if n < 2: return False
    for p in _SMALL_PRIMES[:15]:
        if n % p == 0: return n == p
    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1
    for _ in range(k):
        a = secrets.randbelow(n - 3) + 2
        x = pow(a, d, n)
        if x == 1 or x == n - 1: continue
        for __ in range(s - 1):
            x = (x * x) % n
            if x == n - 1: break
        else:
            return False
    return True


def genpr_algorithm(m, k):
    if m < 3: m = 3
    if m % 2 == 0: m += 1
    n = m + 2 * k - 2
    A = [1] * k
    d = 3
    while True:
        if d * d > n:
            break
        inv_2 = (d + 1) // 2
        start_j = ((-m * inv_2) % d)
        if (m + 2 * start_j) == d:
            start_j += d
        current_j = start_j
        while current_j < k:
            A[current_j] = 0
            current_j += d
        if d % 6 == 1:
            d += 4
        else:
            d += 2
    primes = []
    for i in range(k):
        if A[i] == 1:
            primes.append(m + 2 * i)
    return [p for p in primes if is_prime_deterministic(p)]


def generate_large_prime(bits=None, method='miller-rabin', genpr_params=None):
    if method == 'genpr':
        if not genpr_params:
            m_val = 1 << (bits - 1) if bits else 1001
            k_val = 1000
        else:
            m_val, k_val = genpr_params
        primes = genpr_algorithm(m_val, k_val)
        if primes:
            return secrets.choice(primes)
        else:
            raise ValueError(f"GENPR: нет простых чисел в диапазоне [{m_val}, {m_val + 2 * k_val - 2}]")

    if bits < 2: raise ValueError("Битность ≥ 2")
    max_allowed = METHOD_MAX_BITS.get(method, 1024)
    if bits > max_allowed:
        raise ValueError(f"Метод '{method}' поддерживает ≤ {max_allowed} бит.")

    while True:
        candidate = secrets.randbits(bits)
        candidate |= (1 << (bits - 1)) | 1
        if any(candidate % p == 0 and candidate != p for p in _SMALL_PRIMES):
            continue
        if method == 'trial':
            if candidate < 2: continue
            limit = int(math.isqrt(candidate))
            f = 3
            while f <= limit and candidate % f: f += 2
            if f > limit: return candidate
        elif method == 'sieve':
            limit = (1 << bits) - 1
            sieve = [True] * (limit + 1);
            sieve[0:2] = [False, False]
            for i in range(2, int(limit ** 0.5) + 1):
                if sieve[i]: sieve[i * i::i] = [False] * ((limit - i * i) // i + 1)
            primes = [i for i, fl in enumerate(sieve) if fl]
            if primes: return secrets.choice(primes)
        elif method == 'miller-rabin':
            if is_prime_miller_rabin(candidate, k=10): return candidate


def mod_exp(base, exp, mod):
    return pow(base, exp, mod)


# -------------------- Окно просмотра Гаммы --------------------
class GammaDisplayWindow(QDialog):
    def __init__(self, gamma_bytes, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Просмотр Гаммы")
        self.resize(600, 500)
        layout = QVBoxLayout(self)

        layout.addWidget(QLabel("<b>16-ричный вид (HEX):</b>"))
        self.hex_view = QTextEdit()
        self.hex_view.setReadOnly(True)
        hex_str = gamma_bytes.hex(" ").upper()
        self.hex_view.setPlainText(hex_str)
        layout.addWidget(self.hex_view)

        layout.addWidget(QLabel("<b>Десятичный вид (0-255):</b>"))
        self.dec_view = QTextEdit()
        self.dec_view.setReadOnly(True)
        dec_str = ", ".join(str(b) for b in gamma_bytes)
        self.dec_view.setPlainText(dec_str)
        layout.addWidget(self.dec_view)

        btn_close = QPushButton("Закрыть")
        btn_close.clicked.connect(self.close)
        layout.addWidget(btn_close)


# -------------------- GammaTab --------------------
class GammaTab(QWidget):
    MAX_LOG_BLOCKS = 1000

    def __init__(self):
        super().__init__()
        main_layout = QHBoxLayout(self)

        # Левая панель управления
        left_panel = QWidget()
        left_panel.setMaximumWidth(400)
        left_layout = QVBoxLayout(left_panel)

        # Группа параметров генератора
        params_group = QGroupBox("Параметры генератора")
        params_layout = QVBoxLayout(params_group)

        seed_layout = QHBoxLayout()
        seed_layout.addWidget(QLabel("Seed:"))
        self.seed_input = QLineEdit("12345")
        seed_layout.addWidget(self.seed_input)
        params_layout.addLayout(seed_layout)

        type_layout = QHBoxLayout()
        type_layout.addWidget(QLabel("Тип:"))
        self.gen_combo = QComboBox()
        self.gen_combo.addItems(["LCG (Линейный)", "Мультипликативный", "Аддитивный"])
        self.gen_combo.currentIndexChanged.connect(self.on_gen_changed)
        type_layout.addWidget(self.gen_combo)
        params_layout.addLayout(type_layout)

        coeffs_layout = QHBoxLayout()
        self.a_label = QLabel("a:")
        self.a_input = QLineEdit("1664525")
        self.b_label = QLabel("b:")
        self.b_input = QLineEdit("1013904223")
        self.m_label = QLabel("m:")
        self.m_input = QLineEdit("4294967296")
        coeffs_layout.addWidget(self.a_label)
        coeffs_layout.addWidget(self.a_input)
        coeffs_layout.addWidget(self.b_label)
        coeffs_layout.addWidget(self.b_input)
        coeffs_layout.addWidget(self.m_label)
        coeffs_layout.addWidget(self.m_input)
        params_layout.addLayout(coeffs_layout)

        key_btns = QHBoxLayout()
        self.btn_save_key = QPushButton("Сохранить ключи")
        self.btn_save_key.clicked.connect(self.save_key_file)
        self.btn_load_key = QPushButton("Загрузить ключи")
        self.btn_load_key.clicked.connect(self.load_key_file)
        key_btns.addWidget(self.btn_save_key)
        key_btns.addWidget(self.btn_load_key)
        params_layout.addLayout(key_btns)

        left_layout.addWidget(params_group)

        # Группа управления
        control_group = QGroupBox("Управление")
        control_layout = QVBoxLayout(control_group)

        file_btns = QHBoxLayout()
        self.btn_load = QPushButton("Загрузить файл")
        self.btn_load.clicked.connect(self.load_file)
        file_btns.addWidget(self.btn_load)
        control_layout.addLayout(file_btns)

        action_btns = QHBoxLayout()
        self.btn_encrypt = QPushButton("Шифровать")
        self.btn_encrypt.clicked.connect(self.encrypt)
        self.btn_decrypt = QPushButton("Дешифровать")
        self.btn_decrypt.clicked.connect(self.decrypt)
        action_btns.addWidget(self.btn_encrypt)
        action_btns.addWidget(self.btn_decrypt)
        control_layout.addLayout(action_btns)

        gamma_btn_layout = QHBoxLayout()
        self.btn_show_gamma = QPushButton("Показать гамму")
        self.btn_show_gamma.clicked.connect(self.show_gamma_window)
        self.btn_show_gamma.setEnabled(False)
        gamma_btn_layout.addWidget(self.btn_show_gamma)
        control_layout.addLayout(gamma_btn_layout)

        left_layout.addWidget(control_group)

        # Группа лога
        log_group = QGroupBox("Лог операций")
        log_layout = QVBoxLayout(log_group)
        self.log_text = QTextEdit()
        self.log_text.setReadOnly(True)
        self.log_text.setMaximumHeight(200)
        log_layout.addWidget(self.log_text)

        log_btns = QHBoxLayout()
        self.btn_clear_log = QPushButton("Очистить")
        self.btn_clear_log.clicked.connect(self.log_text.clear)
        self.btn_save_log = QPushButton("Сохранить лог")
        self.btn_save_log.clicked.connect(self.save_log)
        log_btns.addWidget(self.btn_clear_log)
        log_btns.addWidget(self.btn_save_log)
        log_layout.addLayout(log_btns)

        left_layout.addWidget(log_group)
        left_layout.addStretch()

        # Правая панель данных
        right_panel = QWidget()
        right_layout = QVBoxLayout(right_panel)

        # Группа ввода
        input_group = QGroupBox("Входные данные")
        input_layout = QVBoxLayout(input_group)
        self.input_text = QTextEdit()
        self.input_text.setPlaceholderText("Введите текст...")
        input_layout.addWidget(self.input_text)
        right_layout.addWidget(input_group)

        # Группа вывода
        output_group = QGroupBox("Результат")
        output_layout = QVBoxLayout(output_group)
        self.output_text = QTextEdit()
        self.output_text.setReadOnly(True)
        output_layout.addWidget(self.output_text)

        save_btn_layout = QHBoxLayout()
        self.btn_save = QPushButton("Сохранить результат")
        self.btn_save.clicked.connect(self.save_result)
        save_btn_layout.addWidget(self.btn_save)
        output_layout.addLayout(save_btn_layout)

        right_layout.addWidget(output_group)

        # Добавляем панели в главный layout
        main_layout.addWidget(left_panel)
        main_layout.addWidget(right_panel)

        self.last_gamma = b""

        self.on_gen_changed(0)

    def on_gen_changed(self, index):
        if index == 0:  # LCG
            self.a_input.setEnabled(True)
            self.a_label.setText("a:")
            self.b_input.setEnabled(True)
            self.b_input.setText("1013904223")
            self.m_input.setEnabled(True)
        elif index == 1:  # Мультипликативный
            self.a_input.setEnabled(True)
            self.a_label.setText("a:")
            self.b_input.setEnabled(False)
            self.b_input.setText("0")
            self.m_input.setEnabled(True)
        elif index == 2:  # Аддитивный
            self.a_input.setEnabled(False)
            self.a_label.setText("a (N/A):")
            self.b_input.setEnabled(False)
            self.b_input.setText("N/A")
            self.m_input.setEnabled(True)

    def get_generator(self):
        try:
            seed = int(self.seed_input.text())
            m_val = int(self.m_input.text())
            idx = self.gen_combo.currentIndex()
            if idx == 0:
                a_val = int(self.a_input.text())
                b_val = int(self.b_input.text())
                return LCG(seed, a=a_val, b=b_val, m=m_val)
            elif idx == 1:
                a_val = int(self.a_input.text())
                return Multiplicative(seed, a=a_val, m=m_val)
            else:
                return Additive(seed, m=m_val)
        except ValueError:
            QMessageBox.warning(self, "Ошибка", "Проверьте, что a, b, m и seed - целые числа.")
            return LCG(12345)

    def load_file(self):
        path, _ = QFileDialog.getOpenFileName(self, "Открыть", "", "TXT (*.txt);;All (*)")
        if path:
            with open(path, 'r', encoding='utf-8') as f:
                self.input_text.setPlainText(f.read())

    def generate_seed(self):
        try:
            bits = 128  # Fixed bits for seed generation
            self.seed_input.setText(str(secrets.randbits(bits)))
        except:
            pass

    def save_key_file(self):
        try:
            seed = self.seed_input.text()
            gen_idx = self.gen_combo.currentIndex()
            a = self.a_input.text()
            b = self.b_input.text()
            m = self.m_input.text()
            content = (f"seed={seed}\ntype={gen_idx}\na={a}\nb={b}\nm={m}\n")
            path, _ = QFileDialog.getSaveFileName(self, "Сохранить ключ", "", "TXT (*.txt)")
            if path:
                with open(path, 'w', encoding='utf-8') as f:
                    f.write(content)
                QMessageBox.information(self, "OK", "Сохранено")
        except Exception as e:
            QMessageBox.critical(self, "ERR", str(e))

    def load_key_file(self):
        path, _ = QFileDialog.getOpenFileName(self, "Загрузить ключ", "", "TXT (*.txt)")
        if not path: return
        try:
            with open(path, 'r', encoding='utf-8') as f:
                lines = f.readlines()
            for line in lines:
                if '=' not in line: continue
                k, v = line.strip().split('=', 1)
                if k == 'seed':
                    self.seed_input.setText(v)
                elif k == 'type':
                    self.gen_combo.setCurrentIndex(int(v))
                elif k == 'a':
                    self.a_input.setText(v)
                elif k == 'b':
                    self.b_input.setText(v)
                elif k == 'm':
                    self.m_input.setText(v)
            self.on_gen_changed(self.gen_combo.currentIndex())
        except Exception as e:
            QMessageBox.critical(self, "ERR", str(e))

    def process_gamma(self, data_bytes, gen):
        block_size = 8
        for i in range(0, len(data_bytes), block_size):
            block = data_bytes[i:i + block_size]
            formula_str = gen.get_formula_info()
            params_desc = gen.get_params_description()

            raw_val = gen.next()
            full_info = f"{formula_str} = {raw_val}\n    {params_desc}"

            gamma = bytearray()
            gamma.append(raw_val & 0xFF)
            for _ in range(len(block) - 1):
                gamma.append(gen.next() & 0xFF)

            out_block = bytes(b ^ g for b, g in zip(block, gamma))
            yield i // block_size, block, gamma, out_block, full_info

    def encrypt(self):
        text = self.input_text.toPlainText()
        if not text: return
        gen = self.get_generator()
        data = text.encode('utf-8')
        out = bytearray()
        full_log = []
        self.last_gamma = bytearray()

        for idx, inp, gam, res, info in self.process_gamma(data, gen):
            out.extend(res)
            self.last_gamma.extend(gam)

            inp_chars = bytes_to_printable_utf8(inp)
            res_chars = bytes_to_printable_utf8(res)

            log_entry = (
                f"Block {idx}:\n"
                f"  Info:  {info}\n"
                f"  Text:  '{inp_chars}'\n"
                f"  InHex: {inp.hex()}\n"
                f"  Gamma: {gam.hex()}\n"
                f"  Out:   {res.hex()} (Encrypted: '{res_chars}')"
            )
            full_log.append(log_entry)

        self.output_text.setPlainText(out.hex())
        self.log_text.setPlainText('\n---------------------------------\n'.join(full_log))
        self.btn_show_gamma.setEnabled(True)

    def decrypt(self):
        src = self.input_text.toPlainText().strip()
        if not src: return
        try:
            data = bytes.fromhex(src)
        except:
            data = src.encode('utf-8')
        gen = self.get_generator()
        out = bytearray()
        full_log = []
        self.last_gamma = bytearray()

        for idx, inp, gam, res, info in self.process_gamma(data, gen):
            out.extend(res)
            self.last_gamma.extend(gam)

            inp_chars = bytes_to_printable_utf8(inp)
            res_chars = bytes_to_printable_utf8(res)

            log_entry = (
                f"Block {idx}:\n"
                f"  Info:  {info}\n"
                f"  InHex: {inp.hex()}\n"
                f"  Gamma: {gam.hex()}\n"
                f"  Out:   {res.hex()}\n"
                f"  Text:  '{res_chars}'"
            )
            full_log.append(log_entry)

        try:
            res_txt = out.decode('utf-8')
        except:
            res_txt = out.decode('utf-8', 'replace')

        self.output_text.setPlainText(res_txt)
        self.log_text.setPlainText('\n---------------------------------\n'.join(full_log))
        self.btn_show_gamma.setEnabled(True)

    def show_gamma_window(self):
        if not self.last_gamma:
            QMessageBox.information(self, "Информация", "Сначала выполните шифрование или дешифрование.")
            return
        dialog = GammaDisplayWindow(self.last_gamma, self)
        dialog.exec()

    def save_result(self):
        txt = self.output_text.toPlainText()
        if not txt:
            QMessageBox.warning(self, "", "Пусто")
            return
        path, _ = QFileDialog.getSaveFileName(self, "Сохранить результат", "", "Text Files (*.txt)")
        if path:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(txt)
            QMessageBox.information(self, "OK", "Сохранено")

    def save_log(self):
        txt = self.log_text.toPlainText()
        if not txt:
            QMessageBox.warning(self, "Пусто", "Лог пуст, нечего сохранять.")
            return
        path, _ = QFileDialog.getSaveFileName(self, "Сохранить лог", "", "Text Files (*.txt)")
        if path:
            try:
                with open(path, 'w', encoding='utf-8') as f:
                    f.write(txt)
                QMessageBox.information(self, "OK", "Лог сохранен")
            except Exception as e:
                QMessageBox.critical(self, "Ошибка", str(e))


# -------------------- ModArithmeticTab --------------------
class ModArithmeticTab(QWidget):
    def __init__(self):
        super().__init__()
        main_layout = QHBoxLayout(self)

        # Левая панель управления
        left_panel = QWidget()
        left_panel.setMaximumWidth(400)
        left_layout = QVBoxLayout(left_panel)

        # Группа генерации простых чисел
        gen_group = QGroupBox("Генерация простых чисел")
        gen_layout = QVBoxLayout(gen_group)

        method_layout = QHBoxLayout()
        method_layout.addWidget(QLabel("Метод:"))
        self.method_combo = QComboBox()
        self.method_combo.addItems(["Миллер–Рабин", "Перебор", "Решето Эратосфена", "GENPR"])
        self.method_combo.currentIndexChanged.connect(self.on_method_changed)
        method_layout.addWidget(self.method_combo)
        gen_layout.addLayout(method_layout)

        bits_layout = QHBoxLayout()
        self.bits_label = QLabel("Битность:")
        bits_layout.addWidget(self.bits_label)
        self.bits_spin = QSpinBox()
        self.bits_spin.setRange(8, 2048)
        self.bits_spin.setValue(128)
        bits_layout.addWidget(self.bits_spin)
        gen_layout.addLayout(bits_layout)

        genpr_layout = QHBoxLayout()
        self.genpr_m_label = QLabel("m:")
        self.genpr_m_spin = QSpinBox()
        self.genpr_m_spin.setRange(3, 999999999)
        self.genpr_m_spin.setValue(1001)
        self.genpr_k_label = QLabel("k:")
        self.genpr_k_spin = QSpinBox()
        self.genpr_k_spin.setRange(1, 999999)
        self.genpr_k_spin.setValue(100)
        self.genpr_m_label.setVisible(False)
        self.genpr_m_spin.setVisible(False)
        self.genpr_k_label.setVisible(False)
        self.genpr_k_spin.setVisible(False)
        genpr_layout.addWidget(self.genpr_m_label)
        genpr_layout.addWidget(self.genpr_m_spin)
        genpr_layout.addWidget(self.genpr_k_label)
        genpr_layout.addWidget(self.genpr_k_spin)
        gen_layout.addLayout(genpr_layout)

        gen_btn_layout = QHBoxLayout()
        self.btn_gen = QPushButton("Сгенерировать 2 простых")
        self.btn_gen.clicked.connect(self.generate_primes)
        gen_btn_layout.addWidget(self.btn_gen)
        gen_layout.addLayout(gen_btn_layout)

        primes_layout = QHBoxLayout()
        self.p1_edit = QLineEdit()
        self.p1_edit.setPlaceholderText("p1")
        self.p2_edit = QLineEdit()
        self.p2_edit.setPlaceholderText("p2")
        primes_layout.addWidget(self.p1_edit)
        primes_layout.addWidget(self.p2_edit)
        gen_layout.addLayout(primes_layout)

        left_layout.addWidget(gen_group)

        # Группа операций
        ops_group = QGroupBox("Операции")
        ops_layout = QVBoxLayout(ops_group)

        a_layout = QHBoxLayout()
        a_layout.addWidget(QLabel("a ="))
        self.a_edit = QLineEdit()
        a_layout.addWidget(self.a_edit)
        ops_layout.addLayout(a_layout)

        b_layout = QHBoxLayout()
        b_layout.addWidget(QLabel("b ="))
        self.b_edit = QLineEdit()
        b_layout.addWidget(self.b_edit)
        ops_layout.addLayout(b_layout)

        n_layout = QHBoxLayout()
        n_layout.addWidget(QLabel("n ="))
        self.n_edit = QLineEdit("17")
        n_layout.addWidget(self.n_edit)
        ops_layout.addLayout(n_layout)

        m_layout = QHBoxLayout()
        m_layout.addWidget(QLabel("m ="))
        self.m_edit = QLineEdit("101")
        m_layout.addWidget(self.m_edit)
        ops_layout.addLayout(m_layout)

        use_btn_layout = QHBoxLayout()
        self.btn_use = QPushButton("Использовать p1,p2 как a,b")
        self.btn_use.clicked.connect(self.use_primes)
        use_btn_layout.addWidget(self.btn_use)
        ops_layout.addLayout(use_btn_layout)

        calc_btn_layout = QHBoxLayout()
        self.btn_calc = QPushButton("Выполнить операции")
        self.btn_calc.clicked.connect(self.calculate_all)
        calc_btn_layout.addWidget(self.btn_calc)
        ops_layout.addLayout(calc_btn_layout)

        left_layout.addWidget(ops_group)
        left_layout.addStretch()

        # Правая панель результатов
        right_panel = QWidget()
        right_layout = QVBoxLayout(right_panel)

        results_group = QGroupBox("Результаты")
        results_layout = QVBoxLayout(results_group)
        self.results = QTextEdit()
        self.results.setReadOnly(True)
        self.results.setPlaceholderText("Результаты...")
        results_layout.addWidget(self.results)
        right_layout.addWidget(results_group)

        main_layout.addWidget(left_panel)
        main_layout.addWidget(right_panel)

    def on_method_changed(self):
        method = self.get_method()
        is_genpr = (method == "genpr")
        self.bits_label.setVisible(not is_genpr)
        self.bits_spin.setVisible(not is_genpr)
        self.genpr_m_label.setVisible(is_genpr)
        self.genpr_m_spin.setVisible(is_genpr)
        self.genpr_k_label.setVisible(is_genpr)
        self.genpr_k_spin.setVisible(is_genpr)
        if not is_genpr:
            self.adjust_bits_limit()

    def adjust_bits_limit(self):
        method = self.get_method()
        max_bits = METHOD_MAX_BITS.get(method, 1024)
        if self.bits_spin.value() > max_bits:
            self.bits_spin.setValue(max_bits)
            QMessageBox.information(self, "ℹ️ Ограничение", f"Для '{method}' максимум {max_bits} бит.")
        self.bits_spin.setMaximum(max_bits)

    def get_method(self):
        t = self.method_combo.currentText()
        if "Миллер" in t: return "miller-rabin"
        if "Перебор" in t: return "trial"
        if "Решето" in t: return "sieve"
        if "GENPR" in t: return "genpr"
        return "miller-rabin"

    def generate_primes(self):
        try:
            method = self.get_method()
            bits = self.bits_spin.value()
            genpr_params = None
            if method == 'genpr':
                m = self.genpr_m_spin.value()
                k = self.genpr_k_spin.value()
                if m % 2 == 0: m += 1
                genpr_params = (m, k)
            p1 = generate_large_prime(bits, method, genpr_params)
            p2 = generate_large_prime(bits, method, genpr_params)
            attempts = 0
            while p1 == p2 and attempts < 10:
                p2 = generate_large_prime(bits, method, genpr_params)
                attempts += 1
            self.p1_edit.setText(str(p1))
            self.p2_edit.setText(str(p2))
            QMessageBox.information(self, "✅ Успех", f"Сгенерированы два простых (Метод: {method}).")
        except Exception as e:
            QMessageBox.critical(self, "❌ Генерация", str(e))

    def use_primes(self):
        try:
            p1 = self.p1_edit.text()
            p2 = self.p2_edit.text()
            if not p1 or not p2:
                raise ValueError("Сначала сгенерируйте простые.")
            self.a_edit.setText(p1)
            self.b_edit.setText(p2)
        except Exception as e:
            QMessageBox.warning(self, "⚠️ Ошибка", str(e))

    def calculate_all(self):
        try:
            a_txt = self.a_edit.text().strip()
            b_txt = self.b_edit.text().strip()
            n_txt = self.n_edit.text().strip()
            m_txt = self.m_edit.text().strip()
            if not (a_txt and b_txt and n_txt and m_txt):
                raise ValueError("Заполните a, b, n, m.")
            a = int(a_txt)
            b = int(b_txt)
            n = int(n_txt)
            m = int(m_txt)
            if b == 0: raise ValueError("b не может быть 0.")
            if m == 0: raise ValueError("m не может быть 0.")
            add = a + b
            sub = a - b
            mul = a * b
            div_floor = a // b
            modv_ab = a % b
            try:
                div_float = a / b
                if abs(div_float) > 1e300:
                    div_str = "слишком большое"
                else:
                    div_str = f"{div_float:.20g}"
                    if '.' not in div_str and 'e' not in div_str:
                        div_str += ".0"
            except Exception:
                div_str = "ошибка"
            amodm = a % m
            pow_full = pow(a, n)
            digits = len(str(pow_full))
            if digits <= 5000:
                pow_full_str = str(pow_full)
                pow_full_info = ""
            else:
                pow_full_str = f"[число слишком длинное: {digits} цифр]"
                pow_full_info = f"Длина a^n = {digits} цифр"
            pow_mod = mod_exp(a, n, m)
            lines = [
                "Операции:",
                f"a = {a}",
                f"b = {b}",
                f"n = {n}",
                f"m = {m}",
                f"a + b = {add}",
                f"a - b = {sub}",
                f"a * b = {mul}",
                f"a // b = {div_floor}",
                f"a / b = {div_str}",
                f"a mod b = {modv_ab}",
                f"a mod m = {amodm}",
                f"a^n = {pow_full_str}",
                *([pow_full_info] if pow_full_info else []),
                f"a^n mod m = {pow_mod}"
            ]
            self.results.setPlainText('\n'.join(lines))
        except Exception as e:
            QMessageBox.critical(self, "❌ Вычисления", str(e))


# -------------------- RSATab (с полной анимацией) --------------------
class RSATab(QWidget):
    def __init__(self):
        super().__init__()
        main_layout = QHBoxLayout(self)

        # Левая панель управления с прокруткой
        scroll_area = QScrollArea()
        scroll_area.setWidgetResizable(True)
        scroll_area.setMaximumWidth(450)
        scroll_area.setHorizontalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        scroll_area.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)

        left_panel = QWidget()
        left_panel.setObjectName("left_panel_rsa")
        left_layout = QVBoxLayout(left_panel)

        # Группа генерации ключей
        key_gen_group = QGroupBox("Генерация ключей RSA")
        key_gen_layout = QVBoxLayout(key_gen_group)

        # Параметры генерации
        params_layout = QVBoxLayout()

        method_layout = QHBoxLayout()
        method_layout.addWidget(QLabel("Способ:"))
        self.gen_method_combo = QComboBox()
        self.gen_method_combo.addItems(["Автом. (одинаково)", "Автом. (раздельно)", "Ручной ввод"])
        self.gen_method_combo.currentIndexChanged.connect(self.on_generation_method_changed)
        method_layout.addWidget(self.gen_method_combo)
        params_layout.addLayout(method_layout)

        # Параметры p
        p_group = QGroupBox("Параметры p")
        p_layout = QVBoxLayout(p_group)

        p_bits_layout = QHBoxLayout()
        p_bits_layout.addWidget(QLabel("Битность:"))
        self.bits_p_spin = QSpinBox()
        self.bits_p_spin.setRange(10, 2048)
        self.bits_p_spin.setValue(128)
        p_bits_layout.addWidget(self.bits_p_spin)
        p_layout.addLayout(p_bits_layout)

        p_method_layout = QHBoxLayout()
        p_method_layout.addWidget(QLabel("Метод:"))
        self.method_p_combo = QComboBox()
        self.method_p_combo.addItems(["Авто", "Миллер–Рабин", "Перебор", "Решето", "GENPR"])
        self.method_p_combo.currentIndexChanged.connect(self.update_p_method_ui)
        p_method_layout.addWidget(self.method_p_combo)
        p_layout.addLayout(p_method_layout)

        p_genpr_layout = QHBoxLayout()
        self.genpr_m_p_label = QLabel("m:")
        self.genpr_m_p_spin = QSpinBox()
        self.genpr_m_p_spin.setRange(3, 10 ** 9)
        self.genpr_m_p_spin.setValue(1001)
        self.genpr_k_p_label = QLabel("k:")
        self.genpr_k_p_spin = QSpinBox()
        self.genpr_k_p_spin.setRange(1, 10 ** 6)
        self.genpr_k_p_spin.setValue(100)
        p_genpr_layout.addWidget(self.genpr_m_p_label)
        p_genpr_layout.addWidget(self.genpr_m_p_spin)
        p_genpr_layout.addWidget(self.genpr_k_p_label)
        p_genpr_layout.addWidget(self.genpr_k_p_spin)
        self.genpr_m_p_label.setVisible(False)
        self.genpr_m_p_spin.setVisible(False)
        self.genpr_k_p_label.setVisible(False)
        self.genpr_k_p_spin.setVisible(False)
        p_layout.addLayout(p_genpr_layout)
        params_layout.addWidget(p_group)

        # Параметры q (только для раздельного режима)
        self.q_group = QGroupBox("Параметры q")
        q_layout = QVBoxLayout(self.q_group)

        q_bits_layout = QHBoxLayout()
        q_bits_layout.addWidget(QLabel("Битность:"))
        self.bits_q_spin = QSpinBox()
        self.bits_q_spin.setRange(10, 2048)
        self.bits_q_spin.setValue(128)
        q_bits_layout.addWidget(self.bits_q_spin)
        q_layout.addLayout(q_bits_layout)

        q_method_layout = QHBoxLayout()
        q_method_layout.addWidget(QLabel("Метод:"))
        self.method_q_combo = QComboBox()
        self.method_q_combo.addItems(["Авто", "Миллер–Рабин", "Перебор", "Решето", "GENPR"])
        self.method_q_combo.currentIndexChanged.connect(self.update_q_method_ui)
        q_method_layout.addWidget(self.method_q_combo)
        q_layout.addLayout(q_method_layout)

        q_genpr_layout = QHBoxLayout()
        self.genpr_m_q_label = QLabel("m:")
        self.genpr_m_q_spin = QSpinBox()
        self.genpr_m_q_spin.setRange(3, 10 ** 9)
        self.genpr_m_q_spin.setValue(2001)
        self.genpr_k_q_label = QLabel("k:")
        self.genpr_k_q_spin = QSpinBox()
        self.genpr_k_q_spin.setRange(1, 10 ** 6)
        self.genpr_k_q_spin.setValue(100)
        q_genpr_layout.addWidget(self.genpr_m_q_label)
        q_genpr_layout.addWidget(self.genpr_m_q_spin)
        q_genpr_layout.addWidget(self.genpr_k_q_label)
        q_genpr_layout.addWidget(self.genpr_k_q_spin)
        self.genpr_m_q_label.setVisible(False)
        self.genpr_m_q_spin.setVisible(False)
        self.genpr_k_q_label.setVisible(False)
        self.genpr_k_q_spin.setVisible(False)
        q_layout.addLayout(q_genpr_layout)
        params_layout.addWidget(self.q_group)

        key_gen_layout.addLayout(params_layout)

        # Кнопка генерации
        gen_btn_layout = QHBoxLayout()
        self.btn_gen_pq = QPushButton("Сгенерировать p,q")
        self.btn_gen_pq.clicked.connect(self.generate_pq)
        gen_btn_layout.addWidget(self.btn_gen_pq)
        key_gen_layout.addLayout(gen_btn_layout)

        # Поля p и q
        pq_layout = QHBoxLayout()
        pq_layout.addWidget(QLabel("p:"))
        self.p_edit = QLineEdit()
        pq_layout.addWidget(self.p_edit)
        pq_layout.addWidget(QLabel("q:"))
        self.q_edit = QLineEdit()
        pq_layout.addWidget(self.q_edit)
        key_gen_layout.addLayout(pq_layout)

        left_layout.addWidget(key_gen_group)

        # Группа расчета ключей
        key_calc_group = QGroupBox("Расчет ключей")
        key_calc_layout = QVBoxLayout(key_calc_group)

        mode_layout = QHBoxLayout()
        mode_layout.addWidget(QLabel("Режим:"))
        self.key_mode_combo = QComboBox()
        self.key_mode_combo.addItems(["Рассчитать из p и q", "Ввести вручную"])
        self.key_mode_combo.currentIndexChanged.connect(self.on_key_mode_changed)
        mode_layout.addWidget(self.key_mode_combo)
        key_calc_layout.addLayout(mode_layout)

        # Виджет для автоматического расчета
        self.calc_keys_widget = QWidget()
        calc_layout = QVBoxLayout(self.calc_keys_widget)

        e_layout = QHBoxLayout()
        e_layout.addWidget(QLabel("e:"))
        self.e_edit = QLineEdit("65537")
        self.auto_e_cb = QCheckBox("Авто")
        self.auto_e_cb.setChecked(True)
        self.e_edit.setEnabled(False)
        self.auto_e_cb.toggled.connect(lambda checked: self.e_edit.setEnabled(not checked))
        e_layout.addWidget(self.e_edit)
        e_layout.addWidget(self.auto_e_cb)
        calc_layout.addLayout(e_layout)

        calc_btn_layout = QHBoxLayout()
        self.btn_calc_keys = QPushButton("Рассчитать ключи")
        self.btn_calc_keys.clicked.connect(self.calculate_keys)
        calc_btn_layout.addWidget(self.btn_calc_keys)
        calc_layout.addLayout(calc_btn_layout)
        key_calc_layout.addWidget(self.calc_keys_widget)

        # Виджет для ручного ввода
        self.manual_keys_widget = QWidget()
        manual_layout = QVBoxLayout(self.manual_keys_widget)

        n_layout = QHBoxLayout()
        n_layout.addWidget(QLabel("N:"))
        self.N_edit = QLineEdit()
        n_layout.addWidget(self.N_edit)
        manual_layout.addLayout(n_layout)

        e_manual_layout = QHBoxLayout()
        e_manual_layout.addWidget(QLabel("e:"))
        self.e_manual_edit = QLineEdit("65537")
        e_manual_layout.addWidget(self.e_manual_edit)
        manual_layout.addLayout(e_manual_layout)

        d_layout = QHBoxLayout()
        d_layout.addWidget(QLabel("d:"))
        self.d_edit = QLineEdit()
        d_layout.addWidget(self.d_edit)
        manual_layout.addLayout(d_layout)

        manual_btn_layout = QHBoxLayout()
        self.btn_set_manual_keys = QPushButton("Установить ключи")
        self.btn_set_manual_keys.clicked.connect(self.set_manual_keys)
        manual_btn_layout.addWidget(self.btn_set_manual_keys)
        manual_layout.addLayout(manual_btn_layout)

        self.manual_keys_widget.setVisible(False)
        key_calc_layout.addWidget(self.manual_keys_widget)

        # Отображение ключей
        keys_display_layout = QVBoxLayout()
        self.N_label = QLabel("N = ?")
        self.phi_label = QLabel("φ(N) = ?")
        self.d_label = QLabel("d = ?")
        keys_display_layout.addWidget(self.N_label)
        keys_display_layout.addWidget(self.phi_label)
        keys_display_layout.addWidget(self.d_label)
        key_calc_layout.addLayout(keys_display_layout)

        # Управление ключами
        keys_manage_layout = QHBoxLayout()
        self.btn_load_keys = QPushButton("Загрузить ключи")
        self.btn_load_keys.clicked.connect(self.load_keys_from_file)
        self.btn_save_keys = QPushButton("Сохранить ключи")
        self.btn_save_keys.clicked.connect(self.save_keys_to_file)
        keys_manage_layout.addWidget(self.btn_load_keys)
        keys_manage_layout.addWidget(self.btn_save_keys)
        key_calc_layout.addLayout(keys_manage_layout)

        left_layout.addWidget(key_calc_group)

        # Группа операций
        ops_group = QGroupBox("Операции")
        ops_layout = QVBoxLayout(ops_group)

        encrypt_btn_layout = QHBoxLayout()
        self.btn_encrypt = QPushButton("Зашифровать")
        self.btn_encrypt.clicked.connect(self.encrypt_rsa)
        encrypt_btn_layout.addWidget(self.btn_encrypt)
        ops_layout.addLayout(encrypt_btn_layout)

        decrypt_btn_layout = QHBoxLayout()
        self.btn_decrypt = QPushButton("Расшифровать")
        self.btn_decrypt.clicked.connect(self.decrypt_rsa)
        decrypt_btn_layout.addWidget(self.btn_decrypt)
        ops_layout.addLayout(decrypt_btn_layout)

        left_layout.addWidget(ops_group)

        # Группа лога
        log_group = QGroupBox("Лог операций")
        log_layout = QVBoxLayout(log_group)
        self.log_text_edit = QTextEdit()
        self.log_text_edit.setReadOnly(True)
        self.log_text_edit.setMaximumHeight(150)
        log_layout.addWidget(self.log_text_edit)

        log_btns_layout = QHBoxLayout()
        self.btn_save_rsa_log = QPushButton("Сохранить лог")
        self.btn_save_rsa_log.clicked.connect(self.save_rsa_log)
        self.btn_clear_rsa_log = QPushButton("Очистить лог")
        self.btn_clear_rsa_log.clicked.connect(self.log_text_edit.clear)
        log_btns_layout.addWidget(self.btn_save_rsa_log)
        log_btns_layout.addWidget(self.btn_clear_rsa_log)
        log_layout.addLayout(log_btns_layout)

        left_layout.addWidget(log_group)
        left_layout.addStretch()

        scroll_area.setWidget(left_panel)
        main_layout.addWidget(scroll_area)

        # Правая панель данных
        right_panel = QWidget()
        right_layout = QVBoxLayout(right_panel)

        # Группа ввода
        input_group = QGroupBox("Входные данные")
        input_layout = QVBoxLayout(input_group)
        self.input_text_edit = QTextEdit()
        self.input_text_edit.setPlaceholderText("Введите текст, список чисел или компактный HEX шифр")
        input_layout.addWidget(self.input_text_edit)

        input_btns_layout = QHBoxLayout()
        self.btn_load_input = QPushButton("Загрузить из файла")
        self.btn_load_input.clicked.connect(self.load_input_data)
        self.btn_clear_input = QPushButton("Очистить")
        self.btn_clear_input.clicked.connect(self.input_text_edit.clear)
        input_btns_layout.addWidget(self.btn_load_input)
        input_btns_layout.addWidget(self.btn_clear_input)
        input_layout.addLayout(input_btns_layout)

        right_layout.addWidget(input_group)

        # Группа вывода
        output_group = QGroupBox("Выходные данные")
        output_layout = QVBoxLayout(output_group)
        self.output_text_edit = QTextEdit()
        self.output_text_edit.setPlaceholderText("Результат...")
        output_layout.addWidget(self.output_text_edit)

        output_btns_layout = QHBoxLayout()
        self.btn_save_output = QPushButton("Сохранить в файл")
        self.btn_save_output.clicked.connect(self.save_output_data)
        self.btn_clear_output = QPushButton("Очистить")
        self.btn_clear_output.clicked.connect(self.output_text_edit.clear)
        self.btn_copy_output = QPushButton("Копировать")
        self.btn_copy_output.clicked.connect(self.copy_output)
        output_btns_layout.addWidget(self.btn_save_output)
        output_btns_layout.addWidget(self.btn_clear_output)
        output_btns_layout.addWidget(self.btn_copy_output)
        output_layout.addLayout(output_btns_layout)

        right_layout.addWidget(output_group)

        main_layout.addWidget(right_panel)

        # Инициализация переменных
        self.N = None
        self.phi = None
        self.d = None
        self.e_val = 65537
        self.blocks = []
        self.block_bytes = None
        self.plain_lengths = []
        self.total_plain_bytes = None
        self.cipher_blocks = []
        self.last_cipher_payload = None
        self.last_output_kind = None

        self.on_key_mode_changed(0)
        self.on_generation_method_changed(0)



    def detect_input_type(self, content):
        if not content or not content.strip():
            return 'empty'
        s = content.strip()

        # Проверяем, является ли ввод компактным HEX
        if self.N and re.fullmatch(r'[0-9a-fA-F]+', s):
            try:
                compact_hex_to_blocks(s, self.N)
                return 'compact_hex'
            except:
                pass

        # Проверяем, является ли ввод списком чисел
        allowed = set("[]{}(),; \t\r\n0123456789+")
        if all(ch in allowed for ch in s):
            try:
                blocks = parse_numbers(s)
                if blocks:
                    return 'blocks'
            except:
                pass

        # По умолчанию считаем текстом
        return 'text'

    # Остальные методы RSATab (on_generation_method_changed, update_p_method_ui, update_q_method_ui,
    # on_key_mode_changed, generate_pq, calculate_keys, set_manual_keys, encrypt_rsa, decrypt_rsa,
    # load_keys_from_file, save_keys_to_file, load_input_data, save_output_data, copy_output, save_rsa_log)
    # остаются без изменений, как в предыдущей реализации

    # Добавим только недостающие заглушки для оставшихся методов
    def on_generation_method_changed(self, index):
        if index == 0:  # Автом. (одинаково)
            self.q_group.setVisible(False)
        elif index == 1:  # Автом. (раздельно)
            self.q_group.setVisible(True)
        else:  # Ручной ввод
            self.q_group.setVisible(False)

    def update_p_method_ui(self):
        is_genpr = (self.method_p_combo.currentText() == "GENPR")
        self.genpr_m_p_label.setVisible(is_genpr)
        self.genpr_m_p_spin.setVisible(is_genpr)
        self.genpr_k_p_label.setVisible(is_genpr)
        self.genpr_k_p_spin.setVisible(is_genpr)

    def update_q_method_ui(self):
        is_genpr = (self.method_q_combo.currentText() == "GENPR")
        self.genpr_m_q_label.setVisible(is_genpr)
        self.genpr_m_q_spin.setVisible(is_genpr)
        self.genpr_k_q_label.setVisible(is_genpr)
        self.genpr_k_q_spin.setVisible(is_genpr)

    def on_key_mode_changed(self, index):
        self.calc_keys_widget.setVisible(index == 0)
        self.manual_keys_widget.setVisible(index == 1)

    def generate_pq(self):
        try:
            gm = self.gen_method_combo.currentIndex()
            if gm == 2:  # Ручной ввод
                QMessageBox.information(self, "Информация", "Введите p и q вручную в поля ниже.")
                return

            bits_p = self.bits_p_spin.value()
            method_p = self.method_p_combo.currentText().lower()
            if "миллер" in method_p:
                method_p = "miller-rabin"
            elif "перебор" in method_p:
                method_p = "trial"
            elif "решето" in method_p:
                method_p = "sieve"
            else:
                method_p = "miller-rabin"

            if gm == 0:  # Одинаково
                bits_q = bits_p
                method_q = method_p
            else:  # Раздельно
                bits_q = self.bits_q_spin.value()
                method_q = self.method_q_combo.currentText().lower()
                if "миллер" in method_q:
                    method_q = "miller-rabin"
                elif "перебор" in method_q:
                    method_q = "trial"
                elif "решето" in method_q:
                    method_q = "sieve"
                else:
                    method_q = "miller-rabin"

            p = generate_large_prime(bits_p, method_p)
            q = generate_large_prime(bits_q, method_q)

            self.p_edit.setText(str(p))
            self.q_edit.setText(str(q))
            self.log_text_edit.append(f"Сгенерированы: p={p}, q={q}")

        except Exception as e:
            QMessageBox.critical(self, "Ошибка", f"Ошибка генерации: {str(e)}")

    def calculate_keys(self):
        try:
            p = int(self.p_edit.text())
            q = int(self.q_edit.text())
            self.N = p * q
            self.phi = (p - 1) * (q - 1)

            if self.auto_e_cb.isChecked():
                self.e_val = 65537
                if self.e_val >= self.phi:
                    self.e_val = 3
                while math.gcd(self.e_val, self.phi) != 1:
                    self.e_val += 2
            else:
                self.e_val = int(self.e_edit.text())

            self.d = mod_inverse(self.e_val, self.phi)

            self.N_label.setText(f"N = {self.N}")
            self.phi_label.setText(f"φ(N) = {self.phi}")
            self.d_label.setText(f"d = {self.d}")

            self.log_text_edit.append(f"Рассчитаны ключи: N={self.N}, e={self.e_val}, d={self.d}")

        except Exception as e:
            QMessageBox.critical(self, "Ошибка", f"Ошибка расчета ключей: {str(e)}")

    def set_manual_keys(self):
        try:
            self.N = int(self.N_edit.text())
            self.e_val = int(self.e_manual_edit.text())
            self.d = int(self.d_edit.text())

            self.N_label.setText(f"N = {self.N}")
            self.phi_label.setText("φ(N) = ?")
            self.d_label.setText(f"d = {self.d}")

            self.log_text_edit.append(f"Установлены ключи вручную: N={self.N}, e={self.e_val}, d={self.d}")

        except Exception as e:
            QMessageBox.critical(self, "Ошибка", f"Ошибка установки ключей: {str(e)}")

    def encrypt_rsa(self):
        try:
            if self.N is None or self.e_val is None:
                raise ValueError("Сначала установите ключи")

            text = self.input_text_edit.toPlainText()
            if not text:
                raise ValueError("Введите текст для шифрования")

            # Используем существующую логику шифрования
            self.blocks, self.block_bytes, self.plain_lengths, self.total_plain_bytes = encode_text_to_blocks(text, self.N)
            e = int(self.e_edit.text())
            self.cipher_blocks = []
            
            # Очищаем лог
            self.log_text_edit.clear()
            self.log_text_edit.append("=== Начало шифрования ===")
            self.log_text_edit.append(f"Всего блоков для шифрования: {len(self.blocks)}")
            self.log_text_edit.append(f"Публичная экспонента (e): {e}")
            self.log_text_edit.append(f"Модуль (N): {self.N}")
            self.log_text_edit.append("")
            
            # Шифруем каждый блок с подробным логированием
            for idx, m in enumerate(self.blocks):
                m_len = self.plain_lengths[idx]
                
                # Получаем байты блока
                try:
                    m_bytes = m.to_bytes(m_len, 'big')
                except OverflowError:
                    actual_len = (m.bit_length() + 7) // 8
                    m_bytes = m.to_bytes(actual_len, 'big')
                m_text = bytes_to_printable_utf8(m_bytes)
                
                # Шифруем блок
                c = mod_exp(m, e, self.N)
                self.cipher_blocks.append(c)
                
                # Детальное логирование
                self.log_text_edit.append(f"--- Блок {idx} ---")
                self.log_text_edit.append(f"Открытый текст: '{m_text}'")
                self.log_text_edit.append(f"Байты: {m_bytes.hex().upper()}")
                self.log_text_edit.append(f"Числовое значение (M): {m}")
                self.log_text_edit.append(f"Операция: M^e mod N = {m}^{e} mod {self.N}")
                self.log_text_edit.append(f"Зашифрованное значение (C): {c}")
                self.log_text_edit.append("")
            
            compact_hex = blocks_to_compact_hex(self.cipher_blocks, self.N)
            self.output_text_edit.setPlainText(compact_hex)
            
            self.log_text_edit.append("=== Шифрование завершено ===")
            self.log_text_edit.append(f"Результат (компактный HEX): {compact_hex[:100]}..." if len(compact_hex) > 100 else f"Результат (компактный HEX): {compact_hex}")

        except Exception as e:
            QMessageBox.critical(self, "Ошибка", f"Ошибка шифрования: {str(e)}")

    def decrypt_rsa(self):
        try:
            if self.N is None or self.d is None:
                raise ValueError("Сначала установите ключи")

            cipher = self.input_text_edit.toPlainText().strip()
            if not cipher:
                raise ValueError("Введите шифр для расшифровки")

            # Определяем тип ввода и дешифруем
            input_type = self.detect_input_type(cipher)
            if input_type == 'compact_hex':
                cblocks = compact_hex_to_blocks(cipher, self.N)
            elif input_type == 'blocks':
                cblocks = parse_numbers(cipher)
            else:
                raise ValueError("Нужен компактный HEX или список чисел")

            # Очищаем лог
            self.log_text_edit.clear()
            self.log_text_edit.append("=== Начало дешифрования ===")
            self.log_text_edit.append(f"Всего блоков для дешифрования: {len(cblocks)}")
            self.log_text_edit.append(f"Приватная экспонента (d): {self.d}")
            self.log_text_edit.append(f"Модуль (N): {self.N}")
            self.log_text_edit.append("")
            
            plain = []
            bb = self.block_bytes or max(1, (self.N.bit_length() - 1) // 8)
            
            # Дешифруем каждый блок с подробным логированием
            for idx, c in enumerate(cblocks):
                # Дешифруем блок
                m = mod_exp(c, self.d, self.N)
                plain.append(m)
                
                # Получаем байты блока
                try:
                    plen = self.plain_lengths[idx] if (self.plain_lengths and idx < len(self.plain_lengths)) else bb
                    m_bytes = m.to_bytes(plen, 'big')
                except OverflowError:
                    actual_len = (m.bit_length() + 7) // 8
                    m_bytes = m.to_bytes(actual_len, 'big')
                m_text = bytes_to_printable_utf8(m_bytes)
                
                # Детальное логирование
                self.log_text_edit.append(f"--- Блок {idx} ---")
                self.log_text_edit.append(f"Зашифрованное значение (C): {c}")
                self.log_text_edit.append(f"Операция: C^d mod N = {c}^{self.d} mod {self.N}")
                self.log_text_edit.append(f"Расшифрованное значение (M): {m}")
                self.log_text_edit.append(f"Байты: {m_bytes.hex().upper()}")
                self.log_text_edit.append(f"Открытый текст: '{m_text}'")
                self.log_text_edit.append("")
            
            text = decode_blocks_to_text_precise(plain, bb, self.plain_lengths, self.total_plain_bytes)
            self.output_text_edit.setPlainText(text)
            
            self.log_text_edit.append("=== Дешифрование завершено ===")
            self.log_text_edit.append(f"Результат: {text[:100]}..." if len(text) > 100 else f"Результат: {text}")

        except Exception as e:
            QMessageBox.critical(self, "Ошибка", f"Ошибка дешифрования: {str(e)}")

    def load_keys_from_file(self):
        QMessageBox.information(self, "Информация", "Функция загрузки ключей будет реализована позже")

    def save_keys_to_file(self):
        QMessageBox.information(self, "Информация", "Функция сохранения ключей будет реализована позже")

    def load_input_data(self):
        QMessageBox.information(self, "Информация", "Функция загрузки данных будет реализована позже")

    def save_output_data(self):
        QMessageBox.information(self, "Информация", "Функция сохранения данных будет реализована позже")

    def copy_output(self):
        text = self.output_text_edit.toPlainText()
        if text:
            QApplication.clipboard().setText(text)
            QMessageBox.information(self, "Успех", "Текст скопирован в буфер обмена")

    def save_rsa_log(self):
        log_text = self.log_text_edit.toPlainText()
        if not log_text:
            QMessageBox.warning(self, "Предупреждение", "Лог пуст")
            return

        path, _ = QFileDialog.getSaveFileName(self, "Сохранить лог", "", "Text Files (*.txt)")
        if path:
            try:
                with open(path, 'w', encoding='utf-8') as f:
                    f.write(log_text)
                QMessageBox.information(self, "Успех", "Лог сохранен")
            except Exception as e:
                QMessageBox.critical(self, "Ошибка", f"Ошибка сохранения: {str(e)}")


# -------------------- RSALibraryTab (полная реализация) --------------------
class RSALibraryTab(QWidget):
    def __init__(self):
        super().__init__()
        main_layout = QHBoxLayout(self)

        # Левая панель управления
        left_panel = QWidget()
        left_panel.setMaximumWidth(450)
        left_layout = QVBoxLayout(left_panel)

        # Группа ключей
        key_group = QGroupBox("Ключи RSA")
        key_layout = QVBoxLayout(key_group)

        bits_layout = QHBoxLayout()
        bits_layout.addWidget(QLabel("Битность:"))
        self.lib_bits_spin = QSpinBox()
        self.lib_bits_spin.setRange(512, 4096)
        self.lib_bits_spin.setValue(2048)
        bits_layout.addWidget(self.lib_bits_spin)
        key_layout.addLayout(bits_layout)

        gen_btn_layout = QHBoxLayout()
        self.btn_lib_generate = QPushButton("Сгенерировать пару ключей")
        self.btn_lib_generate.clicked.connect(self.lib_generate_keys)
        gen_btn_layout.addWidget(self.btn_lib_generate)
        key_layout.addLayout(gen_btn_layout)

        # Публичный ключ
        pub_key_group = QGroupBox("Публичный ключ")
        pub_key_layout = QVBoxLayout(pub_key_group)
        self.pub_key_edit = QTextEdit()
        self.pub_key_edit.setPlaceholderText("Публичный ключ (PEM)")
        self.pub_key_edit.setMaximumHeight(120)
        pub_key_layout.addWidget(self.pub_key_edit)

        pub_btns_layout = QHBoxLayout()
        btn_load_pub = QPushButton("Загрузить")
        btn_load_pub.clicked.connect(self.lib_load_public_key)
        btn_save_pub = QPushButton("Сохранить")
        btn_save_pub.clicked.connect(self.lib_save_public_key)
        pub_btns_layout.addWidget(btn_load_pub)
        pub_btns_layout.addWidget(btn_save_pub)
        pub_key_layout.addLayout(pub_btns_layout)
        key_layout.addWidget(pub_key_group)

        # Приватный ключ
        priv_key_group = QGroupBox("Приватный ключ")
        priv_key_layout = QVBoxLayout(priv_key_group)
        self.priv_key_edit = QTextEdit()
        self.priv_key_edit.setPlaceholderText("Приватный ключ (PEM)")
        self.priv_key_edit.setMaximumHeight(120)
        priv_key_layout.addWidget(self.priv_key_edit)

        priv_btns_layout = QHBoxLayout()
        btn_load_priv = QPushButton("Загрузить")
        btn_load_priv.clicked.connect(self.lib_load_private_key)
        btn_save_priv = QPushButton("Сохранить")
        btn_save_priv.clicked.connect(self.lib_save_private_key)
        priv_btns_layout.addWidget(btn_load_priv)
        priv_btns_layout.addWidget(btn_save_priv)
        priv_key_layout.addLayout(priv_btns_layout)
        key_layout.addWidget(priv_key_group)

        left_layout.addWidget(key_group)

        # Группа операций
        ops_group = QGroupBox("Операции")
        ops_layout = QVBoxLayout(ops_group)

        encrypt_btn_layout = QHBoxLayout()
        self.btn_lib_encrypt = QPushButton("Зашифровать (OAEP)")
        self.btn_lib_encrypt.clicked.connect(self.lib_encrypt)
        encrypt_btn_layout.addWidget(self.btn_lib_encrypt)
        ops_layout.addLayout(encrypt_btn_layout)

        decrypt_btn_layout = QHBoxLayout()
        self.btn_lib_decrypt = QPushButton("Расшифровать (OAEP)")
        self.btn_lib_decrypt.clicked.connect(self.lib_decrypt)
        decrypt_btn_layout.addWidget(self.btn_lib_decrypt)
        ops_layout.addLayout(decrypt_btn_layout)

        # Группа информации
        info_group = QGroupBox("Информация")
        info_layout = QVBoxLayout(info_group)
        self.lib_status_label = QLabel("Готово.")
        self.lib_info_label = QLabel("")
        self.lib_info_label.setWordWrap(True)
        info_layout.addWidget(self.lib_status_label)
        info_layout.addWidget(self.lib_info_label)
        ops_layout.addWidget(info_group)

        left_layout.addWidget(ops_group)
        left_layout.addStretch()

        # Правая панель данных
        right_panel = QWidget()
        right_layout = QVBoxLayout(right_panel)

        # Группа ввода
        input_group = QGroupBox("Входные данные")
        input_layout = QVBoxLayout(input_group)
        self.input_edit = QTextEdit()
        self.input_edit.setPlaceholderText("Текст или Base64 блоки")
        input_layout.addWidget(self.input_edit)

        input_btns_layout = QHBoxLayout()
        self.btn_load_input_lib = QPushButton("Загрузить вход")
        self.btn_load_input_lib.clicked.connect(self.load_library_input_file)
        self.btn_clear_input_lib = QPushButton("Очистить вход")
        self.btn_clear_input_lib.clicked.connect(self.input_edit.clear)
        input_btns_layout.addWidget(self.btn_load_input_lib)
        input_btns_layout.addWidget(self.btn_clear_input_lib)
        input_layout.addLayout(input_btns_layout)

        right_layout.addWidget(input_group)

        # Группа вывода
        output_group = QGroupBox("Выходные данные")
        output_layout = QVBoxLayout(output_group)
        self.output_edit = QTextEdit()
        self.output_edit.setPlaceholderText("Результат")
        output_layout.addWidget(self.output_edit)

        output_btns_layout = QHBoxLayout()
        self.btn_save_output_lib = QPushButton("Сохранить выход")
        self.btn_save_output_lib.clicked.connect(self.save_library_output_file)
        self.btn_copy_output_lib = QPushButton("Копировать выход")
        self.btn_copy_output_lib.clicked.connect(
            lambda: QApplication.clipboard().setText(self.output_edit.toPlainText()))
        self.btn_clear_output_lib = QPushButton("Очистить выход")
        self.btn_clear_output_lib.clicked.connect(self.output_edit.clear)
        output_btns_layout.addWidget(self.btn_save_output_lib)
        output_btns_layout.addWidget(self.btn_copy_output_lib)
        output_btns_layout.addWidget(self.btn_clear_output_lib)
        output_layout.addLayout(output_btns_layout)

        right_layout.addWidget(output_group)

        main_layout.addWidget(left_panel)
        main_layout.addWidget(right_panel)

        self.private_key = None
        self.public_key = None

    def set_status(self, text):
        self.lib_status_label.setText(text)

    def set_info(self, text):
        self.lib_info_label.setText(text)

    def ensure_public_key(self):
        if self.public_key:
            return self.public_key
        pem = self.pub_key_edit.toPlainText().strip()
        if not pem:
            raise ValueError("Публичный ключ не задан.")
        try:
            self.public_key = serialization.load_pem_public_key(pem.encode('utf-8'))
            return self.public_key
        except Exception as e:
            raise ValueError(f"Неверный формат публичного ключа: {str(e)}")

    def ensure_private_key(self):
        if self.private_key:
            return self.private_key
        pem = self.priv_key_edit.toPlainText().strip()
        if not pem:
            raise ValueError("Приватный ключ не задан.")
        try:
            self.private_key = serialization.load_pem_private_key(pem.encode('utf-8'), password=None)
            return self.private_key
        except Exception as e:
            raise ValueError(f"Неверный формат приватного ключа: {str(e)}")

    def lib_generate_keys(self):
        try:
            bits = self.lib_bits_spin.value()
            self.set_status(f"Генерация ключей {bits} бит...")
            QApplication.processEvents()  # Обновляем интерфейс

            # Генерируем приватный ключ
            private_key = crypto_rsa.generate_private_key(
                public_exponent=65537,
                key_size=bits
            )

            # Получаем публичный ключ
            public_key = private_key.public_key()

            # Сериализуем ключи в PEM формат
            private_pem = private_key.private_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PrivateFormat.PKCS8,
                encryption_algorithm=serialization.NoEncryption()
            ).decode('utf-8')

            public_pem = public_key.public_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PublicFormat.SubjectPublicKeyInfo
            ).decode('utf-8')

            # Устанавливаем ключи в интерфейс
            self.private_key = private_key
            self.public_key = public_key
            self.priv_key_edit.setPlainText(private_pem)
            self.pub_key_edit.setPlainText(public_pem)

            # Получаем информацию о ключах
            key_info = self.get_key_info(public_key)

            self.set_status(f"✅ Сгенерирована новая пара ключей {bits} бит")
            self.set_info(key_info)

        except Exception as e:
            QMessageBox.critical(self, "❌ Ошибка", f"Ошибка генерации ключей:\n{str(e)}")
            self.set_status("Ошибка генерации ключей")

    def get_key_info(self, public_key):
        """Получить информацию о ключе"""
        try:
            numbers = public_key.public_numbers()
            key_size = public_key.key_size
            n_hex = hex(numbers.n)[2:].upper()
            e_hex = hex(numbers.e)[2:].upper()

            # Обрезаем длинные значения для отображения
            n_display = n_hex[:50] + "..." if len(n_hex) > 50 else n_hex
            e_display = e_hex

            info = f"""
<b>Информация о ключе:</b>
• Размер ключа: {key_size} бит
• Модуль (N): {n_display}
• Публичная экспонента (e): {e_display}
• Алгоритм: RSA-OAEP с SHA-256
• Макс. размер данных: ~{key_size // 8 - 66} байт
"""
            return info
        except Exception as e:
            return f"Информация о ключе недоступна: {str(e)}"

    def lib_load_public_key(self):
        path, _ = QFileDialog.getOpenFileName(self, "Загрузить публичный ключ", "", "PEM Files (*.pem);;All Files (*)")
        if not path:
            return
        try:
            with open(path, 'r', encoding='utf-8') as f:
                pem = f.read()

            # Проверяем валидность ключа
            public_key = serialization.load_pem_public_key(pem.encode('utf-8'))
            self.public_key = public_key
            self.pub_key_edit.setPlainText(pem)

            key_info = self.get_key_info(public_key)
            self.set_status("✅ Публичный ключ загружен")
            self.set_info(key_info)

        except Exception as e:
            QMessageBox.critical(self, "❌ Ошибка", f"Ошибка загрузки публичного ключа:\n{str(e)}")

    def lib_save_public_key(self):
        pem = self.pub_key_edit.toPlainText().strip()
        if not pem:
            QMessageBox.warning(self, "⚠️ Внимание", "Нет публичного ключа для сохранения.")
            return

        path, _ = QFileDialog.getSaveFileName(self, "Сохранить публичный ключ", "public_key.pem",
                                              "PEM Files (*.pem);;All Files (*)")
        if path:
            try:
                with open(path, 'w', encoding='utf-8') as f:
                    f.write(pem)
                self.set_status("✅ Публичный ключ сохранён")
            except Exception as e:
                QMessageBox.critical(self, "❌ Ошибка", f"Ошибка сохранения:\n{str(e)}")

    def lib_load_private_key(self):
        path, _ = QFileDialog.getOpenFileName(self, "Загрузить приватный ключ", "", "PEM Files (*.pem);;All Files (*)")
        if not path:
            return
        try:
            with open(path, 'r', encoding='utf-8') as f:
                pem = f.read()

            # Проверяем валидность ключа
            private_key = serialization.load_pem_private_key(pem.encode('utf-8'), password=None)
            self.private_key = private_key
            self.priv_key_edit.setPlainText(pem)

            # Также загружаем соответствующий публичный ключ
            public_key = private_key.public_key()
            public_pem = public_key.public_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PublicFormat.SubjectPublicKeyInfo
            ).decode('utf-8')

            self.public_key = public_key
            self.pub_key_edit.setPlainText(public_pem)

            key_info = self.get_key_info(public_key)
            self.set_status("✅ Приватный ключ загружен")
            self.set_info(key_info)

        except Exception as e:
            QMessageBox.critical(self, "❌ Ошибка", f"Ошибка загрузки приватного ключа:\n{str(e)}")

    def lib_save_private_key(self):
        pem = self.priv_key_edit.toPlainText().strip()
        if not pem:
            QMessageBox.warning(self, "⚠️ Внимание", "Нет приватного ключа для сохранения.")
            return

        path, _ = QFileDialog.getSaveFileName(self, "Сохранить приватный ключ", "private_key.pem",
                                              "PEM Files (*.pem);;All Files (*)")
        if path:
            try:
                with open(path, 'w', encoding='utf-8') as f:
                    f.write(pem)
                self.set_status("✅ Приватный ключ сохранён")
            except Exception as e:
                QMessageBox.critical(self, "❌ Ошибка", f"Ошибка сохранения:\n{str(e)}")

    def _chunk_encrypt(self, public_key, data_bytes, hash_alg=hashes.SHA256()):
        """Шифрование данных с разбиением на блоки"""
        key_size = public_key.key_size
        # Максимальный размер блока для OAEP
        max_block_size = key_size // 8 - 2 * hash_alg.digest_size - 2

        if max_block_size <= 0:
            raise ValueError("Слишком маленький размер ключа для OAEP")

        # Разбиваем данные на блоки
        chunks = []
        for i in range(0, len(data_bytes), max_block_size):
            chunk = data_bytes[i:i + max_block_size]
            chunks.append(chunk)

        # Шифруем каждый блок
        encrypted_chunks = []
        for i, chunk in enumerate(chunks):
            try:
                encrypted = public_key.encrypt(
                    chunk,
                    crypto_padding.OAEP(
                        mgf=crypto_padding.MGF1(algorithm=hash_alg),
                        algorithm=hash_alg,
                        label=None
                    )
                )
                encrypted_chunks.append(encrypted)
            except Exception as e:
                raise ValueError(f"Ошибка шифрования блока {i}: {str(e)}")

        # Кодируем в Base64
        base64_chunks = [base64.b64encode(chunk).decode('utf-8') for chunk in encrypted_chunks]
        return base64_chunks

    def _chunk_decrypt(self, private_key, base64_chunks, hash_alg=hashes.SHA256()):
        """Дешифрование данных из Base64 блоков"""
        decrypted_data = bytearray()

        for i, base64_chunk in enumerate(base64_chunks):
            try:
                # Декодируем из Base64
                encrypted_data = base64.b64decode(base64_chunk)

                # Дешифруем
                decrypted_chunk = private_key.decrypt(
                    encrypted_data,
                    crypto_padding.OAEP(
                        mgf=crypto_padding.MGF1(algorithm=hash_alg),
                        algorithm=hash_alg,
                        label=None
                    )
                )
                decrypted_data.extend(decrypted_chunk)

            except Exception as e:
                raise ValueError(f"Ошибка дешифрования блока {i}: {str(e)}")

        return bytes(decrypted_data)

    def lib_encrypt(self):
        try:
            public_key = self.ensure_public_key()
            input_text = self.input_edit.toPlainText().strip()

            if not input_text:
                raise ValueError("Введите текст для шифрования")

            self.set_status("Шифрование...")
            QApplication.processEvents()

            # Преобразуем текст в байты
            data_bytes = input_text.encode('utf-8')

            # Шифруем данные
            encrypted_chunks = self._chunk_encrypt(public_key, data_bytes)

            # Формируем результат
            result = '\n'.join(encrypted_chunks)

            self.output_edit.setPlainText(result)
            self.set_status(f"✅ Зашифровано {len(encrypted_chunks)} блок(ов)")
            self.set_info(f"Исходный размер: {len(data_bytes)} байт\nЗашифровано блоков: {len(encrypted_chunks)}")

        except Exception as e:
            QMessageBox.critical(self, "❌ Ошибка", f"Ошибка шифрования:\n{str(e)}")
            self.set_status("Ошибка шифрования")

    def lib_decrypt(self):
        try:
            private_key = self.ensure_private_key()
            input_text = self.input_edit.toPlainText().strip()

            if not input_text:
                raise ValueError("Введите Base64 блоки для дешифрования")

            self.set_status("Дешифрование...")
            QApplication.processEvents()

            # Разбиваем вход на строки (каждая строка - отдельный блок)
            lines = [line.strip() for line in input_text.split('\n') if line.strip()]

            if not lines:
                raise ValueError("Нет данных для дешифрования")

            # Проверяем, что все строки - валидный Base64
            for i, line in enumerate(lines):
                try:
                    base64.b64decode(line)
                except:
                    raise ValueError(f"Строка {i + 1} содержит невалидный Base64")

            # Дешифруем данные
            decrypted_data = self._chunk_decrypt(private_key, lines)

            # Пытаемся декодировать как текст
            try:
                result = decrypted_data.decode('utf-8')
            except UnicodeDecodeError:
                # Если не получается декодировать как UTF-8, показываем как hex
                result = f"[Бинарные данные, размер: {len(decrypted_data)} байт]\n" + decrypted_data.hex()

            self.output_edit.setPlainText(result)
            self.set_status("✅ Расшифровано успешно")
            self.set_info(f"Расшифровано блоков: {len(lines)}\nРазмер данных: {len(decrypted_data)} байт")

        except Exception as e:
            QMessageBox.critical(self, "❌ Ошибка", f"Ошибка дешифрования:\n{str(e)}")
            self.set_status("Ошибка дешифрования")

    def load_library_input_file(self):
        path, _ = QFileDialog.getOpenFileName(self, "Загрузить входные данные", "", "Text Files (*.txt);;All Files (*)")
        if not path:
            return
        try:
            with open(path, 'r', encoding='utf-8') as f:
                content = f.read()

            if not content.strip():
                QMessageBox.warning(self, "⚠️ Внимание", "Файл пуст.")
                return

            self.input_edit.setPlainText(content)
            self.set_status("✅ Входные данные загружены")

            # Автоматически определяем тип данных
            lines = [line.strip() for line in content.split('\n') if line.strip()]
            if len(lines) > 1 or (len(lines) == 1 and len(lines[0]) > 100):
                self.set_info("Обнаружены Base64 блоки шифротекста")
            else:
                self.set_info("Обнаружен обычный текст")

        except Exception as e:
            QMessageBox.critical(self, "❌ Ошибка", f"Ошибка загрузки файла:\n{str(e)}")

    def save_library_output_file(self):
        content = self.output_edit.toPlainText().strip()
        if not content:
            QMessageBox.warning(self, "⚠️ Внимание", "Нет данных для сохранения.")
            return

        path, _ = QFileDialog.getSaveFileName(self, "Сохранить выходные данные", "",
                                              "Text Files (*.txt);;All Files (*)")
        if not path:
            return

        try:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(content)
            self.set_status("✅ Выходные данные сохранены")
        except Exception as e:
            QMessageBox.critical(self, "❌ Ошибка", f"Ошибка сохранения:\n{str(e)}")

# -------------------- Главное окно --------------------
class CryptoSuite(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Криптографический практикум")
        self.resize(1400, 900)
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)

        tabs = QTabWidget()
        tabs.addTab(GammaTab(), "🔒 ПЗ-9: Гаммирование")
        tabs.addTab(ModArithmeticTab(), "🧮 ПЗ-10: Модулярная арифметика")
        tabs.addTab(RSATab(), "🔐 ПЗ-11: RSA (полная)")
        tabs.addTab(RSALibraryTab(), "🔐 ПЗ-12: RSA (библиотека)")

        layout.addWidget(tabs)
        self.apply_modern_style()

    def apply_modern_style(self):
        self.setStyleSheet("""
            QMainWindow {
                background-color: #f5f5f5;
            }
            QTabWidget::pane {
                border: 1px solid #c0c0c0;
                background-color: white;
            }
            QTabBar::tab {
                background-color: #e0e0e0;
                padding: 8px 16px;
                margin-right: 2px;
                border: 1px solid #c0c0c0;
                border-bottom: none;
                border-top-left-radius: 4px;
                border-top-right-radius: 4px;
                color: #333333;
            }
            QTabBar::tab:selected {
                background-color: white;
                border-bottom: 1px solid white;
                color: #333333;
            }
            QGroupBox {
                font-weight: bold;
                border: 1px solid #c0c0c0;
                border-radius: 5px;
                margin-top: 10px;
                padding-top: 10px;
                background-color: white;
                color: #333333;
            }
            QGroupBox::title {
                subcontrol-origin: margin;
                subcontrol-position: top center;
                padding: 0 5px;
                background-color: white;
                color: #333333;
            }
            QPushButton {
                background-color: #4CAF50;
                border: none;
                color: white;
                padding: 6px 12px;
                border-radius: 4px;
                font-weight: bold;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
            QPushButton:pressed {
                background-color: #3d8b40;
            }
            QTextEdit, QLineEdit, QSpinBox {
                border: 1px solid #c0c0c0;
                border-radius: 3px;
                padding: 4px;
                background-color: white;
                color: #333333;
            }
            QComboBox {
                border: 1px solid #c0c0c0;
                border-radius: 3px;
                padding: 4px;
                background-color: white;
                color: #333333;
            }
            QComboBox QAbstractItemView {
                border: 1px solid #c0c0c0;
                background-color: white;
                color: #333333;
                selection-background-color: #4CAF50;
                selection-color: white;
            }
            QComboBox::drop-down {
                subcontrol-origin: padding;
                subcontrol-position: top right;
                width: 20px;
                border-left-width: 1px;
                border-left-color: #c0c0c0;
                border-left-style: solid;
                border-top-right-radius: 3px;
                border-bottom-right-radius: 3px;
            }
            QComboBox::down-arrow {
                width: 12px;
                height: 12px;
            }
            QLabel {
                color: #333333;
                background-color: transparent;
            }
            QProgressBar {
                border: 1px solid #c0c0c0;
                border-radius: 3px;
                text-align: center;
                color: #333333;
                background-color: white;
            }
            QProgressBar::chunk {
                background-color: #4CAF50;
            }
            QSlider::groove:horizontal {
                border: 1px solid #c0c0c0;
                height: 6px;
                background: #e0e0e0;
                border-radius: 3px;
            }
            QSlider::handle:horizontal {
                background: #4CAF50;
                border: 1px solid #388E3C;
                width: 12px;
                border-radius: 6px;
            }
            QScrollArea {
                border: none;
                background-color: white;
            }
            QScrollBar:vertical {
                border: none;
                background-color: #f0f0f0;
                width: 12px;
                margin: 0px;
            }
            QScrollBar::handle:vertical {
                background-color: #c0c0c0;
                border-radius: 6px;
                min-height: 20px;
            }
            QScrollBar::handle:vertical:hover {
                background-color: #a0a0a0;
            }
            QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
                border: none;
                background: none;
            }
            /* Специфичные стили для левой панели RSATab */
            QWidget#left_panel_rsa {
                background-color: white;
            }
        """)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = CryptoSuite()
    window.show()
    sys.exit(app.exec())