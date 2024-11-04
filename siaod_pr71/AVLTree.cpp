#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
public:
    Node* createNode(int key) {
        Node* node = new Node();
        node->key = key;
        node->left = node->right = nullptr;
        node->height = 1;
        return node;
    }

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) return createNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);

        if (balance > 1 && key < node->left->key) return rotateRight(node);
        if (balance < -1 && key > node->right->key) return rotateLeft(node);
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inOrderTraversal(Node* root) {
        if (root) {
            inOrderTraversal(root->left);
            cout << root->key << " ";
            inOrderTraversal(root->right);
        }
    }

    void postOrderTraversal(Node* root) {
        if (root) {
            postOrderTraversal(root->left);
            postOrderTraversal(root->right);
            cout << root->key << " ";
        }
    }

    int leafSum(Node* root) {
        if (!root) return 0;
        if (!root->left && !root->right) return root->key;
        return leafSum(root->left) + leafSum(root->right);
    }

    int treeHeight(Node* root) {
        return getHeight(root);
    }

    void printTree(Node* root, int space = 0, int levelSpacing = 6) {
        if (!root) return;
        space += levelSpacing;
        printTree(root->right, space);
        cout << endl;
        cout << setw(space) << root->key;
        printTree(root->left, space);
    }

    void fillTree(Node*& root, int count, bool randomFill) {
        if (randomFill) {
            srand(time(nullptr));
            for (int i = 0; i < count; ++i) {
                int key = rand() % 100;
                root = insert(root, key);
            }
            cout << "Дерево заполнено случайными значениями.\n";
        } else {
            int key;
            for (int i = 0; i < count; ++i) {
                cout << "Введите значение #" << i + 1 << ": ";
                cin >> key;
                root = insert(root, key);
            }
            cout << "Дерево заполнено введёнными значениями.\n";
        }
    }
};
