#include <iostream>
#include <string.h>
#include <clocale>

void main() {
	setlocale(LC_ALL, "");
	
    // Исходные строки
    char str1[100] = "Hello, ";
    char str2[] = "World!";
    char str3[100];
    char str4[] = "Hello, World!";

    std::cout << "=== Демонстрация работы со строками ===\n\n";

    // 1. Использование strlen() - определение длины строки
    std::cout << "1. Функция strlen() - определение длины строки:\n";
    std::cout << "   Длина str1 (\"" << str1 << "\"): " << strlen(str1) << " символов\n";
    std::cout << "   Длина str2 (\"" << str2 << "\"): " << strlen(str2) << " символов\n\n";

    // 2. Использование strcat() - конкатенация строк
    std::cout << "2. Функция strcat() - конкатенация строк:\n";
    std::cout << "   До конкатенации: str1 = \"" << str1 << "\"\n";
    strcat_s(str1, str2);  // Добавляем str2 к str1
    std::cout << "   После strcat(str1, str2): str1 = \"" << str1 << "\"\n\n";

    // 3. Использование strcpy() - копирование строк
    std::cout << "3. Функция strcpy() - копирование строк:\n";
    std::cout << "   До копирования: str3 = \"" << str3 << "\"\n";
    strcpy_s(str3, str1);  // Копируем str1 в str3
    std::cout << "   После strcpy(str3, str1): str3 = \"" << str3 << "\"\n\n";

    // 4. Использование strcmp() - сравнение строк
    std::cout << "4. Функция strcmp() - сравнение строк:\n";

    // Сравниваем str1 и str3 (они должны быть равны)
    int result1 = strcmp(str1, str3);
    std::cout << "   Сравнение str1 и str3: ";
    if (result1 == 0) {
        std::cout << "строки идентичны\n";
    }
    else if (result1 < 0) {
        std::cout << "str1 меньше str3\n";
    }
    else {
        std::cout << "str1 больше str3\n";
    }

    // Сравниваем str1 и str4
    int result2 = strcmp(str1, str4);
    std::cout << "   Сравнение str1 и str4: ";
    if (result2 == 0) {
        std::cout << "строки идентичны\n";
    }
    else if (result2 < 0) {
        std::cout << "str1 меньше str4\n";
    }
    else {
        std::cout << "str1 больше str4\n";
    }

    // Сравниваем "Apple" и "Banana" (лексикографическое сравнение)
    char fruit1[] = "Apple";
    char fruit2[] = "Banana";
    int result3 = strcmp(fruit1, fruit2);
    std::cout << "   Сравнение \"Apple\" и \"Banana\": ";
    if (result3 == 0) {
        std::cout << "строки идентичны\n";
    }
    else if (result3 < 0) {
        std::cout << "\"Apple\" меньше \"Banana\" (т.к. 'A' < 'B' в ASCII)\n";
    }
    else {
        std::cout << "\"Apple\" больше \"Banana\"\n";
    }
}
