#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

const int WINDOW_SIZE = 5;

vector<tuple<int, int, char>> LZ77(const string& text) {
	vector<tuple<int, int, char>> result;
	int pos = 0;

	while (pos < text.size()) {
		int maxLen = 0, bestOffset = 0;
		char nextChar = text[pos];

		for (int offset = 1; offset <= WINDOW_SIZE && pos - offset >= 0; offset++) {
			int len = 0;
			while (len < WINDOW_SIZE && pos + len < text.size() && text[pos - offset + len] == text[pos + len])
				len++;

			if (len > maxLen) {
				maxLen = len;
				bestOffset = offset;
				nextChar = pos + len < text.size() ? text[pos + len] : '\0';
			}
		}

		result.push_back({bestOffset, maxLen, nextChar});
		pos += maxLen + 1;
	}

	return result;
}

int encodeLZ77() {
	string text = "0010100110010000001";
	auto encoded = LZ77(text);

	cout << "(offset, length, next)\n";
	for (auto& tuple : encoded)
		cout << "(" << get<0>(tuple) << ", " << get<1>(tuple) << ", " << get<2>(tuple) << ")\n";

	return 0;
}
