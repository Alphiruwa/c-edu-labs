#include "Stroka.h"
#include <iostream>
#include <clocale>
#include <windows.h>

int main() {    
    setlocale(LC_ALL, "");

    // Тестирование конструкторов
    Stroka s1("qwert");
    Stroka s2;          // Пустая строка
    Stroka s3(s1);      // Конструктор копирования
    Stroka s4;
    Stroka s5;

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2 (пустая): " << s2 << std::endl;
    std::cout << "s3 (копия s1): " << s3 << std::endl;

    // Тестирование ввода
    std::cout << "\nВведите строку для s2: ";
    s2.vvod();
    std::cout << "Вы ввели: " << s2 << std::endl;

    // Тестирование присваивания
    s4 = "asdfg";
    std::cout << "s4 после присваивания: " << s4 << std::endl;

    s4 = s2;  // Присваивание объекта
    std::cout << "s4 после присваивания s2: " << s4 << std::endl;

    // Тестирование конкатенации
    s5 = s1 + s4 + s3;
    std::cout << "\ns5 = s1 + s4 + s3: " << s5 << std::endl;
    std::cout << "Длина s5 = " << s5.dlina() << std::endl;

    // Тестирование сравнения
    if (s1 == s5) {
        std::cout << "Строки s1 и s5 равны" << std::endl;
    }
    else if (s1 == s3) {
        std::cout << "Строки s1 и s3 равны" << std::endl;
    }
    else {
        std::cout << "Строки s1 и s3 не равны" << std::endl;
    }

    // Тестирование оператора неравенства
    if (s1 != s2) {
        std::cout << "Строки s1 и s2 не равны" << std::endl;
    }

    // Тестирование дополнительных методов
    std::cout << "\nC-строка s1: " << s1.c_str() << std::endl;
    std::cout << "s2 пустая? " << (s2.pusta() ? "Да" : "Нет") << std::endl;

    // Тестирование операторов ввода/вывода
    Stroka s6;
    std::cout << "\nВведите строку для s6 (через оператор >>): ";
    std::cin >> s6;
    std::cout << "s6: " << s6 << std::endl;

    return 0;
}
