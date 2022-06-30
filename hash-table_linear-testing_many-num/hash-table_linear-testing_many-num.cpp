#include<Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef int T;
typedef int hashTableIndex;
int hashTableSize;
T* hashTable;
bool* used;

hashTableIndex myhash(T data);
void insertData(T data, int* ArrIndex);
void deleteData(T data);
bool findData(T data);
int dist(hashTableIndex a, hashTableIndex b);
int maxnum = 10;


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int i, insert;
    //cout << "Введите количество элементов maxnum : ";
    ////cin >> maxnum;

    cout << "Введите размер хеш-таблицы : ";
    cin >> hashTableSize;

    int* ArrIndex = new int[hashTableSize];
    vector <int>znach;
    for (int i = 0; i < hashTableSize; i++)
        ArrIndex[i] = 0;
    int* a = new int[maxnum];
    hashTable = new T[hashTableSize];
    used = new bool[hashTableSize];
    fstream out;
    for (i = 0; i < hashTableSize; i++) {
        hashTable[i] = 0;
        used[i] = false;
    }

    for (insert = 0; insert < 10; insert++)
    {
        for (i = 0; i < maxnum; i++)
        {
            a[i] = rand()/*%1000+1*/;
            znach.push_back(a[i]);
        }

        for (i = 0; i < maxnum; i++)
            insertData(a[i], ArrIndex);

        /*for (i = maxnum - 1; i >= 0; i--)
            findData(a[i]);*/

        out.open("HashTable.txt");
        for (i = 0; i < hashTableSize; i++)
        {
            out << i << "  :  " << used[i] << " : " << hashTable[i] << endl;
        }
        out.close();
        cout << "\n" << insert + 1 << ") Обращения к индексу для " << maxnum << " вставок: " << endl;
        for (int i = 0; i < hashTableSize; i++)
            cout << ArrIndex[i] << " ";
        for (i = 0; i < hashTableSize; i++)
            ArrIndex[i] = 0;
    }
    //fstream out; out.open("List.txt");
    //    out << "Первая вставка:" << endl;
    //    for (i = 0; i < znach.size(); i++) {
    //        out << znach[i] << " ";
    //        /*if (i < maxnum - 1) out << "\t";*/
    //    }
    //    out.close();
    cout << "\n" << "Массив значений: " << endl;
    for (i = 0; i < znach.size(); i++) {
        cout << znach[i] << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}

// хеш-функция размещения величины
hashTableIndex myhash(T data) {
    return (data % hashTableSize);
}

void insertData(T data, int* ArrIndex) {
    hashTableIndex index;
    index = myhash(data);
    while (used[index] && hashTable[index] != data)
    {
        ArrIndex[index] += 1;
        index = (index + 1) % hashTableSize;

    }
    if (!used[index]) {
        used[index] = true;
        hashTable[index] = data;
        ArrIndex[index] += 1;
    }
}

// функция поиска величины, равной data
bool findData(T data) {
    hashTableIndex index;
    index = myhash(data);
    while (used[index] && hashTable[index] != data)
        index = (index + 1) % hashTableSize;
    return used[index] && hashTable[index] == data;
}

//функция удаления величины из таблицы
void deleteData(T data) {
    int index, gap;
    index = myhash(data);
    while (used[index] && hashTable[index] != data)
        index = (index + 1) % hashTableSize;
    if (used[index] && hashTable[index] == data) {
        used[index] = false;
        gap = index;
        index = (index + 1) % hashTableSize;
        while (used[index]) {
            if (index == myhash(hashTable[index]))
                index = (index + 1) % hashTableSize;
            else if (dist(myhash(hashTable[index]), index) < dist(gap, index))
                index = (index + 1) % hashTableSize;
            else {
                used[gap] = true;
                hashTable[gap] = hashTable[index];
                used[index] = false;
                gap = index;
                index++;
            }
        }
    }
}

// функция вычисления расстояние от a до b (по часовой стрелке, слева направо) 
int dist(hashTableIndex a, hashTableIndex b) {
    return (b - a + hashTableSize) % hashTableSize;
}