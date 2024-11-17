//
// Created by Igorello on 17.11.2024.
//

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <map>
#include <string>

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
Node* buildHuffmanTree(const std::string& text, std::map<char, int>& freqTable);
void encode(Node* root, const std::string& str, std::map<char, std::string>& huffmanCode);
std::string encodeHuffman(const std::string& text, const std::map<char, std::string>& huffmanCode);
std::string decodeHuffman(Node* root, const std::string& encodedText);

#endif //HUFFMAN_H
