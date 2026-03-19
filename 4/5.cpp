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
char* konkat(char* dest, const char* src) {  // Изменено на const char*
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

// Функция для вывода массива строк
void print_string_array(char** arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << "str[" << i << "] = \"" << arr[i] << "\" (длина: " << dlinal(arr[i]) << ")" << std::endl;
    }
}

void main() {
	setlocale(LC_ALL, "");
	
    const int NUM_STRINGS = 5;
    const int MAX_LENGTH = 50;

    // Создаем массив указателей на строки
    char** strings = (char**)calloc(NUM_STRINGS, sizeof(char*));

    if (!strings) {
        std::cout << "Ошибка выделения памяти для массива строк!" << std::endl;
        return;
    }

    // Выделяем память для каждой строки
    for (int i = 0; i < NUM_STRINGS; i++) {
        strings[i] = (char*)calloc(MAX_LENGTH, sizeof(char));
        if (!strings[i]) {
            std::cout << "Ошибка выделения памяти для строки " << i << "!" << std::endl;
            return;
        }
    }

    // Инициализируем строки
    strcpy_s(strings[0], MAX_LENGTH, "Apple");
    strcpy_s(strings[1], MAX_LENGTH, "Banana");
    strcpy_s(strings[2], MAX_LENGTH, "Cherry");
    strcpy_s(strings[3], MAX_LENGTH, "Date");
    strcpy_s(strings[4], MAX_LENGTH, "Elderberry");

    std::cout << "=== Исходный массив строк ===" << std::endl;
    print_string_array(strings, NUM_STRINGS);
    std::cout << std::endl;

    // 1. Демонстрация функций длины строк
    std::cout << "=== Демонстрация функций длины строк ===" << std::endl;
    for (int i = 0; i < NUM_STRINGS; i++) {
        std::cout << "Строка \"" << strings[i] << "\":" << std::endl;
        std::cout << "  dlinal(): " << dlinal(strings[i]) << std::endl;
        std::cout << "  dlina2(): " << dlina2(strings[i]) << std::endl;
        std::cout << "  dlina3(): " << dlina3(strings[i]) << std::endl;
    }
    std::cout << std::endl;

    // 2. Демонстрация копирования строк
    std::cout << "=== Демонстрация копирования строк ===" << std::endl;
    std::cout << "Копируем strings[0] в strings[3]..." << std::endl;
    std::cout << "До копирования: strings[3] = \"" << strings[3] << "\"" << std::endl;
    kopir(strings[3], strings[0]);
    std::cout << "После копирования: strings[3] = \"" << strings[3] << "\"" << std::endl;
    std::cout << std::endl;

    // 3. Демонстрация сравнения строк
    std::cout << "=== Демонстрация сравнения строк ===" << std::endl;
    std::cout << "Сравнение strings[0] и strings[1]:" << std::endl;
    std::cout << "  sravn(\"" << strings[0] << "\", \"" << strings[1] << "\") = "
        << sravn(strings[0], strings[1]) << std::endl;

    std::cout << "Сравнение strings[1] и strings[0]:" << std::endl;
    std::cout << "  sravn(\"" << strings[1] << "\", \"" << strings[0] << "\") = "
        << sravn(strings[1], strings[0]) << std::endl;

    std::cout << "Сравнение strings[0] и strings[3] (после копирования):" << std::endl;
    std::cout << "  sravn(\"" << strings[0] << "\", \"" << strings[3] << "\") = "
        << sravn(strings[0], strings[3]) << std::endl;
    std::cout << std::endl;

    // 4. Демонстрация конкатенации строк
    std::cout << "=== Демонстрация конкатенации строк ===" << std::endl;

    // Создаем дополнительную строку для конкатенации
    char* temp_str = (char*)calloc(MAX_LENGTH * 2, sizeof(char));
    if (!temp_str) {
        std::cout << "Ошибка выделения памяти для временной строки!" << std::endl;
        return;
    }

    strcpy_s(temp_str, MAX_LENGTH * 2, "Fruit: ");
    std::cout << "До конкатенации: temp_str = \"" << temp_str << "\"" << std::endl;
    konkat(temp_str, strings[1]);
    std::cout << "После конкатенации с \"" << strings[1] << "\": temp_str = \"" << temp_str << "\"" << std::endl;

    // Конкатенация нескольких строк
    char* multi_str = (char*)calloc(MAX_LENGTH * 3, sizeof(char));
    if (!multi_str) {
        std::cout << "Ошибка выделения памяти для многострочной строки!" << std::endl;
        free(temp_str);
        return;
    }

    strcpy_s(multi_str, MAX_LENGTH * 3, "Фрукты: ");

    // Создаем временные строки для разделителей
    char comma_space[3] = ", ";
    char space[2] = " ";

    for (int i = 0; i < 3; i++) {
        konkat(multi_str, strings[i]);
        if (i < 2) {
            konkat(multi_str, comma_space);
        }
    }
    std::cout << "Конкатенация первых трех строк: \"" << multi_str << "\"" << std::endl;
    std::cout << std::endl;

    // 5. Обновленный массив строк
    std::cout << "=== Обновленный массив строк ===" << std::endl;
    print_string_array(strings, NUM_STRINGS);

    // 6. Поиск самой длинной строки в массиве
    std::cout << "\n=== Поиск самой длинной строки в массиве ===" << std::endl;
    int max_length = 0;
    int longest_index = 0;

    for (int i = 0; i < NUM_STRINGS; i++) {
        int len = dlinal(strings[i]);
        if (len > max_length) {
            max_length = len;
            longest_index = i;
        }
    }

    std::cout << "Самая длинная строка: strings[" << longest_index << "] = \""
        << strings[longest_index] << "\" (длина: " << max_length << ")" << std::endl;

    // Освобождение памяти
    for (int i = 0; i < NUM_STRINGS; i++) {
        free(strings[i]);
    }
    free(strings);
    free(temp_str);
    free(multi_str);

    return;
}