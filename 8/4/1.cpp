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

    // Демонстрация 1: Проверка состояния потока до открытия (раздел 4.1)
    cout << "\n=== Демонстрация работы с состояниями потоков ===" << endl;

    ifstream test_stream;
    cout << "1. Проверка состояния потока до открытия файла:" << endl;
    cout << "   test_stream.good() = " << test_stream.good() << endl;
    cout << "   test_stream.eof() = " << test_stream.eof() << endl;
    cout << "   test_stream.fail() = " << test_stream.fail() << endl;
    cout << "   test_stream.bad() = " << test_stream.bad() << endl;

    // Использование оператора void*() для проверки состояния (раздел 4.1, Таблица 9)
    if (test_stream) {
        cout << "   Поток в нормальном состоянии (test_stream вернул true)" << endl;
    }
    else {
        cout << "   Поток в ошибочном состоянии (test_stream вернул false)" << endl;
    }

    // Демонстрация 2: Сохранение и восстановление состояния потока
    cout << "\n2. Демонстрация сохранения и изменения состояния потока:" << endl;

    // Создаем объекты потоков без открытия файлов (конструктор по умолчанию)
    ifstream input_file;
    ofstream output_file;

    // Открываем входной файл в бинарном режиме (раздел 5.2)
    input_file.open(input_filename.c_str(), ios::in | ios::binary);

    // Проверка состояния потока с использованием оператора void* (раздел 4.1)
    if (!input_file) {
        cerr << "Ошибка: не удалось открыть входной файл '"
            << input_filename << "'" << endl;

        // Проверка конкретных флагов ошибок
        if (input_file.fail()) {
            cerr << "   Установлен флаг failbit" << endl;
        }
        if (input_file.bad()) {
            cerr << "   Установлен флаг badbit" << endl;
        }

        return 1;
    }

    // Проверка состояния после успешного открытия
    cout << "   После открытия файла:" << endl;
    cout << "   input_file.good() = " << input_file.good() << endl;

    // Демонстрация 3: Использование метода rdstate() (раздел 4.2, Таблица 11)
    cout << "\n3. Использование rdstate() для получения полного состояния:" << endl;
    ios::iostate current_state = input_file.rdstate();
    cout << "   Текущее состояние входного потока (rdstate): " << current_state << endl;

    // Проверка отдельных флагов через bitwise AND (раздел 4.2)
    if (current_state & ios::eofbit) {
        cout << "   Установлен eofbit" << endl;
    }
    if (current_state & ios::failbit) {
        cout << "   Установлен failbit" << endl;
    }
    if (current_state & ios::badbit) {
        cout << "   Установлен badbit" << endl;
    }
    if (current_state == ios::goodbit) {
        cout << "   Все флаги сброшены (goodbit)" << endl;
    }

    // Открываем выходной файл в бинарном режиме
    output_file.open(output_filename.c_str(), ios::out | ios::binary | ios::trunc);

    if (!output_file) {
        cerr << "Ошибка: не удалось открыть выходной файл '"
            << output_filename << "'" << endl;
        input_file.close();
        return 1;
    }

    // Демонстрация 4: Сохранение состояния перед операциями
    cout << "\n4. Сохранение состояния перед обработкой файла:" << endl;
    ios::iostate saved_input_state = input_file.rdstate();
    ios::iostate saved_output_state = output_file.rdstate();
    cout << "   Состояние входного потока сохранено: " << saved_input_state << endl;
    cout << "   Состояние выходного потока сохранено: " << saved_output_state << endl;

    // Читаем файл посимвольно и шифруем
    char ch;
    size_t key_index = 0;
    size_t key_length = key.length();
    long bytes_processed = 0;

    // Используем цикл с проверкой состояния потока (раздел 4.1)
    while (input_file && output_file) {
        // Используем метод get() для чтения символа (раздел 6.4)
        if (input_file.get(ch)) {
            // Применяем XOR с текущим символом ключа
            char encrypted_char = ch ^ key[key_index];

            // Используем метод put() для записи символа
            if (!output_file.put(encrypted_char)) {
                cerr << "Ошибка записи в выходной файл на позиции " << bytes_processed << endl;
                break;
            }

            // Переходим к следующему символу ключа (циклически)
            key_index = (key_index + 1) % key_length;
            bytes_processed++;

            // Периодически проверяем состояние потоков
            if (bytes_processed % 1000 == 0) {
                // Проверка с использованием operator!() (раздел 4.1, Таблица 9)
                if (!input_file) {
                    cerr << "Проблема с входным потоком после " << bytes_processed << " байт" << endl;
                    break;
                }
                if (!output_file) {
                    cerr << "Проблема с выходным потоком после " << bytes_processed << " байт" << endl;
                    break;
                }
            }
        }
        else {
            // Проверяем причину окончания чтения
            if (input_file.eof()) {
                // Нормальное завершение - достигнут конец файла
                cout << "\nДостигнут конец файла. Обработано " << bytes_processed << " байт." << endl;
                break;
            }
            else if (input_file.fail() || input_file.bad()) {
                // Демонстрация 5: Проверка конкретных флагов ошибок
                cout << "\n5. Анализ ошибки чтения:" << endl;
                if (input_file.fail() && !input_file.eof()) {
                    cout << "   Установлен failbit (но не eofbit)" << endl;
                    cout << "   Возможная причина: ошибка форматирования" << endl;
                }
                if (input_file.bad()) {
                    cout << "   Установлен badbit" << endl;
                    cout << "   Возможная причина: критическая ошибка ввода/вывода" << endl;
                }
                break;
            }
        }
    }

    // Демонстрация 6: Сравнение состояния до и после обработки
    cout << "\n6. Сравнение состояния потоков до и после обработки:" << endl;
    ios::iostate final_input_state = input_file.rdstate();
    ios::iostate final_output_state = output_file.rdstate();

    cout << "   Входной поток:" << endl;
    cout << "   - Исходное состояние: " << saved_input_state << endl;
    cout << "   - Конечное состояние: " << final_input_state << endl;

    cout << "   Выходной поток:" << endl;
    cout << "   - Исходное состояние: " << saved_output_state << endl;
    cout << "   - Конечное состояние: " << final_output_state << endl;

    // Проверяем, не установлены ли флаги ошибок (раздел 4.2)
    if (input_file.bad() || output_file.bad()) {
        cerr << "\nПроизошла критическая ошибка ввода/вывода!" << endl;

        // Демонстрация 7: Использование clear() для сброса ошибок
        cout << "\n7. Попытка сброса ошибок с помощью clear():" << endl;

        if (input_file.bad()) {
            cout << "   Сбрасываем флаги входного потока..." << endl;
            // Сброс всех флагов (раздел 4.2, Таблица 11)
            input_file.clear();
            cout << "   Новое состояние входного потока: " << input_file.rdstate() << endl;
        }

        if (output_file.bad()) {
            cout << "   Сбрасываем флаги выходного потока..." << endl;
            // Установка конкретного состояния (goodbit)
            output_file.clear(ios::goodbit);
            cout << "   Новое состояние выходного потока: " << output_file.rdstate() << endl;
        }
    }
    else if (input_file.fail() && !input_file.eof()) {
        cerr << "\nПроизошла ошибка форматирования!" << endl;

        // Демонстрация 8: Сброс конкретного флага
        cout << "\n8. Сброс конкретного флага с помощью clear():" << endl;
        cout << "   Исходное состояние входного потока: " << input_file.rdstate() << endl;

        // Сброс только failbit (раздел 4.2, Таблица 11)
        input_file.clear(input_file.rdstate() & ~ios::failbit);
        cout << "   Состояние после сброса failbit: " << input_file.rdstate() << endl;
    }
    else {
        // Демонстрация 9: Успешное завершение
        cout << "\n9. Обработка завершена успешно:" << endl;
        cout << "   Все флаги ошибок сброшены" << endl;
        cout << "   input_file.good() = " << input_file.good() << endl;
        cout << "   output_file.good() = " << output_file.good() << endl;
    }

    // Закрываем файлы
    input_file.close();
    output_file.close();

    // Проверка состояния после закрытия
    cout << "\n10. Состояние потоков после закрытия файлов:" << endl;
    cout << "   input_file.rdstate() = " << input_file.rdstate() << endl;
    cout << "   output_file.rdstate() = " << output_file.rdstate() << endl;

    // Используем манипулятор endl для сброса буфера (раздел 3.3.1)
    cout << "\n=== Результат выполнения программы ===" << endl;
    cout << "Файл успешно обработан. Обработано " << bytes_processed << " байт." << endl;
    cout << "Для проверки запустите программу еще раз с теми же параметрами." << endl;
    cout << "Ключ шифрования: '" << key << "' (длина: " << key_length << " символов)" << endl;

    return 0;
