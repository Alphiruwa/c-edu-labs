#include "Stroka.h"
#include <iostream>
#include <clocale>

using namespace std;

// Тест собственных функций (для демонстрации)
void test_custom_functions() {
    cout << "=== Тест собственных функций ===\n";

    // Тест определения длины
    char test1[] = "Hello";
    char test2[] = "";
    char test3[] = "1234567890";

    cout << "Длина '" << test1 << "': " << Stroka::dlina_cstr(test1) << endl;
    cout << "Длина '" << test2 << "': " << Stroka::dlina_cstr(test2) << endl;
    cout << "Длина '" << test3 << "': " << Stroka::dlina_cstr(test3) << endl;

    // Тест копирования
    char dest1[20] = "";
    char src1[] = "Test copy";
    Stroka::kopir_cstr(dest1, src1, 20);
    cout << "Копирование: dest = '" << dest1 << "'\n";

    // Тест сравнения
    char str1[] = "abc";
    char str2[] = "abc";
    char str3[] = "abd";
    char str4[] = "ab";

    cout << "Сравнение 'abc' и 'abc': " << Stroka::sravn_cstr(str1, str2) << endl;
    cout << "Сравнение 'abc' и 'abd': " << Stroka::sravn_cstr(str1, str3) << endl;
    cout << "Сравнение 'abc' и 'ab': " << Stroka::sravn_cstr(str1, str4) << endl;

    // Тест конкатенации
    char dest2[20] = "Hello ";
    char src2[] = "World!";
    Stroka::konkat_cstr(dest2, src2, 20);
    cout << "Конкатенация: dest = '" << dest2 << "'\n";

    cout << "================================\n\n";
}

int main() {
    setlocale(LC_ALL, "");

    // Демонстрация собственных функций
    test_custom_functions();

    // Тестирование класса Stroka
    cout << "=== Тестирование класса Stroka ===\n";

    // Тестирование конструкторов
    Stroka s1("qwert");
    Stroka s2;          // Пустая строка
    Stroka s3(s1);      // Конструктор копирования
    Stroka s4;
    Stroka s5;

    cout << "s1: " << s1 << endl;
    cout << "s2 (пустая): " << s2 << endl;
    cout << "Длина s2: " << s2.dlina() << endl;
    cout << "s3 (копия s1): " << s3 << endl;

    // Тестирование ввода
    cout << "\nВведите строку для s2: ";
    s2.vvod();
    cout << "Вы ввели: " << s2 << endl;
    cout << "Длина введенной строки: " << s2.dlina() << endl;

    // Тестирование присваивания
    s4 = "asdfg";
    cout << "\ns4 после присваивания C-строки: " << s4 << endl;

    s4 = s2;  // Присваивание объекта
    cout << "s4 после присваивания s2: " << s4 << endl;

    // Тестирование конкатенации
    s5 = s1 + s4 + s3;
    cout << "\ns5 = s1 + s4 + s3: " << s5 << endl;
    cout << "Длина s5 = " << s5.dlina() << endl;

    // Тестирование сравнения
    cout << "\nТестирование сравнения:\n";
    if (s1 == s5) {
        cout << "Строки s1 и s5 равны" << endl;
    }
    else {
        cout << "Строки s1 и s5 не равны" << endl;
    }

    if (s1 == s3) {
        cout << "Строки s1 и s3 равны" << endl;
    }
    else {
        cout << "Строки s1 и s3 не равны" << endl;
    }

    // Тестирование оператора неравенства
    if (s1 != s2) {
        cout << "Строки s1 и s2 не равны" << endl;
    }

    // Тестирование дополнительных методов
    cout << "\nC-строка s1: " << s1.c_str() << endl;
    cout << "s2 пустая? " << (s2.pusta() ? "Да" : "Нет") << endl;

    // Тестирование предельных случаев
    cout << "\n=== Тестирование предельных случаев ===\n";

    // Создание длинной строки
    Stroka long1("1234567890123456789012345678901234567890");
    Stroka long2("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    cout << "Длинная строка 1: " << long1 << endl;
    cout << "Длина: " << long1.dlina() << endl;

    Stroka result = long1 + long2;
    cout << "Конкатенация двух длинных строк: " << result << endl;
    cout << "Длина результата: " << result.dlina() << endl;

    // Тестирование операторов ввода/вывода
    Stroka s6;
    cout << "\nВведите строку для s6 (через оператор >>, до пробела): ";
    cin >> s6;
    cout << "s6: " << s6 << endl;
    cout << "Длина s6: " << s6.dlina() << endl;

    return 0;
}
