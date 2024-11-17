#include "Fano1.h"

using namespace std;

// Метод для форматированного вывода параметров символа
string Symbol::toString() const {
    return "Char: '" + string(1, ch) + "', Probability: " + to_string(probability) + ", Code: " + code;
}

// Функция для сравнения символов по вероятности
bool compareByProbability(const Symbol& a, const Symbol& b) {
    return a.probability > b.probability;
}

// Рекурсивная функция для построения кодов Шеннона-Фано
void shannonFano(vector<Symbol>& symbols, int start, int end) {
    if (start >= end) return;

    // Вычисляем общую частоту всех символов в текущем отрезке
    double totalFrequency = 0;
    for (int i = start; i <= end; i++) {
        totalFrequency += symbols[i].probability;
    }

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
    for (int i = start; i <= splitPoint; i++) {
        symbols[i].code += "0"; // Символы слева получают "0" в код
    }
    for (int i = splitPoint + 1; i <= end; i++) {
        symbols[i].code += "1"; // Символы справа получают "1" в код
    }

    // Рекурсивный вызов для левой и правой части
    shannonFano(symbols, start, splitPoint);
    shannonFano(symbols, splitPoint + 1, end);
}

// Функция декодирования текста
string decodeShannonFano(const string& encodedText, const vector<Symbol>& symbols) {
    map<string, char> codeToSymbol;
    for (const auto& sym : symbols) {
        codeToSymbol[sym.code] = sym.ch;
    }

    string decodedText;
    string currentCode;

    for (char bit : encodedText) {
        currentCode += bit;

        // Если текущий код найден в таблице, добавляем символ в результат
        if (codeToSymbol.find(currentCode) != codeToSymbol.end()) {
            decodedText += codeToSymbol[currentCode];
            currentCode.clear(); // Сбрасываем текущий код
        }
    }

    return decodedText;
}

// Функция для выполнения алгоритма Шеннона-Фано на тестовом тексте
int fano() {
    //string text = "Ана-дэус-рики-паки, Дормы-кормыконсту-таки, Энус-дэус-кана-дэусБАЦ!";
    string text = "Ana-deus-riki-paki, Dormy-kormyconstu-taki, Enus-deus-cana-deusBAM!";
    map<char, int> frequency;

    // Подсчёт частоты символов в тексте
    for (char ch : text) {
        frequency[ch]++;
    }

    vector<Symbol> symbols;
    for (const auto& pair : frequency) {
        // Добавляем символы в вектор с их вероятностями
        symbols.push_back({pair.first, static_cast<double>(pair.second) / text.size(), ""});
    }

    // Сортируем символы по вероятности
    sort(symbols.begin(), symbols.end(), compareByProbability);

    // Выводим символы и их начальные значения
    for (int i = 0; i < symbols.size(); i++) {
        cout << symbols[i].toString() << endl;
    }
    cout << endl;

    // Строим коды Шеннона-Фано
    shannonFano(symbols, 0, symbols.size() - 1);

    // Вычисляем исходный размер (в битах)
    int originalSize = text.size() * 8; // 8 бит на символ

    // Вычисляем сжатый размер (в битах)
    int compressedSize = 0;
    for (const auto& sym : symbols) {
        compressedSize += sym.code.size() * frequency[sym.ch]; // Умножаем длину кода на частоту символа
    }

    // Вычисляем процент сжатия
    double compressionRatio = 100.0 - (100.0 * compressedSize / originalSize);

    // Кодируем текст
    string encodedText;
    for (char ch : text) {
        for (const auto& sym : symbols) {
            if (sym.ch == ch) {
                encodedText += sym.code;
                break;
            }
        }
    }

    // Восстанавливаем текст
    string decodedText = decodeShannonFano(encodedText, symbols);

    // Выводим результаты
    cout << "Символ\tЧастота\tКод\n";
    for (const auto& sym : symbols) {
        cout << sym.ch << "\t" << sym.probability << "\t" << sym.code << "\n";
    }

    cout << "\nОригинальный размер: " << originalSize << " бит" << endl;
    cout << "Сжатый размер: " << compressedSize << " бит" << endl;
    cout << "Процент сжатия: " << compressionRatio << "%" << endl;
    cout << "Закодированный текст: " << encodedText << endl;
    cout << "Восстановленный текст: " << decodedText << endl;

    return 0;
}
