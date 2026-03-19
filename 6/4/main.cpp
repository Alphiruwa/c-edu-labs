#include "Stroka.h"
#include <iostream>
#include <clocale>

using namespace std;

void test_dynamic_memory() {
    cout << "=== Тестирование динамической памяти ===\n\n";

    // Тест 1: Конструктор с заданным размером
    cout << "1. Конструктор с заданным размером:\n";
    Stroka s1(50);  // Создаем строку с емкостью 50 символов
    cout << "   Емкость s1: " << s1.get_capacity() << endl;
    cout << "   Длина s1: " << s1.dlina() << endl;
    cout << "   Содержимое: '" << s1 << "'\n\n";

    // Тест 2: Заполнение строки
    cout << "2. Заполнение строки:\n";
    s1 = "Привет, мир!";
    cout << "   После присваивания: '" << s1 << "'\n";
    cout << "   Длина: " << s1.dlina() << endl;
    cout << "   Емкость: " << s1.get_capacity() << endl << endl;

    // Тест 3: Конструктор копирования с динамической памятью
    cout << "3. Конструктор копирования:\n";
    Stroka s2 = s1;  // Используется конструктор копирования
    cout << "   s2 (копия s1): '" << s2 << "'\n";
    cout << "   Длина s2: " << s2.dlina() << endl;
    cout << "   Емкость s2: " << s2.get_capacity() << endl << endl;

    // Тест 4: Присваивание
    cout << "4. Оператор присваивания:\n";
    Stroka s3(10);
    s3 = s1;
    cout << "   s3 (после присваивания s1): '" << s3 << "'\n";
    cout << "   Емкость s3: " << s3.get_capacity() << endl << endl;

    // Тест 5: Автоматическое расширение памяти
    cout << "5. Автоматическое расширение памяти:\n";
    Stroka s4(5);  // Маленькая емкость
    cout << "   Начальная емкость s4: " << s4.get_capacity() << endl;

    s4 = "Очень длинная строка, которая не поместится в начальную емкость";
    cout << "   Содержимое s4: '" << s4 << "'\n";
    cout << "   Длина s4: " << s4.dlina() << endl;
    cout << "   Новая емкость s4: " << s4.get_capacity() << endl << endl;

    // Тест 6: Конкатенация с динамическим расширением
    cout << "6. Конкатенация с динамическим расширением:\n";
    Stroka s5("Начало ");
    Stroka s6("и продолжение строки");

    Stroka s7 = s5 + s6;
    cout << "   s5: '" << s5 << "' (емкость: " << s5.get_capacity() << ")\n";
    cout << "   s6: '" << s6 << "' (емкость: " << s6.get_capacity() << ")\n";
    cout << "   s7 = s5 + s6: '" << s7 << "'\n";
    cout << "   Длина s7: " << s7.dlina() << endl;
    cout << "   Емкость s7: " << s7.get_capacity() << endl << endl;

    // Тест 7: Цепочка операций
    cout << "7. Цепочка операций:\n";
    Stroka s8("A");
    Stroka s9("B");
    Stroka s10("C");

    Stroka result = s8 + s9 + s10 + "D" + "E";
    cout << "   Результат цепочки: '" << result << "'\n";
    cout << "   Длина: " << result.dlina() << endl;
    cout << "   Емкость: " << result.get_capacity() << endl << endl;

    // Тест 8: Ввод с клавиатуры
    cout << "8. Ввод с клавиатуры:\n";
    Stroka input_str(20);
    cout << "   Введите строку (метод vvod()): ";
    input_str.vvod();
    cout << "   Вы ввели: '" << input_str << "'\n";
    cout << "   Длина: " << input_str.dlina() << endl;
    cout << "   Емкость: " << input_str.get_capacity() << endl << endl;

    // Тест 9: Проверка деструктора (косвенно)
    cout << "9. Проверка работы в области видимости:\n";
    {
        Stroka local_str(100);
        local_str = "Локальная строка, которая будет уничтожена при выходе из блока";
        cout << "   Внутри блока: '" << local_str << "'\n";
    }
    cout << "   Вне блока: локальная строка уничтожена (деструктор вызван)\n\n";

    // Тест 10: Сравнение строк
    cout << "10. Сравнение строк:\n";
    Stroka a("abc");
    Stroka b("abc");
    Stroka c("abd");

    cout << "   a = '" << a << "', b = '" << b << "', c = '" << c << "'\n";
    cout << "   a == b? " << (a == b ? "Да" : "Нет") << endl;
    cout << "   a == c? " << (a == c ? "Да" : "Нет") << endl;
    cout << "   a != c? " << (a != c ? "Да" : "Нет") << endl;
}

int main() {
    setlocale(LC_ALL, "");

    test_dynamic_memory();
    return 0;
}
