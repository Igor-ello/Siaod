#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <set>
#include <chrono>
#include <string.h>

using namespace std;

// Структура записи
struct Record {
    int cityCode; // Код города
    char cityName[30]; // Название города
};

// Структура индекса
struct IndexEntry {
    int cityCode;  // Код города (ключ)
    streampos filePos;  // Смещение записи в файле
};

// Функция для генерации данных
void generateData(int recordCount, vector<Record>& records) {
    random_device rd;
    mt19937 gen(rd());

    // Генерация случайных уникальных кодов городов
    uniform_int_distribution<> codeDist(0, 9999);
    set<int> uniqueNumbers;  // Множество для хранения уникальных кодов

    // Генерация случайных уникальных названий городов
    vector<string> baseCityNames = {"Alpha", "Beta", "Gamma", "Delta", "Omega", "Zeta", "Sigma", "Theta", "Iota", "Kappa"};
    uniform_int_distribution<> nameDist(0, 999);

    set<string> uniqueCityNames;  // Множество для уникальных названий городов

    while (uniqueNumbers.size() < recordCount) {
        int newCode = codeDist(gen);  // Генерация случайного уникального кода
        int nameIndex = rand() % baseCityNames.size();  // Выбор случайного базового названия города
        int suffix = nameDist(gen);  // Генерация случайного суффикса для уникальности

        string newCityName = baseCityNames[nameIndex] + to_string(suffix);  // Формирование уникального названия города

        // Проверка на уникальность как кода, так и названия
        if (uniqueNumbers.insert(newCode).second && uniqueCityNames.insert(newCityName).second) {
            Record rec;
            rec.cityCode = newCode;  // Присвоение уникального кода
            strncpy(rec.cityName, newCityName.c_str(), sizeof(rec.cityName));  // Присвоение уникального названия
            records.push_back(rec);  // Добавление записи в вектор
        }
    }
}

// Функция для записи данных в текстовый файл
void writeTextFile(const string& filename, const vector<Record>& records) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка при открытии файла " << filename << endl;
        return;
    }

    for (const auto& rec : records) {
        outFile << rec.cityCode << "\t" << rec.cityName << endl;
    }
    outFile.close();
}

// Функция конвертации текстового файла в бинарный
void convertToBinary(const string& textFilename, const string& binaryFilename) {
    ifstream inFile(textFilename);
    ofstream outFile(binaryFilename, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Ошибка при открытии файлов" << endl;
        return;
    }

    Record rec;
    while (inFile >> rec.cityCode) {
        inFile.ignore();
        inFile.getline(rec.cityName, sizeof(rec.cityName));
        outFile.write(reinterpret_cast<char*>(&rec), sizeof(Record));
    }

    inFile.close();
    outFile.close();
}

// Функция для записи данных в бинарный файл
void writeBinaryFile(const string& filename, const vector<Record>& records) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Ошибка при открытии файла " << filename << endl;
        return;
    }
    for (const auto& rec : records) {
        outFile.write(reinterpret_cast<const char*>(&rec), sizeof(Record));
    }
    outFile.close();
}

// Функция для линейного поиска
bool linearSearchInFile(const string& binaryFilename, int searchKey, Record& foundRecord) {
    ifstream inFile(binaryFilename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка при открытии файла " << binaryFilename << endl;
        return false;
    }

    Record rec;
    while (inFile.read(reinterpret_cast<char*>(&rec), sizeof(Record))) {
        if (rec.cityCode == searchKey) {
            foundRecord = rec;
            inFile.close();
            return true; // Запись найдена
        }
    }

    inFile.close();
    return false; // Запись не найдена
}

// Функция для поиска записи с использованием бинарного поиска
bool fibonacciSearchInFile(const string& binaryFilename, int searchKey, Record& foundRecord) {
    ifstream inFile(binaryFilename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка при открытии файла " << binaryFilename << endl;
        return false;
    }

    vector<Record> records;
    Record rec;
    while (inFile.read(reinterpret_cast<char*>(&rec), sizeof(Record))) {
        records.push_back(rec);
    }

    int n = records.size();

    int fibMMm2 = 0;  // (m-2)'th Fibonacci No.
    int fibMMm1 = 1;  // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1;  // m'th Fibonacci

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (records[i].cityCode < searchKey) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (records[i].cityCode > searchKey) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            foundRecord = records[i];
            return true;
        }
    }

    if (fibMMm1 && records[offset + 1].cityCode == searchKey) {
        foundRecord = records[offset + 1];
        return true;
    }

    return false;
}

// Функция для сравнения записей по коду города
bool compareRecords(const Record& a, const Record& b) {
    return a.cityCode < b.cityCode;
}

// Функция для создания индексной таблицы
void createIndexTable(const string& binaryFilename, vector<IndexEntry>& indexTable) {
    ifstream inFile(binaryFilename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка при открытии файла " << binaryFilename << endl;
        return;
    }

    Record rec;
    while (inFile.read(reinterpret_cast<char*>(&rec), sizeof(Record))) {
        IndexEntry entry;
        entry.cityCode = rec.cityCode;
        entry.filePos = inFile.tellg() - static_cast<streampos>(sizeof(Record));  // Позиция записи
        indexTable.push_back(entry);
    }
    inFile.close();
}

