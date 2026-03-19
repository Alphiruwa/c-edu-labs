#ifndef STROKA_H
#define STROKA_H

#include <iostream>

class Stroka {
private:
    static const int MAX_LENGTH = 80;  // Максимальная длина строки
    char str[MAX_LENGTH];             // Массив для хранения символов

public:
    // Конструкторы
    Stroka();                          // Конструктор по умолчанию
    Stroka(const char* string);        // Конструктор из C-строки
    Stroka(const Stroka& other);       // Конструктор копирования

    // Деструктор
    ~Stroka();

    // Операторы
    Stroka& operator=(const Stroka& other);          // Оператор присваивания
    Stroka& operator=(const char* string);           // Присваивание C-строки
    Stroka operator+(const Stroka& other) const;     // Оператор сложения (конкатенация)
    bool operator==(const Stroka& other) const;      // Оператор сравнения на равенство
    bool operator!=(const Stroka& other) const;      // Оператор сравнения на неравенство

    // Методы
    int dlina() const;                // Определение длины строки
    void vvod();                      // Ввод строки
    void vyvod() const;               // Вывод строки

    // Дополнительные полезные методы
    const char* c_str() const;        // Получить C-строку
    bool pusta() const;               // Проверка на пустоту

    // Дружественные функции для ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Stroka& s);
    friend std::istream& operator>>(std::istream& is, Stroka& s);
};

#endif // STROKA_H

#pragma once
