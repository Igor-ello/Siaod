//
// Created by Igorello on 17.11.2024.
//

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <map>
#include <string>
#include <iostream>

using namespace std;

struct Node {
	char ch;
	int freq;
	Node* left, * right;
	Node(char ch, int freq);
};

struct Compare {
	bool operator()(Node* l, Node* r);
};

// Объявления функций
Node* buildHuffmanTree(const string& text, map<char, int>& freqTable);
void encode(Node* root, const string& str, map<char, string>& huffmanCode);
string encodeHuffman(const string& text, const map<char, string>& huffmanCode);
string decodeHuffman(Node* root, const string& encodedText);
// // Рекурсивная функция для вывода дерева
// void printHuffmanTree2(Node* root, string indent = "", bool isLeft = true) {
// 	if (root == nullptr) return;
//
// 	cout << indent;
// 	if (isLeft) {
// 		cout << "├── ";
// 	} else {
// 		cout << "└── ";
// 	}
//
// 	if (root->ch != '\0') {
// 		cout << "'" << root->ch << "' (" << root->freq << ")" << endl;
// 	} else {
// 		cout << "[" << root->freq << "]" << endl;
// 	}
//
// 	printHuffmanTree2(root->left, indent + (isLeft ? "│   " : "    "), true);
// 	printHuffmanTree2(root->right, indent + (isLeft ? "│   " : "    "), false);
// }

#endif //HUFFMAN_H