// Функция для поиска смещения записи по ключу с использованием Фибоначчи
bool fibonacciSearchInIndexTable(const vector<IndexEntry>& indexTable, int searchKey, streampos& filePos) {
    int n = indexTable.size();

    int fibMMm2 = 0;  // (m-2)'е число Фибоначчи
    int fibMMm1 = 1;  // (m-1)'е число Фибоначчи
    int fibM = fibMMm2 + fibMMm1;  // m'е число Фибоначчи

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (indexTable[i].cityCode < searchKey) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (indexTable[i].cityCode > searchKey) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            filePos = indexTable[i].filePos;
            return true;
        }
    }

    if (fibMMm1 && indexTable[offset + 1].cityCode == searchKey) {
        filePos = indexTable[offset + 1].filePos;
        return true;
    }

    return false;
}

// Функция для чтения записи из бинарного файла по смещению
bool readRecordAtPosition(const string& binaryFilename, streampos filePos, Record& foundRecord) {
    ifstream inFile(binaryFilename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка при открытии файла " << binaryFilename << endl;
        return false;
    }

    inFile.seekg(filePos);  // Перемещаем указатель файла на заданное смещение
    inFile.read(reinterpret_cast<char*>(&foundRecord), sizeof(Record));
    inFile.close();

    return true;
}


// Функция для сравнения записей по коду города (для сортировки)
bool compareIndexEntries(const IndexEntry& a, const IndexEntry& b) {
    return a.cityCode < b.cityCode;
}


// ДЛЯ 1
// // Основная функция программы
// int main() {
//     vector<Record> records;
//     generateData(100, records);
//
//     // Сортируем записи по полю cityCode перед записью
//     sort(records.begin(), records.end(), compareRecords);
//
//     string textFilename = "records.txt";
//     string binaryFilename = "records.bin";
//
//     writeTextFile(textFilename, records);
//     convertToBinary(textFilename, binaryFilename);
//
//     int searchKey = records[0].cityCode;
//     Record foundRecord;
//
//     auto start = chrono::high_resolution_clock::now();
//     bool found = fibonacciSearchInFile(binaryFilename, searchKey, foundRecord);
//     auto end = chrono::high_resolution_clock::now();
//
//     auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
//
//     if (found) {
//         cout << "Запись найдена: " << foundRecord.cityCode << " " << foundRecord.cityName << endl;
//     } else {
//         cout << "Запись не найдена." << endl;
//     }
//
//     cout << "Время поиска: " << duration << " мкс" << endl;
//
//     return 0;
// }
//

// ДЛЯ 2
// int main() {
//     vector<Record> records;
//
//     // Измерение времени для разных объемов записей
//     for (int recordCount : {100, 1000, 10000}) {
//         generateData(recordCount, records);
//         string binaryFilename = "records_" + to_string(recordCount) + ".bin";
//         writeBinaryFile(binaryFilename, records);
//
//         // Поиск
//         Record foundRecord;
//         int searchKey = records[0].cityCode; // Поиск первой записи для теста
//
//         auto start = chrono::high_resolution_clock::now();
//         bool found = linearSearchInFile(binaryFilename, searchKey, foundRecord);
//         auto end = chrono::high_resolution_clock::now();
//
//         auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
//
//         if (found) {
//             cout << "Запись найдена: " << foundRecord.cityCode << " " << foundRecord.cityName << endl;
//         } else {
//             cout << "Запись не найдена." << endl;
//         }
//
//         cout << "Время поиска для " << recordCount << " записей: " << duration << " мкс" << endl;
//
//         // Очищаем записи для следующего теста
//         records.clear();
//     }
//
//     return 0;
// }

// ДЛЯ 3
// Основная функция программы
// Основная функция программы
// Основная функция
int main() {
    vector<Record> records;
    generateData(10000, records);

    string binaryFilename = "records.bin";
    writeBinaryFile(binaryFilename, records);

    // Создание индексной таблицы
    vector<IndexEntry> indexTable;
    createIndexTable(binaryFilename, indexTable);

    // Сортировка индексной таблицы по полю cityCode
    sort(indexTable.begin(), indexTable.end(), compareIndexEntries);

    // Ключ для поиска
    int searchKey = indexTable[3333].cityCode;  // Например, ключ для поиска
    Record foundRecord;

    // Линейный поиск
    cout << "Линейный поиск:" << endl;
    auto startLinear = chrono::high_resolution_clock::now();
    if (linearSearchInFile(binaryFilename, searchKey, foundRecord)) {
        auto endLinear = chrono::high_resolution_clock::now();
        auto durationLinear = chrono::duration_cast<chrono::microseconds>(endLinear - startLinear).count();
        cout << "Запись найдена: " << foundRecord.cityCode << " " << foundRecord.cityName << endl;
        cout << "Время поиска: " << durationLinear << " мкс" << endl;
    } else {
        cout << "Запись не найдена." << endl;
    }

    // Поиск по Фибоначчи
    cout << "Поиск по Фибоначчи:" << endl;
    streampos filePos;
    auto startFibonacci = chrono::high_resolution_clock::now();
    if (fibonacciSearchInIndexTable(indexTable, searchKey, filePos)) {
        if (readRecordAtPosition(binaryFilename, filePos, foundRecord)) {
            auto endFibonacci = chrono::high_resolution_clock::now();
            auto durationFibonacci = chrono::duration_cast<chrono::microseconds>(endFibonacci - startFibonacci).count();
            cout << "Запись найдена: " << foundRecord.cityCode << " " << foundRecord.cityName << endl;
            cout << "Время поиска: " << durationFibonacci << " мкс" << endl;
        }
    } else {
        cout << "Запись не найдена." << endl;
    }

    return 0;
}