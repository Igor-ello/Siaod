#include <iostream>
#include "AVLTree.cpp"

using namespace std;

void displayMenu() {
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "Меню:\n";
    cout << "1. Вставка элемента\n";
    cout << "2. Симметричный обход\n";
    cout << "3. Обратный обход\n";
    cout << "4. Найти сумму значений листьев\n";
    cout << "5. Найти высоту дерева\n";
    cout << "6. Вывести всё дерево\n";
    cout << "7. Заполнить дерево\n";
    cout << "8. Выход\n";
}

int main() {
    AVLTree tree;
    Node* root = nullptr;
    int choice, key;

    while (true) {
        displayMenu();
        cout << "Выберите режим работы: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите значение для вставки: ";
                cin >> key;
                root = tree.insert(root, key);
                cout << "Элемент вставлен и дерево сбалансировано.\n";
                break;
            case 2:
                cout << "Симметричный обход: ";
                tree.inOrderTraversal(root);
                cout << "\n";
                break;
            case 3:
                cout << "Обратный обход: ";
                tree.postOrderTraversal(root);
                cout << "\n";
                break;
            case 4:
                cout << "Сумма значений листьев: " << tree.leafSum(root) << "\n";
                break;
            case 5:
                cout << "Высота дерева: " << tree.treeHeight(root) << "\n";
                break;
            case 6:
                cout << "Вывод дерева:\n";
                tree.printTree(root);
                cout << "\n";
                break;
            case 7:
                int count;
                bool randomFill;
                cout << "Введите количество узлов: ";
                cin >> count;
                cout << "Заполнить дерево случайными значениями? (1 - да, 0 - нет): ";
                cin >> randomFill;
                tree.fillTree(root, count, randomFill);
                break;
            case 8:
                cout << "Выход из программы.\n";
                return 0;
            default:
                cout << "Некорректный ввод. Попробуйте снова.\n";
        }
    }
}
