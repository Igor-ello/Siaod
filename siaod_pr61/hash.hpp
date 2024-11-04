#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Data_Record {
    int license_number; // номер лицензии
    string company_name; // название предприятия
    string founder; // учредитель

    Data_Record(int license_number, const string& company_name, const string& founder)
        : license_number(license_number), company_name(company_name), founder(founder) {}

    string string_rep();
};

class Hash_Table {
private:
    Data_Record **table;
    int size;
    int num_of_elements;
    const float load_factor_threshold = 0.75;

    int hash_function(int license_number) const;
    int second_hash_function(int license_number) const; // вторая хеш-функция для двойного хеширования
    void rehash();

public:
    Hash_Table(int table_size);
    ~Hash_Table();

    void insert(Data_Record *new_record);
    Data_Record *search(int license_number);
    int remove(int license_number);
    void display() const;
};
