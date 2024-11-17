//
// Created by Igorello on 17.11.2024.
//

#ifndef FANO1_H
#define FANO1_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Symbol {
	char ch;
	double probability;
	string code;

	string toString() const;
};

bool compareByProbability(const Symbol& a, const Symbol& b);
void shannonFano(vector<Symbol>& symbols, int start, int end);
int fano();

#endif //FANO1_H
