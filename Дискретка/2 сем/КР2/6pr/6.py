import math
import random


def sieve_of_eratosthenes(limit):
    sieve = [True] * (limit + 1)
    sieve[0:2] = [False, False]
    for current in range(2, int(math.sqrt(limit)) + 1):
        if sieve[current]:
            for multiple in range(current * current, limit + 1, current):
                sieve[multiple] = False
    return [i for i, is_prime in enumerate(sieve) if is_prime]


def fermat_factorization(n):
    if n <= 1:
        return None, None
    if n % 2 == 0:
        return 2, n // 2

    for q in range(1, (n - 1) // 2 + 1):
        value = n + q * q
        p = math.isqrt(value)
        if p * p == value:
            factor1 = p - q
            factor2 = p + q
            if factor1 > 1 and factor2 > 1:
                return factor1, factor2

    m = math.isqrt(n)
    if m * m < n:
        m += 1

    for p in range(m, (n + 1) // 2 + 1):
        value = p * p - n
        q = math.isqrt(value)
        if q * q == value:
            factor1 = p - q
            factor2 = p + q
            if factor1 > 1 and factor2 > 1:
                return factor1, factor2

    return None, None


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


def jacobi_symbol(a, n):
    if n <= 0 or n % 2 == 0:
        return 0
    a = a % n
    result = 1
    while a != 0:
        while a % 2 == 0:
            a //= 2
            if n % 8 in [3, 5]:
                result = -result
        a, n = n, a
        if a % 4 == 3 and n % 4 == 3:
            result = -result
        a = a % n
    return result if n == 1 else 0


def solovay_strassen_test(p, iterations=5, log_filename=None):
    if p < 2:
        return False
    if p != 2 and p % 2 == 0:
        return False

    log_entries = []
    log_entries.append(f"Тест Соловея-Штрассена для числа p = {p}")
    log_entries.append(f"Количество итераций: {iterations}")
    log_entries.append("=" * 50)

    for i in range(iterations):
        log_entries.append(f"Итерация {i + 1}:")
        a = random.randrange(2, p)
        log_entries.append(f"  Выбрано случайное a = {a}")

        gcd_val = gcd(a, p)
        log_entries.append(f"  НОД(a, p) = НОД({a}, {p}) = {gcd_val}")
        if gcd_val != 1:
            log_entries.append(f"  Число p не простое (НОД ≠ 1)")
            if log_filename:
                with open(log_filename, 'w', encoding='utf-8') as f:
                    f.write("\n".join(log_entries))
            return False

        j = pow(a, (p - 1) // 2, p)
        log_entries.append(f"  j = a^((p-1)/2) mod p = {a}^({(p - 1) // 2}) mod {p} = {j}")

        J = jacobi_symbol(a, p)
        log_entries.append(f"  Символ Якоби J(a, p) = J({a}, {p}) = {J}")

        if j != J:
            log_entries.append(f"  j ≠ J, число p определенно не простое")
            if log_filename:
                with open(log_filename, 'w', encoding='utf-8') as f:
                    f.write("\n".join(log_entries))
            return False

        log_entries.append(f"  j = J, число p может быть простым (вероятность ≤ 50%)")
        log_entries.append("-" * 30)

    log_entries.append(f"Число p прошло все {iterations} итераций теста")
    if log_filename:
        with open(log_filename, 'w', encoding='utf-8') as f:
            f.write("\n".join(log_entries))

    return True


def lehmann_test(p, iterations=5, log_filename=None):
    if p < 2:
        return False
    if p != 2 and p % 2 == 0:
        return False

    log_entries = []
    log_entries.append(f"Тест Леманна для числа p = {p}")
    log_entries.append(f"Количество итераций: {iterations}")
    log_entries.append("=" * 50)

    flag = False
    for i in range(iterations):
        log_entries.append(f"Итерация {i + 1}:")
        a = random.randrange(2, p)
        log_entries.append(f"  Выбрано случайное a = {a}")

        exp = pow(a, (p - 1) // 2, p)
        log_entries.append(f"  a^((p-1)/2) mod p = {a}^({(p - 1) // 2}) mod {p} = {exp}")

        if exp != 1 and exp != p - 1:
            log_entries.append(f"  Результат ≠ 1 и ≠ -1, число p определенно не простое")
            if log_filename:
                with open(log_filename, 'w', encoding='utf-8') as f:
                    f.write("\n".join(log_entries))
            return False

        if exp == p - 1:
            flag = True
            log_entries.append(f"  Результат = -1, установлен флаг")

        log_entries.append(f"  Вероятность того, что p не простое, не превышает 50%")
        log_entries.append("-" * 30)

    if flag:
        log_entries.append(f"Число p прошло все {iterations} итераций теста")
    else:
        log_entries.append(f"Число p не прошло тест (все результаты = 1)")

    if log_filename:
        with open(log_filename, 'w', encoding='utf-8') as f:
            f.write("\n".join(log_entries))

    return flag


def rabin_miller_test(n, iterations=5, log_filename=None):
    if n < 2:
        return False
    if n != 2 and n % 2 == 0:
        return False
    if n == 3:
        return True

    log_entries = []
    log_entries.append(f"Тест Рабина-Миллера для числа n = {n}")
    log_entries.append(f"Количество итераций: {iterations}")
    log_entries.append("=" * 50)

    m = n - 1
    b = 0
    while m % 2 == 0:
        m //= 2
        b += 1

    log_entries.append(f"n-1 = {n - 1} = 2^{b} * {m}")
    log_entries.append(f"b = {b}, m = {m}")
    log_entries.append("")

    for i in range(iterations):
        log_entries.append(f"Итерация {i + 1}:")
        a = random.randrange(2, n - 1)
        log_entries.append(f"  Выбрано случайное a = {a}")

        j = 0
        z = pow(a, m, n)
        log_entries.append(f"  j = {j}, z = a^m mod n = {a}^{m} mod {n} = {z}")

        if z == 1 or z == n - 1:
            log_entries.append(f"  z = 1 или z = n-1, число проходит тест")
            log_entries.append("-" * 30)
            continue

        composite = True

        for j_val in range(1, b):
            log_entries.append(f"  j = {j_val}:")
            z = pow(z, 2, n)
            log_entries.append(f"    z = z^2 mod n = {z}")

            if z == n - 1:
                log_entries.append(f"    z = n-1, число проходит тест")
                composite = False
                break
            if z == 1:
                log_entries.append(f"    z = 1, число не простое")
                if log_filename:
                    with open(log_filename, 'w', encoding='utf-8') as f:
                        f.write("\n".join(log_entries))
                return False

        if composite:
            log_entries.append(f"  После всех j, z ≠ n-1, число не простое")
            if log_filename:
                with open(log_filename, 'w', encoding='utf-8') as f:
                    f.write("\n".join(log_entries))
            return False

        log_entries.append("-" * 30)

    log_entries.append(f"Число n прошло все {iterations} итераций теста")
    if log_filename:
        with open(log_filename, 'w', encoding='utf-8') as f:
            f.write("\n".join(log_entries))

    return True


def direct_primality_check(n):
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        if n % i == 0:
            return False
    return True


if __name__ == "__main__":
    print("1. Решето Эратосфена для чисел < 256: ")
    primes = sieve_of_eratosthenes(255)
    print(primes)

    with open(f"eratosthenes_sieve.txt", 'w', encoding='utf-8') as f:
        f.write("Простые числа < 256:\n")
        f.write(", ".join(map(str, primes)))

    print("\n2. Метод Ферма для проверки и разложения (введите ваши числа через пробел): ")
    test_numbers = [int(i) for i in input().split()]

    fermat_results = []
    for num in test_numbers:
        factor1, factor2 = fermat_factorization(num)
        if factor1 is None:
            result = f"{num} - простое число"
            fermat_results.append(result)
            print(result)
        else:
            result = f"{num} = {factor1} * {factor2}"
            fermat_results.append(result)
            print(result)

    with open(f"fermat_factorization.txt", 'w', encoding='utf-8') as f:
        f.write("Метод Ферма для проверки и разложения:\n")
        f.write("\n".join(fermat_results))

    print("\n3. Тесты на простоту для больших чисел (введите ваши числа через пробел): ")
    test_numbers = [int(i) for i in input().split()]
    iters = int(input("Введите количество итераций для тестов: "))
    print("\n" + "=" * 60)

    for num in test_numbers:
        print(f"\nТесты для числа {num}:")

        ss_filename = f"solovay_strassen_{num}.txt"
        ss_result = solovay_strassen_test(num, iters, ss_filename)
        print(f"Тест Соловея-Штрассена: {ss_result} (подробности в файле {ss_filename})")

        lehmann_filename = f"lehmann_{num}.txt"
        lehmann_result = lehmann_test(num, iters, lehmann_filename)
        print(f"Тест Леманна: {lehmann_result} (подробности в файле {lehmann_filename})")

        rm_filename = f"rabin_miller_{num}.txt"
        rm_result = rabin_miller_test(num, iters, rm_filename)
        print(f"Тест Рабина-Миллера: {rm_result} (подробности в файле {rm_filename})")

        direct_result = direct_primality_check(num)
        print(f"Непосредственная проверка: {direct_result}")

        print("=" * 60)