#ifndef STROKA_H
#define STROKA_H

#include <iostream>

class Stroka {
private:
    static const int MAX_LENGTH = 256;  // Максимальная длина строки
    char str[MAX_LENGTH];               // Массив для хранения строки

    // Вспомогательные функции для работы с C-строками
    static int dlina_cstr(const char* str);
    static void kopir_cstr(char* dest, const char* src, int max_len);
    static int sravn_cstr(const char* str1, const char* str2);
    static void konkat_cstr(char* dest, const char* src, int max_len);

public:
    // Конструкторы
    Stroka();
    Stroka(const char* string);
    Stroka(const Stroka& other);

    // Деструктор
    ~Stroka();

    // Операторы присваивания
    Stroka& operator=(const Stroka& other);
    Stroka& operator=(const char* string);

    // Операторы арифметические
    Stroka operator+(const Stroka& other) const;

    // Операторы сравнения
    bool operator==(const Stroka& other) const;
    bool operator!=(const Stroka& other) const;
    bool operator<(const Stroka& other) const;
    bool operator>(const Stroka& other) const;
    bool operator<=(const Stroka& other) const;
    bool operator>=(const Stroka& other) const;

    // Методы для работы со строкой
    int dlina() const;
    void vvod();
    void vyvod() const;
    const char* c_str() const;
    bool pusta() const;

    // Дружественные операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Stroka& s);
    friend std::istream& operator>>(std::istream& is, Stroka& s);

    // Дополнительный метод для чтения строки с пробелами
    friend std::istream& getline(std::istream& is, Stroka& s);
};

// Объявление операторов ввода/вывода
std::ostream& operator<<(std::ostream& os, const Stroka& s);
std::istream& operator>>(std::istream& is, Stroka& s);
std::istream& getline(std::istream& is, Stroka& s);

#endif // STROKA_H
