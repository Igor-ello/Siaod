#include "hash.hpp"
#include <limits>

Hash_Table companies(5);

void add_initial_records() {
    companies.insert(new Data_Record(1234567, "Компания А", "Иванов Иван Иванович"));
    companies.insert(new Data_Record(2345678, "Компания Б", "Петров Петр Петрович"));
    companies.insert(new Data_Record(3456789, "Компания В", "Сидоров Сидор Сидорович"));
    companies.insert(new Data_Record(4567890, "Компания Г", "Кузнецов Николай Николаевич"));
    companies.insert(new Data_Record(5678901, "Компания Д", "Федоров Федор Федорович"));
}

void clear_cin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int get_license_number_from_user() {
    int license_number;
    while (true) {
        cout << "Введите номер лицензии (7-значное число): ";
        if (cin >> license_number && license_number >= 1000000 && license_number <= 9999999) {
            clear_cin();
            return license_number;
        }
        clear_cin();
        cout << "Неверный номер лицензии. Пожалуйста, введите 7-значное число.\n";
    }
}

string get_string_from_user(string prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

void insert() {
    int license_number = get_license_number_from_user();
    string company_name = get_string_from_user("Введите название предприятия: ");
    string founder = get_string_from_user("Введите ФИО учредителя: ");
    Data_Record* new_record = new Data_Record(license_number, company_name, founder);
    companies.insert(new_record);
    cout << "Успешно добавлено предприятие: " << new_record->string_rep() << endl;
}

void del() {
    int license_number = get_license_number_from_user();
    int return_code = companies.remove(license_number);
    if (return_code == 0) {
        cout << "Предприятие с номером лицензии " << license_number << " успешно удалено." << endl;
    } else {
        cout << "Предприятие с номером лицензии " << license_number << " не найдено." << endl;
    }
}

void search() {
    int license_number = get_license_number_from_user();
    Data_Record* record = companies.search(license_number);
    if (record == nullptr) {
        cout << "Предприятие с номером лицензии " << license_number << " не найдено." << endl;
    } else {
        cout << "Найдено предприятие: " << record->string_rep() << endl;
    }
}

void display() {
    cout << "Отображение всех предприятий: " << endl;
    companies.display();
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    add_initial_records();

    int cmd;
    while (true) {
        while (true) {
            cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "1: Добавить новое предприятие" << endl;
            cout << "2: Удалить предприятие" << endl;
            cout << "3: Поиск предприятия" << endl;
            cout << "4: Отобразить все предприятия" << endl;
            cout << "0: Выйти" << endl;
            cout << "\nКоманда: ";
            if (cin >> cmd && cmd >= 0 && cmd <= 4) break;
            clear_cin();
            cout << "Неверный код команды.\n";
        }

        switch (cmd) {
            case 0:
                return 0;
            case 1:
                insert();
                break;
            case 2:
                del();
                break;
            case 3:
                search();
                break;
            case 4:
                display();
                break;
        }
    }
}
