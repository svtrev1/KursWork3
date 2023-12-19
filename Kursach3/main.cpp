#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <typeinfo>
#include <sstream>
//#include <cmath>

using namespace std;
template <typename K, typename V>
class HashTable {

private:
    
    int tableSize; // Размер хеш-таблицы
    static const int initialSize = 7; // Начальный размер таблицы
    static const int resizeFactor = 2; // Коэффициент увеличения размера таблицы

    list<pair<K, V>>* table; // Массив для хранения пар ключ-значение
    int numElements; // Количество элементов в таблице
public:
    HashTable()
    {
        tableSize = initialSize;
        table = new list<pair<K,V>>[tableSize]();
        numElements = 0;
    }
    int hashFunction(K key) // Общая хеш-функция
    {
        string temp;
        if (typeid(key).name()[0] == 'S')
            temp = key;
        else
        {
            key = key * 53;
            stringstream ss;
            ss << key;
            temp = ss.str();
        }
        char * s = const_cast<char*>(temp.c_str());
        int h = 0, a = 127;
        cout << "tableSize: " << tableSize << endl;
        for (int i = 0; i < temp.length(); i++)
            h = (a * h + s[i]) % tableSize;
        return abs(h);
    }

    void insertItem(K key, V value) // Вставка элемента
    {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 1; // Используем простое линейное пробирование для поиска следующей позиции

        while (table[index].size() > 0 && table[index].front().first != key) 
        {
            index = (originalIndex + i) % tableSize; // Линейное пробирование
            i++;
            if (index == originalIndex) {
                resizeTable(); // Если пробежали всю таблицу, увеличиваем ее размер
                index = hashFunction(key); // Снова получаем хеш для ключа
            }
        }

        if (table[index].size() == 0)
            numElements++; // Увеличиваем количество элементов только если вставляем новый элемент
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
    
    void printTable() 
    {
            for (int i = 0; i < tableSize; ++i)
            {
                std::cout << "Bucket [" << i << "]: ";
                for (const auto& pair : table[i]) 
                {
                    std::cout << "{" << pair.first << ": " << pair.second << "}";
                }
                std::cout << std::endl;
            }
        }


    void removeItem(K key) // Удаление элемента по ключу
    {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                numElements--;
                break;
            }
        }

    }
    
    void resizeTable() 
    {
        int newSize = tableSize * resizeFactor; // Увеличиваем размер таблицы
        list<std::pair<K, V>>* newTable = new list<pair<K, V>>[newSize](); // Создаем новую (большую) таблицу

        for (int i = 0; i < tableSize; ++i)
        {
            for (const auto& pair : table[i]) 
            {
                int index = hashFunction(pair.first) % newSize; // Перехешируем все существующие элементы в новую таблицу
                newTable[index].push_back(pair);
            }
        }

        delete[] table; // Удаляем старую таблицу
        table = newTable;
        tableSize = newSize;
    }


    void searchItem(K key) // Нахождение элемента по ключу
    {
        bool check = true;
        int index = hashFunction(key);
        for (const auto& pair : table[index]) 
        {
            if (pair.first == key)
            {
                check = false;
                cout << pair.second; // Если нашелся, выводит значение ключа
                break;
            }
        }
        if (check)
            cout << "Key not found"; // Если не нашелся
    }
    
    void printingTable() // Вывод словаря
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

    void searchItem(K key)
    {
        hashTable.searchItem(key);
    }

    void printDictionary() 
    {
        hashTable.printTable();
    }
    
    void printing()
    {
        hashTable.printingTable();
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
    IntString.printDictionary();
    IntString.insertItem(6, "Lol");
    IntString.printDictionary();
    IntString.insertItem(7, "Pop");
    IntString.printDictionary();
    IntString.insertItem(8, "Pup");
    IntString.printDictionary();
    IntString.insertItem(91, "Love");
    IntString.printDictionary();
    IntString.insertItem(88, "88");
    IntString.printDictionary();
//    IntString.printing();
//    cout << "Element with key 3: ";
//    IntString.searchItem(8);
//    cout << endl;
//    IntString.removeItem(8);
//    IntString.printDictionary();
//    cout << "IntString before remove:" << endl;
//    IntString.printDictionary();
//    
//    cout << endl;
//    
//    cout << "Element with key 89: ";
//    IntString.searchItem(89);
//    cout << endl;
//    
//    cout << "Element with key 3: ";
//    IntString.searchItem(3);
//    cout << endl;
//    IntString.removeItem(3);
//
//    cout << endl;
//
//    cout << "IntString after remove:" << endl;
//    IntString.printDictionary();
//
//    cout << endl;
//    cout << endl;
//    cout << endl;
    
    
    
//    Dictionary<double, double> DoubleDouble;
//
//    DoubleDouble.insertItem(1.1, 3.43);
//    DoubleDouble.insertItem(2.12, 10.28);
//    DoubleDouble.insertItem(3.13, 5.00);
//    DoubleDouble.insertItem(4.15, 4.63);
//    
//    cout << "IntDouble before remove:" << endl;
//    DoubleDouble.printDictionary();
//    
//    cout << endl;
//    
//    cout << "Element with key 78: ";
//    DoubleDouble.searchItem(78);
//    cout << endl;
//    cout << "Element with key 3.13: ";
//    DoubleDouble.searchItem(3.13);
//    cout << endl;
//    DoubleDouble.removeItem(3.13);
//
//    cout << endl;
//
//    cout << "IntDouble after remove:" << endl;
//    DoubleDouble.printDictionary();
//
//    cout << endl;
//    cout << endl;
//    cout << endl;
//    
//    Dictionary<string, double> StringDouble;
//
//    StringDouble.insertItem("Владимир", 3.27);
//    StringDouble.insertItem("Родион", 10.28);
//    StringDouble.insertItem("Евгений", 5.00);
//    StringDouble.insertItem("Илоночка", 4.63);
//    
//    cout << "StringDouble before remove:" << endl;
//    StringDouble.printDictionary();
//    
//    cout << endl;
//    
//    cout << "Element with key Лолошка: ";
//    StringDouble.searchItem("Лолошка");
//    cout << endl;
//    cout << "Element with key Евгений: ";
//    StringDouble.searchItem("Евгений");
//    cout << endl;
//    StringDouble.removeItem("Евгений");
//
//    cout << endl;
//
//    cout << "StringDouble after remove:" << endl;
//    StringDouble.printDictionary();
//
//    cout << endl;
//    cout << endl;
//    cout << endl;
//    
//    Dictionary<string, string> StringString;
//
//    StringString.insertItem("Привет", "Hello");
//    StringString.insertItem("Пока", "By");
//    StringString.insertItem("Как дела?", "How are you?");
//    StringString.insertItem("Сколько тебе лет?", "How old are you?");
//    
//    cout << "StringString before remove:" << endl;
//    StringString.printDictionary();
//    
//    cout << endl;
//    
//    cout << "Element with key Нет, Value: ";
//    StringString.searchItem("Нет");
//    cout << endl;
//    cout << "Element with key Пока, Value: ";
//    StringString.searchItem("Пока");
//    cout << endl;
//    StringString.removeItem("Пока");
//
//    cout << endl;
//
//    cout << "StringString after remove:" << endl;
//    StringString.printDictionary();
//
//    cout << endl;
//    cout << endl;
//    cout << endl;
    
    return 0;
}
