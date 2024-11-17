#include <iostream>

#include "1/main1.h"
#include "2/main2.h"

using namespace std;

int main() {
	int choice;
	cout << "Enter your choice (1 - Task 1, 2 - Task 2): ";
	cin >> choice;
	if (choice == 1) {
		main1();
	} else if (choice == 2) {
		main2();
	} else cout << "Task not exist!";
}