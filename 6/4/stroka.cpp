#include "Stroka.h"
#include <iostream>
#include <limits>

using namespace std;

// Реализация собственных функций

int Stroka::dlina_cstr(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int Stroka::sravn_cstr(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

// Вспомогательные методы для работы с динамической памятью

void Stroka::cleanup() {
    if (str != nullptr) {
        delete[] str;
        str = nullptr;
    }
    capacity = 0;
    length = 0;
}

void Stroka::init_from_cstr(const char* string) {
    if (string == nullptr) {
        length = 0;
        capacity = 1;  // Минимальная емкость для пустой строки
        str = new char[capacity];
        str[0] = '\0';
    }
    else {
        length = dlina_cstr(string);
        capacity = length + 1;  // +1 для завершающего нуля
        str = new char[capacity];

        // Копируем строку
        int i = 0;
        while (string[i] != '\0') {
            str[i] = string[i];
            i++;
        }
        str[i] = '\0';
    }
}

void Stroka::copy_from(const Stroka& other) {
    length = other.length;
    capacity = other.capacity;
    str = new char[capacity];

    // Копируем символы
    for (int i = 0; i <= length; i++) {  // <= чтобы скопировать завершающий ноль
        str[i] = other.str[i];
    }
}

void Stroka::ensure_capacity(int min_capacity) {
    if (capacity >= min_capacity) {
        return;
    }

    // Увеличиваем емкость (простая стратегия - удваивание)
    int new_capacity = capacity * 2;
    if (new_capacity < min_capacity) {
        new_capacity = min_capacity;
    }

    char* new_str = new char[new_capacity];

    // Копируем старую строку
    for (int i = 0; i <= length; i++) {
        new_str[i] = str[i];
    }

    // Освобождаем старую память
    delete[] str;

    // Обновляем указатель и емкость
    str = new_str;
    capacity = new_capacity;
}

// Конструктор по умолчанию
Stroka::Stroka() : str(nullptr), capacity(0), length(0) {
    // Выделяем минимальную память для пустой строки
    capacity = 1;
    str = new char[capacity];
    str[0] = '\0';
    length = 0;
}

// Конструктор с заданным размером
Stroka::Stroka(int size) {
    if (size < 1) {
        size = 1;  // Минимальный размер
    }

    capacity = size;
    length = 0;
    str = new char[capacity];
    str[0] = '\0';
}

// Конструктор из C-строки
Stroka::Stroka(const char* string) {
    init_from_cstr(string);
}

// Конструктор копирования
Stroka::Stroka(const Stroka& other) {
    copy_from(other);
}

// Деструктор (ОБЯЗАТЕЛЕН!)
Stroka::~Stroka() {
    cleanup();
}

// Оператор присваивания для объектов Stroka
Stroka& Stroka::operator=(const Stroka& other) {
    if (this != &other) {  // Защита от самоприсваивания
        // Освобождаем старую память
        cleanup();
        // Копируем данные
        copy_from(other);
    }
    return *this;
}

// Оператор присваивания для C-строк
Stroka& Stroka::operator=(const char* string) {
    // Освобождаем старую память
    cleanup();
    // Инициализируем из C-строки
    init_from_cstr(string);
    return *this;
}

// Оператор сложения (конкатенация)
Stroka Stroka::operator+(const Stroka& other) const {
    // Создаем результат с достаточной емкостью
    Stroka result(length + other.length + 1);

    // Копируем первую строку
    int i = 0;
    while (str[i] != '\0') {
        result.str[i] = str[i];
        i++;
    }

    // Копируем вторую строку
    int j = 0;
    while (other.str[j] != '\0') {
        result.str[i] = other.str[j];
        i++;
        j++;
    }

    result.str[i] = '\0';
    result.length = i;

    return result;
}

// Оператор сравнения на равенство
bool Stroka::operator==(const Stroka& other) const {
    return sravn_cstr(str, other.str) == 0;
}

// Оператор сравнения на неравенство
bool Stroka::operator!=(const Stroka& other) const {
    return sravn_cstr(str, other.str) != 0;
}

// Определение длины строки
int Stroka::dlina() const {
    return length;
}

// Ввод строки
void Stroka::vvod() {
    const int BUFFER_SIZE = 1024;  // Буфер для чтения
    char buffer[BUFFER_SIZE];

    cin.getline(buffer, BUFFER_SIZE);

    // Определяем длину введенной строки
    int input_length = 0;
    while (buffer[input_length] != '\0' && input_length < BUFFER_SIZE - 1) {
        input_length++;
    }

    // Очищаем буфер ввода при необходимости
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Гарантируем достаточную емкость
    ensure_capacity(input_length + 1);

    // Копируем строку
    for (int i = 0; i < input_length; i++) {
        str[i] = buffer[i];
    }
    str[input_length] = '\0';
    length = input_length;
}

// Вывод строки
void Stroka::vyvod() const {
    int i = 0;
    while (str[i] != '\0') {
        cout << str[i];
        i++;
    }
}

// Получить C-строку
const char* Stroka::c_str() const {
    return str;
}

// Проверка на пустоту
bool Stroka::pusta() const {
    return length == 0;
}

// Получить размер выделенной памяти
int Stroka::get_capacity() const {
    return capacity;
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

// Оператор ввода
istream& operator>>(istream& is, Stroka& s) {
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    // Используем метод get для безопасного чтения
    int i = 0;
    char ch;

    // Пропускаем начальные пробелы
    while (is.get(ch) && (ch == ' ' || ch == '\t' || ch == '\n')) {
        // Пропускаем пробельные символы
    }

    // Если получили символ, сохраняем его
    if (!is.fail() && ch != ' ' && ch != '\t' && ch != '\n') {
        buffer[i++] = ch;
    }

    // Читаем до пробела или конца строки
    while (is.get(ch) && ch != ' ' && ch != '\t' && ch != '\n' && i < BUFFER_SIZE - 1) {
        buffer[i++] = ch;
    }

    buffer[i] = '\0';

    // Устанавливаем строку
    s = buffer;  // Используем оператор присваивания

    return is;
}

