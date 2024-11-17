#include "Fano2.h"

using namespace std;

// Метод для форматированного вывода параметров символа
string Symbol2::toString() const {
    return "Char: '" + string(1, ch) + "', Probability: " + to_string(probability) + ", Code: " + code;
}

// Функция для сравнения символов по вероятности
bool compareByProbability2(const Symbol2& a, const Symbol2& b) {
    return a.probability > b.probability;
}

// Рекурсивная функция для построения кодов Шеннона-Фано
void shannonFano2(vector<Symbol2>& symbols, int start, int end) {
    if (start >= end) return;

    // Вычисляем общую частоту всех символов в текущем отрезке
    double totalFrequency = 0;
    for (int i = start; i <= end; i++)
        totalFrequency += symbols[i].probability;

    // Поиск точки раздела
    int splitPoint = start;
    double cumulativeFrequency = 0;
    for (int i = start; i <= end; i++) {
        cumulativeFrequency += symbols[i].probability;
        if (cumulativeFrequency >= totalFrequency / 2) {
            splitPoint = i;
            break;
        }
    }

    // Добавляем соответствующие префиксы
    for (int i = start; i <= splitPoint; i++)
        symbols[i].code += "0";  // Символы слева получают "0" в код
    for (int i = splitPoint + 1; i <= end; i++)
        symbols[i].code += "1";  // Символы справа получают "1" в код

    // Рекурсивный вызов для левой и правой части
    shannonFano2(symbols, start, splitPoint);
    shannonFano2(symbols, splitPoint + 1, end);
}

// Построение таблицы символов и их вероятностей
void buildShannonFanoTable(const string& text, vector<Symbol2>& symbols) {
    map<char, int> frequency;

    // Подсчет частоты символов
    for (char ch : text)
        frequency[ch]++;

    // Заполнение символов с вероятностями
    for (const auto& pair : frequency)
        symbols.push_back({pair.first, static_cast<double>(pair.second) / text.size(), ""});

    // Сортировка символов по вероятности
    sort(symbols.begin(), symbols.end(), compareByProbability2);

    // Строим коды Шеннона-Фано
    shannonFano2(symbols, 0, symbols.size() - 1);
}

// Функция кодирования текста
string encodeShannonFano(const string& text, const vector<Symbol2>& symbols) {
    map<char, string> codeTable;

    // Заполняем таблицу кодов
    for (const auto& sym : symbols)
        codeTable[sym.ch] = sym.code;

    string encodedText;

    // Кодируем текст
    for (char ch : text)
        encodedText += codeTable[ch];

    return encodedText;
}

// Функция декодирования текста
string decodeShannonFano(const string& encodedText, const vector<Symbol2>& symbols) {
    map<string, char> reverseCodeTable;

    // Заполняем таблицу для обратного декодирования
    for (const auto& sym : symbols)
        reverseCodeTable[sym.code] = sym.ch;

    string decodedText, code;

    // Декодируем текст
    for (char bit : encodedText) {
        code += bit;
        if (reverseCodeTable.count(code)) {
            decodedText += reverseCodeTable[code];
            code.clear();
        }
    }

    return decodedText;
}
