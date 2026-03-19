#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    // Проверяем количество аргументов командной строки
    if (argc != 4) {
        cout << "Использование: " << argv[0]
            << " <входной_файл> <выходной_файл> <ключ>" << endl;
        cout << "Пример: " << argv[0]
            << " input.txt output.txt secretkey" << endl;
        return 1;
    }

    // Получаем параметры из командной строки
    string input_filename = argv[1];
    string output_filename = argv[2];
    string key = argv[3];

    // Создаем объекты потоков без открытия файлов (конструктор по умолчанию)
    ifstream input_file;
    ofstream output_file;

    // Открываем входной файл в бинарном режиме (раздел 5.2)
    input_file.open(input_filename.c_str(), ios::in | ios::binary);

    // Проверка состояния потока с использованием оператора void* (раздел 4.1)
    if (!input_file) {
        cerr << "Ошибка: не удалось открыть входной файл '"
            << input_filename << "'" << endl;
        return 1;
    }

    // Открываем выходной файл в бинарном режиме
    output_file.open(output_filename.c_str(), ios::out | ios::binary | ios::trunc);

    if (!output_file) {
        cerr << "Ошибка: не удалось открыть выходной файл '"
            << output_filename << "'" << endl;
        input_file.close();
        return 1;
    }

    // Читаем файл посимвольно и шифруем
    char ch;
    size_t key_index = 0;
    size_t key_length = key.length();

    // Используем цикл с проверкой состояния потока (раздел 4.1)
    while (input_file && output_file) {
        // Используем метод get() для чтения символа (раздел 6.4)
        if (input_file.get(ch)) {
            // Применяем XOR с текущим символом ключа
            char encrypted_char = ch ^ key[key_index];

            // Используем метод put() для записи символа
            output_file.put(encrypted_char);

            // Переходим к следующему символу ключа (циклически)
            key_index = (key_index + 1) % key_length;
        }
        else {
            // Проверяем причину окончания чтения
            if (input_file.eof()) {
                // Нормальное завершение - достигнут конец файла
                break;
            }
            else if (input_file.fail() || input_file.bad()) {
                cerr << "Ошибка при чтении из входного файла!" << endl;
                break;
            }
        }
    }

    // Проверяем, не установлены ли флаги ошибок (раздел 4.2)
    if (input_file.bad() || output_file.bad()) {
        cerr << "Произошла критическая ошибка ввода/вывода!" << endl;
    }
    else if (input_file.fail() && !input_file.eof()) {
        cerr << "Произошла ошибка форматирования!" << endl;
    }

    // Закрываем файлы
    input_file.close();
    output_file.close();

    // Используем манипулятор endl для сброса буфера (раздел 3.3.1)
    cout << "Файл успешно обработан." << endl;
    cout << "Для проверки запустите программу еще раз с теми же параметрами." << endl;

    return 0;
}
