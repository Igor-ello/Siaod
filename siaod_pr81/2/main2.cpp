#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "Fano2.h"
#include "Huffman.h"

using namespace std;

void testShannonFano() {
	//string text = "Пример текста для Шеннона–Фано";
	string text = "Sample text for Shannon–Fano";
	vector<Symbol2> symbols;

	buildShannonFanoTable(text, symbols);

	cout << "Кодирование методом Шеннона-Фано:\n";
	// Выводим символы и их начальные значения
	for (int i = 0; i < symbols.size(); i++) {
		cout << symbols[i].toString() << endl;
	}

	string encodedText = encodeShannonFano(text, symbols);
	cout << "Закодированный текст: " << encodedText << "\n";

	string decodedText = decodeShannonFano(encodedText, symbols);
	cout << "Декодированный текст: " << decodedText << "\n";

	double compressionRatio = (text.size() * 8.0) / encodedText.size();
	cout << "Коэффициент сжатия: " << compressionRatio << "\n";
}

void testHuffman() {
	//string text = "Фамилия Имя Отчество";
	string text = "Orlov Igor Olegovich";

	map<char, int> freqTable;
	for (char ch : text)
		freqTable[ch]++;

	for (const auto& pair : freqTable) {
		cout << "Символ: '" << pair.first << "' встречается " << pair.second << " раз(а)" << endl;
	}
	cout << endl;

	Node* root = buildHuffmanTree(text, freqTable);

	map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Кодирование методом Хаффмана:\n";
	for (const auto& pair : huffmanCode) {
		cout << pair.first << " " << pair.second << endl;
	}

	string encodedText = encodeHuffman(text, huffmanCode);
	cout << "Закодированный текст: " << encodedText << "\n";

	string decodedText = decodeHuffman(root, encodedText);
	cout << "Декодированный текст: " << decodedText << "\n";

	double compressionRatio = (text.size() * 8.0) / encodedText.size();
	cout << "Коэффициент сжатия: " << compressionRatio << "\n";
}

int main2() {
	int choice;
	cout << "Выбор алгоритма сжатия (1 - Алгоритм Шеннона-Фано, 2 - Алгоритм Хаффмана):\n";
	cin >> choice;

	switch (choice) {
		case 1:
			cout << "Тест алгоритма Шеннона-Фано:\n";
			testShannonFano();
		break;
		case 2:
			cout << "Тест алгоритма Хаффмана:\n";
			testHuffman();
		break;
		default:
			cout << "Неверная команда!";
	}

	return 0;
}
