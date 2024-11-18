#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Узел дерева Хаффмана
struct NodeTree {
    char ch;
    int freq;
    NodeTree* left;
    NodeTree* right;

    NodeTree(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

// Сравнение для приоритетной очереди
struct Compare {
    bool operator()(NodeTree* l, NodeTree* r) {
        return l->freq > r->freq;
    }
};

// Построение дерева Хаффмана
NodeTree* buildHuffmanTree(const map<char, int>& frequency) {
    priority_queue<NodeTree*, vector<NodeTree*>, Compare> minHeap;

    for (const auto& pair : frequency) {
        minHeap.push(new NodeTree(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        NodeTree* left = minHeap.top();
        minHeap.pop();
        NodeTree* right = minHeap.top();
        minHeap.pop();

        NodeTree* newNode = new NodeTree('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top(); // Корень дерева
}

// Рекурсивная функция для генерации кодов Хаффмана
void generateHuffmanCodes(NodeTree* root, string code, map<char, string>& huffmanCodes) {
    if (!root) return;

    if (root->ch != '\0') {
        huffmanCodes[root->ch] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Рекурсивная функция для вывода дерева
void printHuffmanTree(NodeTree* root, string indent = "", bool isLeft = true) {
    if (root == nullptr) return;

    cout << indent;
    if (isLeft) {
        cout << "├── ";
    } else {
        cout << "└── ";
    }

    if (root->ch != '\0') {
        cout << "'" << root->ch << "' (" << root->freq << ")" << endl;
    } else {
        cout << "[" << root->freq << "]" << endl;
    }

    printHuffmanTree(root->left, indent + (isLeft ? "│   " : "    "), true);
    printHuffmanTree(root->right, indent + (isLeft ? "│   " : "    "), false);
}

#endif // TREE_H
