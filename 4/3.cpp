#include <iostream>
#include <cstdlib>
#include <cstring>
#include <clocale>

// Способ 1: Определение длины строки с помощью индексации массива
int dlinal(char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Способ 2: Определение длины строки с помощью указателей
int dlina2(char* str) {
    int length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

// Способ 3: Определение длины строки с помощью одного указателя
int dlina3(char* str) {
    char* p = str;
    while (*p != '\0') {
        p++;
    }
    return p - str;
}

// Функция копирования строк
char* kopir(char* dest, char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

// Функция сравнения строк
int sravn(char* str1, char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

// Функция конкатенации строк
char* konkat(char* dest, char* src) {
    // Находим конец строки dest
    int i = 0;
    while (dest[i] != '\0') {
        i++;
    }

    // Копируем src в конец dest
    int j = 0;
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return dest;
}

void main() {
	setlocale(LC_ALL, "");
	
    // Выделение динамической памяти для строк
    char* str1 = (char*)malloc(100);
    char* str2 = (char*)malloc(100);
    char* str3 = (char*)malloc(100);
    char* str4 = (char*)malloc(100);
    char* str5 = (char*)malloc(100);

    // Инициализация строк
    strcpy_s(str1, 100, "qwerty");
    strcpy_s(str2, 100, "1234567890");
    str3[0] = '\0';  // Пустая строка
    strcpy_s(str4, 100, "Hello");
    strcpy_s(str5, 100, "World");

    // Использование функций длины строки
    std::cout << "длина str1=" << dlinal(str1) << ", str2=";
    std::cout << dlinal(str2) << std::endl;

    std::cout << "длина str1=" << dlina2(str1) << ", str2=";
    std::cout << dlina2(str2) << std::endl;

    std::cout << "длина str1=" << dlina3(str1) << ", str2=";
    std::cout << dlina3(str2) << std::endl;

    // Копирование строк
    kopir(str3, str1);
    std::cout << "результат копирования: str3=" << str3;
    std::cout << ", str1=" << str1 << std::endl;

    // Сравнение строк
    int result = sravn(str1, str2);
    std::cout << "результат сравнения str1 и str2: " << result << std::endl;

    // Конкатенация строк
    konkat(str4, str5);
    std::cout << "результат сцепления: str4=" << str4;
    std::cout << ", str5=" << str5 << std::endl;

    // Освобождение динамической памяти
    free(str1);
    free(str2);
    free(str3);
    free(str4);
    free(str5);
}
