#include "Stroka.h"
#include <iostream>
#include <cctype>

using namespace std;

// Вспомогательные статические функции

// Функция определения длины строки
int Stroka::dlina_cstr(const char* str) {
    int length = 0;
    if (str != nullptr) {
        while (str[length] != '\0') {
            length++;
        }
    }
    return length;
}

// Функция копирования строк
void Stroka::kopir_cstr(char* dest, const char* src, int max_len) {
    if (dest == nullptr || src == nullptr || max_len <= 0) {
        return;
    }

    int i = 0;
    while (src[i] != '\0' && i < max_len - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Функция сравнения строк
int Stroka::sravn_cstr(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
        i++;
    }
    return (unsigned char)str1[i] - (unsigned char)str2[i];
}

// Функция конкатенации строк
void Stroka::konkat_cstr(char* dest, const char* src, int max_len) {
    if (dest == nullptr || src == nullptr || max_len <= 0) {
        return;
    }

    // Находим конец dest
    int i = 0;
    while (dest[i] != '\0' && i < max_len) {
        i++;
    }

    // Если dest уже заполнена, ничего не делаем
    if (i >= max_len - 1) {
        return;
    }

    // Копируем src в конец dest
    int j = 0;
    while (src[j] != '\0' && i < max_len - 1) {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}

// Реализация методов класса

// Конструктор по умолчанию
Stroka::Stroka() {
    str[0] = '\0';
}

// Конструктор из C-строки
Stroka::Stroka(const char* string) {
    if (string != nullptr) {
        kopir_cstr(str, string, MAX_LENGTH);
    }
    else {
        str[0] = '\0';
    }
}

// Конструктор копирования
Stroka::Stroka(const Stroka& other) {
    kopir_cstr(str, other.str, MAX_LENGTH);
}

// Деструктор
Stroka::~Stroka() {
    // Нет динамической памяти для освобождения
}

// Оператор присваивания для объектов Stroka
Stroka& Stroka::operator=(const Stroka& other) {
    if (this != &other) {
        kopir_cstr(str, other.str, MAX_LENGTH);
    }
    return *this;
}

// Оператор присваивания для C-строк
Stroka& Stroka::operator=(const char* string) {
    if (string != nullptr) {
        kopir_cstr(str, string, MAX_LENGTH);
    }
    else {
        str[0] = '\0';
    }
    return *this;
}

// Оператор сложения (конкатенация)
Stroka Stroka::operator+(const Stroka& other) const {
    Stroka result(*this);
    konkat_cstr(result.str, other.str, MAX_LENGTH);
    return result;
}

// Операторы сравнения
bool Stroka::operator==(const Stroka& other) const {
    return sravn_cstr(str, other.str) == 0;
}

bool Stroka::operator!=(const Stroka& other) const {
    return sravn_cstr(str, other.str) != 0;
}

bool Stroka::operator<(const Stroka& other) const {
    return sravn_cstr(str, other.str) < 0;
}

bool Stroka::operator>(const Stroka& other) const {
    return sravn_cstr(str, other.str) > 0;
}

bool Stroka::operator<=(const Stroka& other) const {
    return sravn_cstr(str, other.str) <= 0;
}

bool Stroka::operator>=(const Stroka& other) const {
    return sravn_cstr(str, other.str) >= 0;
}

// Методы для работы со строкой
int Stroka::dlina() const {
    return dlina_cstr(str);
}

void Stroka::vvod() {
    cin.getline(str, MAX_LENGTH);
    if (cin.fail()) {
        cin.clear();
        while (cin.get() != '\n') {
            // Пропускаем лишние символы
        }
    }
}

void Stroka::vyvod() const {
    int i = 0;
    while (str[i] != '\0') {
        cout << str[i];
        i++;
    }
}

const char* Stroka::c_str() const {
    return str;
}

bool Stroka::pusta() const {
    return str[0] == '\0';
}

// Оператор вывода
ostream& operator<<(ostream& os, const Stroka& s) {
    int i = 0;
    while (s.str[i] != '\0') {
        os << s.str[i];
        i++;
    }
    return os;
}

// Оператор ввода (читает одно слово до пробела)
istream& operator>>(istream& is, Stroka& s) {
    char buffer[MAX_LENGTH];
    int i = 0;
    char ch;

    // Пропускаем начальные пробелы
    while (is.get(ch) && isspace(static_cast<unsigned char>(ch))) {
        // Пропускаем пробельные символы
    }

    // Если нашли символ, сохраняем его
    if (is.good() && !isspace(static_cast<unsigned char>(ch))) {
        buffer[i++] = ch;

        // Читаем остальные символы до пробела
        while (is.get(ch) && !isspace(static_cast<unsigned char>(ch)) && i < MAX_LENGTH - 1) {
            buffer[i++] = ch;
        }

        // Если последний символ не пробел, возвращаем его в поток
        if (is.good() && !isspace(static_cast<unsigned char>(ch))) {
            is.putback(ch);
        }
    }

    buffer[i] = '\0';
    s = buffer;  // Используем оператор присваивания

    return is;
}

// Функция для чтения целой строки (с пробелами)
istream& getline(istream& is, Stroka& s) {
    char buffer[Stroka::MAX_LENGTH];

    if (is.getline(buffer, Stroka::MAX_LENGTH)) {
        s = buffer;
    }
    else {
        s = "";
        if (is.fail() && !is.eof()) {
            is.clear();
            // Пропускаем оставшиеся символы в строке
            while (is.get() != '\n' && !is.eof()) {
                // Пропускаем
            }
        }
    }

    return is;
}
