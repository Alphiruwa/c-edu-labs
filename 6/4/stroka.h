#ifndef STROKA_H
#define STROKA_H

#include <iostream>

class Stroka {
private:
    char* str;                      // Динамический массив для хранения символов
    int capacity;                   // Размер выделенной памяти
    int length;                     // Фактическая длина строки

public:
    // Конструкторы
    Stroka();                          // Конструктор по умолчанию
    Stroka(int size);                  // Конструктор с заданным размером
    Stroka(const char* string);        // Конструктор из C-строки
    Stroka(const Stroka& other);       // Конструктор копирования

    // Деструктор (ОБЯЗАТЕЛЕН при динамической памяти)
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
    int get_capacity() const;         // Получить размер выделенной памяти
    void ensure_capacity(int min_capacity); // Гарантировать минимальную емкость

    // Дружественные функции для ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Stroka& s);
    friend std::istream& operator>>(std::istream& is, Stroka& s);

private:
    // Вспомогательные функции (вместо библиотечных)
    static int dlina_cstr(const char* str);          // Длина C-строки
    static int sravn_cstr(const char* str1, const char* str2); // Сравнение

    // Вспомогательные методы для работы с динамической памятью
    void init_from_cstr(const char* string);         // Инициализация из C-строки
    void cleanup();                                  // Очистка памяти
    void copy_from(const Stroka& other);             // Копирование из другого объекта
};

#endif // STROKA_H
