#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<pair<int, char>> LZ78(const string& text) {
	map<string, int> dictionary;
	vector<pair<int, char>> result;
	int index = 1;

	string current;
	for (char ch : text) {
		current += ch;
		if (dictionary.find(current) == dictionary.end()) {
			dictionary[current] = index++;
			result.push_back({dictionary[current.substr(0, current.size() - 1)], ch});
			current.clear();
		}
	}

	if (!current.empty())
		result.push_back({dictionary[current.substr(0, current.size() - 1)], current.back()});

	return result;
}

int encodeLZ78() {
	string text = "porpoterpoterporter";
	auto encoded = LZ78(text);

	cout << "(index, char)\n";
	for (auto& pair : encoded)
		cout << "(" << pair.first << ", " << pair.second << ")\n";

	return 0;
}
