#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Node{
public:
    int id;
    Node (int idshnik){
        id = idshnik;
    }

    void get(string keyWord){
        if (key != ""){
            if (key == keyWord and value != ""){
                cout << value << " ";
            }
            nextnode->get(keyWord);
        } else {
            cout << endl;
        }
    }

    void set(string newKey, string newValue){
        if (key == ""){
            key = newKey;
            value = newValue;
            nextnode = new Node(id + 1);
        } else {
            nextnode->set(newKey, newValue);
        }
    }

    void deleteKV(string keyWord, string valueWord){
        if (key != ""){
            if (key == keyWord and value == valueWord){
                value = "";
            }
            nextnode->deleteKV(keyWord, valueWord);
        }
    }
private:
    string key = "";
    string value = "";
    Node *nextnode;
};

class Hash_table{
public:
    Hash_table(unsigned length){
        sizeOfHash = length;
        createHashMap(length);
    }
    
    void get(string key){
        unsigned hashId = hashing(key);
        hashTable[hashId].get(key);

    }

    void set(string key, string value){
        unsigned hashId = hashing(key);
        hashTable[hashId].set(key, value);
    }

    void deleteKZ(string key, string value){
        unsigned hashId = hashing(key);
        hashTable[hashId].deleteKV(key, value);
    }
private:
    unsigned sizeOfHash;
    vector<Node> hashTable;

    void createHashMap(unsigned length){
        for (unsigned i = 0; i < length; i ++){
            Node *node = new Node(0);
            hashTable.push_back(*node);
        }
    }

    unsigned hashing(string key){
        unsigned returnHashId = 0;
        for (int i = 0; i < key.length(); i ++){
            returnHashId += (int) key[i];
        }
        return returnHashId;
    }
};

void chistka(string &line){
    while (line.find("\"") != string::npos){
        int x = line.find("\"");
        line.erase(x, 1);
    }
    while (line.find("\\") != string::npos){
        int x = line.find("\\");
        line.erase(x, 1);
    }
}

void sozd(Hash_table &hash){
    string line;
    ifstream text("contactBook.json");
    int i = 0;
    if (text.is_open()){
        while (getline(text, line)){
            string key;
            if(line.find("\": ") != string::npos and line.find("[") == string::npos){
                int start = line.find("\": ") + 3;
                while(start != line.length() - 1 and line[start] != ','){
                    key += line[start];
                    start ++;
                }
                chistka(key);
                getline(text, line);
                string value;
                start = line.find("\": ") + 4;
                while(start != line.length() - 1){
                    value += line[start];
                    start ++;
                }
                hash.set(key, value);
            }
        }
    }
}

void operation(Hash_table &hash){
    int operation;
    cout << "\nКакую операцию вы хотите сделать?\n1) Добавить ключ-значений в таблицу\n2) Найти значение по ключу\n3) Удалить ключ-значение\nНапишите цифру операции: ";
    cin >> operation;
    if (operation == 1)
    {
        int typeOfData;
        string value;
        cout << "Какого типа будет ключ?\n1) Int\n2) String\nНапишите цифру типа данных: ";
        cin >> typeOfData;
        cout << "Введите ключ: ";
        if (typeOfData == 1){
            int key;
            cin >> key;
            cout << "Введите значение: ";
            while(value.length() == 0){
                getline(cin, value);
            }
            hash.set(to_string(key), value);
        } else if (typeOfData == 2) {
            string keyString;
            while(keyString.length() == 0){
                getline(cin, keyString);
            }
            cout << "Введите значение: ";
            while(value.length() == 0){
                getline(cin, value);
            }
            hash.set(keyString, value);
        }
    } else if (operation == 2) {
        int typeOfData;
        cout << "Какого типа будет ключ?\n1) Int\n2) String\nНапишите цифру типа данных: ";
        cin >> typeOfData;
        if (typeOfData == 1){
            int key;
            cout << "Введите ключ: ";
            cin >> key;
            hash.get(to_string(key));
        } else if (typeOfData == 2) {
            string keyString;
            cout << "Введите ключ: ";
            while(keyString.length() == 0){
                getline(cin, keyString);
            }
            hash.get(keyString);
        }
    } else if (operation == 3) {
        int typeOfData;
        string value;
        cout << "Какого типа будет ключ?\n1) Int\n2) String\nНапишите цифру типа данных: ";
        cin >> typeOfData;
        cout << "Введите ключ: ";
        if (typeOfData == 1){
            int key;
            cin >> key;
            cout << "Введите значение: ";
            while(value.length() == 0){
                getline(cin, value);
            }
            hash.deleteKZ(to_string(key), value);
        } else if (typeOfData == 2) {
            string keyString;
            while(keyString.length() == 0){
                getline(cin, keyString);
            }
            cout << "Введите значение: ";
            while(value.length() == 0){
                getline(cin, value);
            }
            hash.deleteKZ(keyString, value);
        }
    }
}

int main(){
    Hash_table hash(128);
    int table;
    cout << "С какой таблицей будет работа?\n1) Работать с пустой таблицей\n2) Создать из JSON-файла\nНапишите цифру: ";
    cin >> table;
    if (table == 2){
        sozd(hash);
    }
    while (true){
        operation(hash);
    }
    return 0;
}