#define _CRT_SECURE_NO_WARNINGS
#include "Stroka.h"
#include <cstring>
#include <iostream>

using namespace std;

// Конструктор по умолчанию
Stroka::Stroka() {
    str[0] = '\0';  // Пустая строка
}

// Конструктор из C-строки
Stroka::Stroka(const char* string) {
    if (string != nullptr) {
        strncpy(str, string, MAX_LENGTH - 1);
        str[MAX_LENGTH - 1] = '\0';  // Гарантируем завершающий ноль
    }
    else {
        str[0] = '\0';
    }
}

// Конструктор копирования
Stroka::Stroka(const Stroka& other) {
    strncpy(str, other.str, MAX_LENGTH);
    str[MAX_LENGTH - 1] = '\0';
}

// Деструктор
Stroka::~Stroka() {
    // В данном случае деструктор пустой, так как нет динамической памяти
}

// Оператор присваивания для объектов Stroka
Stroka& Stroka::operator=(const Stroka& other) {
    if (this != &other) {  // Защита от самоприсваивания
        strncpy(str, other.str, MAX_LENGTH);
        str[MAX_LENGTH - 1] = '\0';
    }
    return *this;
}

// Оператор присваивания для C-строк
Stroka& Stroka::operator=(const char* string) {
    if (string != nullptr) {
        strncpy(str, string, MAX_LENGTH - 1);
        str[MAX_LENGTH - 1] = '\0';
    }
    else {
        str[0] = '\0';
    }
    return *this;
}

// Оператор сложения (конкатенация)
Stroka Stroka::operator+(const Stroka& other) const {
    Stroka result(*this);  // Создаем копию текущего объекта
    if (strlen(result.str) + strlen(other.str) < MAX_LENGTH) {
        strcat(result.str, other.str);
    }
    else {
        // Если не хватает места, копируем только то, что помещается
        strncat(result.str, other.str, MAX_LENGTH - strlen(result.str) - 1);
    }
    return result;
}

// Оператор сравнения на равенство
bool Stroka::operator==(const Stroka& other) const {
    return strcmp(str, other.str) == 0;
}

// Оператор сравнения на неравенство
bool Stroka::operator!=(const Stroka& other) const {
    return !(*this == other);
}

// Определение длины строки
int Stroka::dlina() const {
    return strlen(str);
}

// Ввод строки
void Stroka::vvod() {
    cin.getline(str, MAX_LENGTH);
    // Очищаем буфер, если ввод был больше максимальной длины
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Вывод строки
void Stroka::vyvod() const {
    setlocale(LC_ALL, "");
    cout << str;
}

// Получить C-строку
const char* Stroka::c_str() const {
    return str;
}

// Проверка на пустоту
bool Stroka::pusta() const {
    return str[0] == '\0';
}

// Оператор вывода
ostream& operator<<(ostream& os, const Stroka& s) {
    os << s.str;
    return os;
}

// Оператор ввода
istream& operator>>(istream& is, Stroka& s) {
    // Используем временный буфер
    char buffer[Stroka::MAX_LENGTH];
    is >> buffer;
    s = buffer;  // Используем оператор присваивания
    return is;
}
