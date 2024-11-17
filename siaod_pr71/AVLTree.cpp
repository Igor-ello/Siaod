#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Структура узла дерева AVL
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Класс AVLTree содержит методы для работы с деревом
class AVLTree {
public:
    // Создает новый узел с заданным значением
    Node* createNode(int key) {
        Node* node = new Node();
        node->key = key;
        node->left = node->right = nullptr;
        node->height = 1;
        return node;
    }

    // Возвращает высоту узла
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    // Вычисляет баланс-фактор узла для проверки его сбалансированности
    int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Выполняет правый поворот поддерева с корнем y
    Node* rotateRight(Node* y) {
        cout << "Right Rotation" << endl;
        Node* x = y->left;
        Node* T2 = x->right;

        // Выполняем поворот
        x->right = y;
        y->left = T2;

        // Обновляем высоты
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Выполняет левый поворот поддерева с корнем x
    Node* rotateLeft(Node* x) {
        cout << "Left Rotation" << endl;
        Node* y = x->right;
        Node* T2 = y->left;

        // Выполняем поворот
        y->left = x;
        x->right = T2;

        // Обновляем высоты
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Вставляет новый узел с заданным ключом в дерево и балансирует его
    Node* insert(Node* node, int key) {
        // Вставляем узел как в обычное бинарное дерево поиска
        if (!node) return createNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node; // Дубликаты не разрешены

        // Обновляем высоту узла
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Проверяем баланс узла
        int balance = getBalanceFactor(node);

        // Выполняем необходимые повороты для балансировки
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

    // Симметричный (in-order) обход дерева
    void inOrderTraversal(Node* root) {
        if (root) {
            inOrderTraversal(root->left);
            cout << root->key << " ";
            inOrderTraversal(root->right);
        }
    }

    // Обратный (post-order) обход дерева
    void postOrderTraversal(Node* root) {
        if (root) {
            postOrderTraversal(root->left);
            postOrderTraversal(root->right);
            cout << root->key << " ";
        }
    }

    // Вычисляет сумму значений всех листьев дерева
    int leafSum(Node* root) {
        if (!root) return 0;
        if (!root->left && !root->right) return root->key; // Если лист
        return leafSum(root->left) + leafSum(root->right);
    }

    // Возвращает высоту всего дерева
    int treeHeight(Node* root) {
        return getHeight(root);
    }

    // Рекурсивно печатает дерево с отступами для каждого уровня
    void printTree(Node* root, int space = 0, int levelSpacing = 6) {
        if (!root) return;

        // Увеличиваем отступ для правого поддерева
        space += levelSpacing;

        // Печатаем правое поддерево
        printTree(root->right, space);

        // Печатаем текущий узел с отступом (корень)
        cout << endl;
        cout << setw(space) << root->key;

        // Печатаем левое поддерево
        printTree(root->left, space);
    }

    // Заполняет дерево узлами с заданным количеством узлов
    // randomFill == true для случайного заполнения, false для пользовательского ввода
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
