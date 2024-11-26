#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

vector<pair<int, char>> LZ78(const string& text) {
    map<string, int> dictionary;
    vector<pair<int, char>> result;
    int index = 1;

    string current;

    // Заголовок таблицы
    cout << left
         << setw(16) << "Словарь"
         << setw(45) << "Считываемое содержимое"
         << setw(15) << "Код" << '\n';
    cout << string(75, '-') << '\n';

    for (char ch : text) {
        current += ch;

        if (dictionary.find(current) == dictionary.end()) {
            // Добавляем новую строку в словарь
            dictionary[current] = index++;

            // Кодировка: (номер словаря, символ)
            int prefixIndex = current.size() > 1 ? dictionary[current.substr(0, current.size() - 1)] : 0;
            result.push_back({prefixIndex, ch});

            // Вывод текущего состояния
            cout << setw(8);
            for (const auto& entry : dictionary) {
                cout << entry.first << " = " << entry.second << ", ";
            }
            cout << setw(19) << current
                 << setw(15) << ("<" + to_string(prefixIndex) + ", " + ch + ">") << '\n';

            current.clear();
        }
    }

    // Если осталась часть строки
    if (!current.empty()) {
        int prefixIndex = current.size() > 1 ? dictionary[current.substr(0, current.size() - 1)] : 0;
        result.push_back({prefixIndex, current.back()});
        cout << setw(30);
        for (const auto& entry : dictionary) {
            cout << entry.first << " = " << entry.second << ", ";
        }
        cout << setw(30) << current
             << setw(15) << ("<" + to_string(prefixIndex) + ", " + current.back() + ">") << '\n';
    }

    return result;
}

double calculateCompressionRatio(const string& text, const vector<pair<int, char>>& encoded) {
    int originalSize = text.size() * 8;  // Размер исходного текста в битах (по 8 бит на символ)
    int dictionarySize = encoded.size(); // Количество триплетов
    int compressedSize = 0;

    // Для каждого триплета (index, char) считаем размер в битах
    for (const auto& pair : encoded) {
        // Индекс занимает log2(dictionarySize) бит, но для упрощения берем log2(количество элементов в словаре)
        int indexSize = static_cast<int>(ceil(log2(dictionarySize)));
        compressedSize += indexSize; // Размер индекса (в битах)
        compressedSize += 8; // Размер символа (1 байт = 8 бит)
    }

    double compressionRatio = 100.0 - (100.0 * compressedSize / originalSize); // Степень сжатия в процентах
    return compressionRatio;
}

int encodeLZ78() {
    string text = "porpoterpoterporter";
    auto encoded = LZ78(text);

    cout << "\nКодированные данные:\n";
    for (auto& pair : encoded) {
        cout << "<" << pair.first << ", " << pair.second << "> ";
    }
    cout << endl << endl;

    cout << "(index, char)\n";
    for (auto& pair : encoded)
        cout << "(" << pair.first << ", " << pair.second << ")\n";
    cout << endl;

    // Расчёт степени сжатия
    double compressionRatio = calculateCompressionRatio(text, encoded);
    cout << "Степень сжатия: " << compressionRatio << "%" << endl;

    return 0;
}

