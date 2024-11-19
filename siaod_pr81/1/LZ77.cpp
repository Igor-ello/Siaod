#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <iomanip>

using namespace std;

const int WINDOW_SIZE = 5;

vector<tuple<int, int, char>> LZ77(const string& text) {
    vector<tuple<int, int, char>> result;
    int pos = 0;

    // Заголовок таблицы
    cout << setw(5) << "Шаг" << setw(16) << "Словарь" << setw(12) << "Буфер"
         << setw(35) << "Совпадающая фраза" << setw(44) << "Закодированные данные\n";

    int step = 1;
    while (pos < text.size()) {
        int maxLen = 0, bestOffset = 0;
        char nextChar = text[pos];

        // Печать текущего словаря и буфера
        string dictionary = text.substr(max(0, pos - WINDOW_SIZE), min(pos, WINDOW_SIZE));
        string buffer = text.substr(pos, WINDOW_SIZE);
        cout << setw(3) << step++ << setw(9) << dictionary << setw(7) << buffer;

        for (int offset = 1; offset <= WINDOW_SIZE && pos - offset >= 0; offset++) {
            int len = 0;
            while (len < WINDOW_SIZE && pos + len < text.size() &&
                   text[pos - offset + len] == text[pos + len])
                len++;

            if (len > maxLen) {
                maxLen = len;
                bestOffset = offset;
                nextChar = pos + len < text.size() ? text[pos + len] : '\0';
            }
        }

        string matchedPhrase = maxLen > 0 ? text.substr(pos, maxLen) : "-";
        cout << setw(19) << matchedPhrase;

        // Добавление в результат
        result.push_back({bestOffset, maxLen, nextChar});

        // Печать закодированных данных
        cout << setw(15) << "(" << bestOffset << ", " << maxLen << ", " << (nextChar ? nextChar : '-') << ")\n";

        pos += maxLen + 1;
    }

    return result;
}

int encodeLZ77() {
	string text = "0010100110010000001";
	auto encoded = LZ77(text);

    cout << "\nКодированные данные:\n";
    for (auto& tuple : encoded)
        cout << "<" << get<0>(tuple) << ", " << get<1>(tuple) << ", " << (get<2>(tuple) ? get<2>(tuple) : '-') << "> ";
    cout << endl << endl;

    cout << "(offset, length, next)\n";
    for (auto& tuple : encoded)
        cout << "(" << get<0>(tuple) << ", " << get<1>(tuple) << ", " << get<2>(tuple) << ")\n";

	return 0;
}
