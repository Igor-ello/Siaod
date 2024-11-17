#include "Huffman.h"
#include <queue>

using namespace std;

Node::Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}

bool Compare::operator()(Node* l, Node* r) {
    return l->freq > r->freq;
}

// Построение дерева Хаффмана
Node* buildHuffmanTree(const string& text, map<char, int>& freqTable) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (auto pair : freqTable)
        minHeap.push(new Node(pair.first, pair.second));

    while (minHeap.size() != 1) {
        Node *left = minHeap.top(); minHeap.pop();
        Node *right = minHeap.top(); minHeap.pop();

        int sum = left->freq + right->freq;
        Node *node = new Node('\0', sum);
        node->left = left;
        node->right = right;
        minHeap.push(node);
    }
    return minHeap.top();
}

// Построение кодов Хаффмана
void encode(Node* root, const string& str, map<char, string>& huffmanCode) {
    if (root == nullptr) return;

    if (!root->left && !root->right) huffmanCode[root->ch] = str;

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Функция кодирования текста
string encodeHuffman(const string& text, const map<char, string>& huffmanCode) {
    string encodedText;
    for (char ch : text)
        encodedText += huffmanCode.at(ch);
    return encodedText;
}

// Декодирование текста
string decodeHuffman(Node* root, const string& encodedText) {
    string decodedText;
    Node* current = root;
    for (char bit : encodedText) {
        if (bit == '0')
            current = current->left;
        else
            current = current->right;

        if (!current->left && !current->right) {
            decodedText += current->ch;
            current = root;
        }
    }
    return decodedText;
}
