#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Функция для перестановки первого и последнего слова
string swapFirstAndLastWords(const string& text) {
    size_t first_space = text.find(' ');
    size_t last_space = text.rfind(' ');

    if (first_space == string::npos || last_space == string::npos || first_space == last_space) {
        return text;  // Если одно слово, ничего не меняем
    }

    string first_word = text.substr(0, first_space);
    string last_word = text.substr(last_space + 1);

    return last_word + text.substr(first_space, last_space - first_space) + " " + first_word;
}

// Хеш-функция для Рабина-Карпа
int hash_rk(const string& str, int prime, int mod) {
    int h = 0;
    for (char ch : str) {
        h = (h * prime + ch) % mod;
    }
    return h;
}

// Поиск подстрок с помощью Рабина-Карпа
unordered_map<string, int> rabinKarpSearch(const string& text, const vector<string>& patterns) {
    const int prime = 31;  // Простое число для хеширования
    const int mod = 1e9 + 9;

    unordered_map<string, int> pattern_counts;

    for (const auto& pattern : patterns) {
        int m = pattern.size();
        int pattern_hash = hash_rk(pattern, prime, mod);
        int text_hash = hash_rk(text.substr(0, m), prime, mod);

        int pow_p = 1;
        for (int i = 1; i < m; i++) {
            pow_p = (pow_p * prime) % mod;
        }

        for (size_t i = 0; i + m <= text.size(); i++) {
            if (text_hash == pattern_hash && text.substr(i, m) == pattern) {
                pattern_counts[pattern]++;
            }
            if (i + m < text.size()) {
                text_hash = (text_hash - text[i] * pow_p % mod + mod) % mod;
                text_hash = (text_hash * prime + text[i + m]) % mod;
            }
        }
    }
    return pattern_counts;
}

// Функция для генерации случайной строки заданной длины
string generateRandomString(int length) {
    const string chars = "abcdefg"; // Буквы алфавита abcdefghijklmnopqrstuvwxyz
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, chars.size() - 1);

    string randomString;
    for (int i = 0; i < length; ++i) {
        randomString += chars[dis(gen)];
    }
    return randomString;
}

// Функция для генерации случайного текста и подстроки (образца)
tuple<string, string, string> generateTextAndPatterns(int textLength, int patternLength) {
    // Генерируем случайный текст и подстроку из текста
    string text = generateRandomString(textLength);

    // Определяем случайную позицию для подстроки
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(0, textLength - patternLength);
    int start = dis(gen);
    // Извлекаем подстроку из текста для создания 1-го образца
    string pattern1 = text.substr(start, patternLength);

    start = dis(gen);
    // Извлекаем подстроку из текста для создания 2-го образца
    string pattern2 = text.substr(start, patternLength);

    return {text, pattern1, pattern2};
}

int main() {
    // Задача 1: перестановка слов
    string msg = "Hello, world! Welcome to coding.";
    string swapped_text = swapFirstAndLastWords(msg);
    cout << "Начальная строка: " << msg << endl;
    cout << "Перестановка слов: " << swapped_text << endl << endl;

    // Задача 2: Рабин-Карп для поиска вхождений

    int textLength = 10;  // Длина текста
    int patternLength = 2;  // Длина образца
    auto [text, pattern1, pattern2] = generateTextAndPatterns(textLength, patternLength);
    cout << "Строка, в которой осуществляется поиск: " << text << endl;
    cout << "Сгенерированный образец 1: " << pattern1 << endl;
    cout << "Сгенерированный образец 2: " << pattern2 << endl;

    vector<string> patterns = {pattern1, pattern2};
    auto start = high_resolution_clock::now();
    auto counts = rabinKarpSearch(text, patterns);
    auto end = high_resolution_clock::now();

    cout << "Вхождения подстрок:\n";
    for (const auto& [pattern, count] : counts) {
        cout << "Подстрока: " << pattern << ", Количество вхождений: " << count << endl;
    }

    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Время выполнения: " << duration << " микросекунд" << endl;

    return 0;
}
