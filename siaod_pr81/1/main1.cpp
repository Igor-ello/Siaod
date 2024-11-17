#include <iostream>
#include "Fano1.h"

using namespace std;

void encodeLZ77();
void encodeLZ78();

int main1() {
    int choice;
    cout << "Выбор алгоритма сжатия (1-shannonFano, 2-encodeLZ77, 3-encodeLZ78):\n";
    cin >> choice;

    switch (choice) {
        case 1:
            fano();
            break;
        case 2:
            encodeLZ77();
            break;
        case 3:
            encodeLZ78();
            break;
        default:
            cout << "Неверная команда!";
    }
    return 0;
}