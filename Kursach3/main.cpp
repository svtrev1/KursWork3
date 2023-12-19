#include <iostream>
#include <list>
#include <utility>

using namespace std;
template <typename K, typename V>
class HashTable {

private:
    
    static const int tableSize = 500; // Размер хеш-таблицы
    
    list<pair<K, V>> table[tableSize]; // Массив для хранения пар ключ-значение
    
public:
    
    int hashFunction(int key)
    {
        return key % tableSize; // Простая хеш-функция (остаток от деления)
    }
    int hashFunction(string key)
    {
        char * s = const_cast<char*>(key.c_str());
        int h = 0, a = 127;
        for (int i = 0; i < key.length() / 2; i++)
            h = (a * h + s[i]) % tableSize;
        return abs(h);
    }
    int hashFunction(double key)
    {
        long long intKey = *(long long *)&key; // Преобразуем double в long long (64 бита)
        int h = (int)(intKey % tableSize);
        return h; // Используем остаток от деления в качестве хеша
    }

    void insertItem(K key, V value)
    {
        int index = hashFunction(key);
        for (auto& pair : table[index]) 
        {
            if (pair.first == key)
            {
                pair.second = value; // Обновление значения, так как ключ уже существует
                return;
            }
        }
        table[index].push_back(make_pair(key, value));
    }

    void removeItem(K key) 
    {
        int index = hashFunction(key);
        list<pair<K, V>>& temp = table[index];

        for (auto it = temp.begin(); it != temp.end(); it++) {
            if (it->first == key) {
                temp.erase(it);
                break;
            }
        }
    }

    V searchItem(K key) {
        int index = hashFunction(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        cout << "Key not found";
        V A;
        return A;
    }
    
    void printTable()
    {
        for (int i = 0; i < tableSize; i++)
        {
            for (const auto &pair : table[i])
            {
                cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
            }
        }
    }
};
template <typename K, typename V>
class Dictionary {
private:
    HashTable<K, V> hashTable; // Используем нашу реализацию хеш-таблицы как часть словаря

public:
    void insertItem(K key, V value) 
    {
        hashTable.insertItem(key, value);
    }

    void removeItem(K key) 
    {
        hashTable.removeItem(key);
    }

    V searchItem(K key)
    {
        return hashTable.searchItem(key);
    }

    void printDictionary() 
    {
        hashTable.printTable();
    }

    
};

int main() 
{
    Dictionary<int, string> IntString;

    IntString.insertItem(1, "A");
    IntString.insertItem(2, "B");
    IntString.insertItem(3, "C");
    IntString.insertItem(4, "D");
    IntString.insertItem(2, "B2");
    
    cout << "IntString before remove:" << endl;
    IntString.printDictionary();
    
    cout << endl;
    
    cout << "Element with key 89: " << IntString.searchItem(89) << endl;
    
    cout << "Element with key 3: " << IntString.searchItem(3) << endl;
    IntString.removeItem(3);

    cout << endl;

    cout << "IntString after remove:" << endl;
    IntString.printDictionary();

    cout << endl;
    cout << endl;
    cout << endl;
    
    
    
    Dictionary<double, double> IntDouble;

    IntDouble.insertItem(1.1, 3.27);
    IntDouble.insertItem(2.12, 10.28);
    IntDouble.insertItem(3.13, 5.00);
    IntDouble.insertItem(4.15, 4.63);
    
    cout << "IntDouble before remove:" << endl;
    IntDouble.printDictionary();
    
    cout << endl;
    
    cout << "Element with key 78: " << IntDouble.searchItem(78) << endl;
    cout << "Element with key 3: " << IntDouble.searchItem(3.13) << endl;
    IntDouble.removeItem(3);

    cout << endl;

    cout << "IntDouble after remove:" << endl;
    IntDouble.printDictionary();

    cout << endl;
    cout << endl;
    cout << endl;
    
    Dictionary<string, double> StringDouble;

    StringDouble.insertItem("Владимир", 3.27);
    StringDouble.insertItem("Родион", 10.28);
    StringDouble.insertItem("Евгений", 5.00);
    StringDouble.insertItem("Илоночка", 4.63);
    
    cout << "StringDouble before remove:" << endl;
    StringDouble.printDictionary();
    
    cout << endl;
    
    cout << "Element with key Лолошка: " << StringDouble.searchItem("Лолошка") << endl;
    cout << "Element with key Евгений: " << StringDouble.searchItem("Евгений") << endl;
    StringDouble.removeItem("Евгений");

    cout << endl;

    cout << "StringDouble after remove:" << endl;
    StringDouble.printDictionary();

    cout << endl;
    cout << endl;
    cout << endl;
    
    Dictionary<string, string> StringString;

    StringString.insertItem("Привет", "Hello");
    StringString.insertItem("Пока", "By");
    StringString.insertItem("Как дела?", "How are you?");
    StringString.insertItem("Сколько тебе лет?", "How old are you?");
    
    cout << "StringString before remove:" << endl;
    StringString.printDictionary();
    
    cout << endl;
    
    cout << "Element with key Нет, Value: " << StringString.searchItem("Нет") << endl;
    cout << "Element with key Пока, Value: " << StringString.searchItem("Пока") << endl;
    StringString.removeItem("Пока");

    cout << endl;

    cout << "StringString after remove:" << endl;
    StringString.printDictionary();

    cout << endl;
    cout << endl;
    cout << endl;
    
    return 0;
}
