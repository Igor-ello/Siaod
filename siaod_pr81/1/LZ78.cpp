#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

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

	return 0;
}
