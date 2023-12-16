#include <iostream>
#include <list>

using namespace std;

class HashTable {

public: 
    
    static const int tableSize = 10; // Размер хеш-таблицы
    list<pair<int, string>> table[tableSize]; // Массив для хранения пар ключ-значение
    
private:
    int hashFunction(int key)
    {
        return key % tableSize; // Простая хеш-функция (остаток от деления)
    }

public:
    
    void insertItem(int key, string value)
    {
        int index = hashFunction(key);
        table[index].push_back(make_pair(key, value));
    }

    void removeItem(int key) {
        int index = hashFunction(key);
       list<pair<int, string>>& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                break;
            }
        }
    }

    string searchItem(int key) {
        int index = hashFunction(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return "Key not found";
    }
};

class Dictionary {
private:
    HashTable hashTable; // Используем нашу реализацию хеш-таблицы как часть словаря

public:
    void insertItem(int key, string value) {
        hashTable.insertItem(key, value);
    }

    void removeItem(int key) {
        hashTable.removeItem(key);
    }

    string searchItem(int key) {
        return hashTable.searchItem(key);
    }

    void printDictionary() {
        for (int i = 0; i < HashTable::tableSize; ++i) {
            for (const auto& pair : hashTable.table[i]) {
                cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
            }
        }
    }

    bool containsKey(int key) {
        string result = hashTable.searchItem(key);
        return result != "Key not found";
    }
};

int main() {
    Dictionary myDictionary;

    // Добавление элементов
    myDictionary.insertItem(1, "Apple");
    myDictionary.insertItem(2, "Banana");
    myDictionary.insertItem(3, "Cherry");
    myDictionary.insertItem(4, "Date");

    // Поиск элемента
    cout << "Element with key 2: " << myDictionary.searchItem(7) << endl;

    // Удаление элемента
    myDictionary.removeItem(3);

    // Проверка наличия элемента
    cout << "Contains key 3: " << (myDictionary.containsKey(3) ? "Yes" : "No") << endl;

    // Распечатать все элементы
    cout << "Dictionary contents:" << endl;
    myDictionary.printDictionary();

    return 0;
}
