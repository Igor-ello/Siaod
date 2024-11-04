#include "hash.hpp"

string Data_Record::string_rep() {
    return "[Номер лицензии: " + to_string(license_number) + ", Название: " + company_name + ", Учредитель: " + founder + "]";
}

Hash_Table::Hash_Table(int table_size) : size(table_size), num_of_elements(0) {
    table = new Data_Record *[size];
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

Hash_Table::~Hash_Table() {
    for (int i = 0; i < size; i++) {
        if (table[i] != nullptr) {
            delete table[i];
        }
    }
    delete[] table;
}

int Hash_Table::hash_function(int license_number) const {
    return license_number % size;
}

int Hash_Table::second_hash_function(int license_number) const {
    return 1 + (license_number % (size - 1));
}

void Hash_Table::rehash() {
    cout << "Перехеширование: увеличиваем размер таблицы до " << size * 2 << endl;
    int old_size = size;
    size *= 2;
    Data_Record **new_table = new Data_Record *[size];
    for (int i = 0; i < size; i++) {
        new_table[i] = nullptr;
    }

    for (int i = 0; i < old_size; i++) {
        if (table[i] != nullptr) {
            int new_index = hash_function(table[i]->license_number);
            new_table[new_index] = table[i];
        }
    }

    delete[] table;
    table = new_table;
}

void Hash_Table::insert(Data_Record *new_record) {
    int index = hash_function(new_record->license_number);
    int step = second_hash_function(new_record->license_number);

    while (table[index] != nullptr) {
        index = (index + step) % size;
    }
    table[index] = new_record;
    num_of_elements++;

    if (static_cast<float>(num_of_elements) / size > load_factor_threshold) {
        rehash();
    }
}

Data_Record *Hash_Table::search(int license_number) {
    int index = hash_function(license_number);
    int step = second_hash_function(license_number);

    while (table[index] != nullptr) {
        if (table[index]->license_number == license_number) {
            return table[index];
        }
        index = (index + step) % size;
    }
    return nullptr;
}

int Hash_Table::remove(int license_number) {
    int index = hash_function(license_number);
    int step = second_hash_function(license_number);

    while (table[index] != nullptr) {
        if (table[index]->license_number == license_number) {
            delete table[index];
            table[index] = nullptr;
            num_of_elements--;
            return 0;
        }
        index = (index + step) % size;
    }
    return 1;
}

void Hash_Table::display() const {
    bool empty_flag = true;
    for (int i = 0; i < size; i++) {
        if (table[i] != nullptr) {
            empty_flag = false;
            cout << "Ячейка " << i << ": " << table[i]->string_rep() << endl;
        }
    }
    if (empty_flag) {
        cout << "Нет данных" << endl;
    }
}
