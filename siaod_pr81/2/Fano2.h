//
// Created by Igorello on 17.11.2024.
//

#ifndef FANO2_H
#define FANO2_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Структура для символа, содержащая его символ, вероятность и код
struct Symbol2 {
	char ch;                // Символ
	double probability;      // Вероятность символа
	string code;            // Код символа

	string toString() const;
};

// Объявления функций
bool compareByProbability2(const Symbol2& a, const Symbol2& b);
void shannonFano2(std::vector<Symbol2>& symbols, int start, int end);
void buildShannonFanoTable(const std::string& text, std::vector<Symbol2>& symbols);
std::string encodeShannonFano(const std::string& text, const std::vector<Symbol2>& symbols);
std::string decodeShannonFano(const std::string& encodedText, const std::vector<Symbol2>& symbols);

#endif //FANO2_H
