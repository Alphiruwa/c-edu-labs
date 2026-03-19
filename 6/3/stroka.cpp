#include "Stroka.h"
#include <iostream>

using namespace std;

// Реализация собственных функций вместо библиотечных

// Функция определения длины строки (способ 1 с индексацией)
int Stroka::dlina_cstr(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Функция копирования строк
void Stroka::kopir_cstr(char* dest, const char* src, int max_len) {
    int i = 0;
    // Копируем символы, но не превышаем max_len-1
    while (src[i] != '\0' && i < max_len - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  // Всегда добавляем завершающий ноль
}

// Функция сравнения строк
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

// Функция конкатенации строк
void Stroka::konkat_cstr(char* dest, const char* src, int max_len) {
    // Находим конец строки dest
    int i = 0;
    while (dest[i] != '\0' && i < max_len) {
        i++;
    }

    // Если dest уже заполнена до предела, ничего не делаем
    if (i >= max_len - 1) {
        return;
    }

    // Копируем src в конец dest
    int j = 0;
    while (src[j] != '\0' && i < max_len - 1) {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';  // Всегда добавляем завершающий ноль
}

// Реализация методов класса

// Конструктор по умолчанию
Stroka::Stroka() {
    str[0] = '\0';  // Пустая строка
}

// Конструктор из C-строки
Stroka::Stroka(const char* string) {
    if (string != nullptr) {
        kopir_cstr(str, string, MAX_LENGTH);
    }
    else {
        str[0] = '\0';
    }
}

// Конструктор копирования
Stroka::Stroka(const Stroka& other) {
    kopir_cstr(str, other.str, MAX_LENGTH);
}

// Деструктор
Stroka::~Stroka() {
    // В данном случае деструктор пустой, так как нет динамической памяти
}

// Оператор присваивания для объектов Stroka
Stroka& Stroka::operator=(const Stroka& other) {
    if (this != &other) {  // Защита от самоприсваивания
        kopir_cstr(str, other.str, MAX_LENGTH);
    }
    return *this;
}

// Оператор присваивания для C-строк
Stroka& Stroka::operator=(const char* string) {
    if (string != nullptr) {
        kopir_cstr(str, string, MAX_LENGTH);
    }
    else {
        str[0] = '\0';
    }
    return *this;
}

// Оператор сложения (конкатенация)
Stroka Stroka::operator+(const Stroka& other) const {
    Stroka result(*this);  // Создаем копию текущего объекта
    konkat_cstr(result.str, other.str, MAX_LENGTH);
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
    return dlina_cstr(str);
}

// Ввод строки
void Stroka::vvod() {
    // Используем cin.getline с ограничением длины
    cin.getline(str, MAX_LENGTH);
    // Очищаем буфер, если ввод был больше максимальной длины
    if (cin.fail()) {
        cin.clear();
        // Пропускаем оставшиеся символы до конца строки
        while (cin.get() != '\n') {
            // Продолжаем пропускать
        }
    }
}

// Вывод строки
void Stroka::vyvod() const {
    // Выводим посимвольно
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
    return str[0] == '\0';
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
    char buffer[Stroka::MAX_LENGTH];

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
    while (is.get(ch) && ch != ' ' && ch != '\t' && ch != '\n' && i < Stroka::MAX_LENGTH - 1) {
        buffer[i++] = ch;
    }

    buffer[i] = '\0';

    // Если прочитали что-то, сохраняем в объект
    if (i > 0) {
        s = buffer;  // Используем оператор присваивания
    }
    else {
        s = "";      // Пустая строка
    }

    return is;
}
