#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <clocale>

// Функция для извлечения номера страницы из строки
int extract_page_number(const std::string& line) {
    // Ищем цифры в строке
    std::string number_str;
    bool found_digit = false;

    for (char c : line) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            number_str += c;
            found_digit = true;
        }
        // Если мы уже нашли цифры и встретили не-цифру - продолжаем искать
        // (на случай если в строке несколько групп цифр, берем первую)
    }

    if (!found_digit || number_str.empty()) {
        return -1; // Номер страницы не найден
    }

    try {
        return std::stoi(number_str);
    }
    catch (...) {
        return -1;
    }
}

// Функция для удаления дефисов и лишних пробелов из номера страницы
std::string format_page_number(const std::string& line) {
    std::string result;
    bool found_digit = false;

    for (char c : line) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            result += c;
            found_digit = true;
        }
    }

    return found_digit ? result : "";
}

void process_file(const std::string& input_filename, const std::string& output_filename) {
    std::ifstream input_file(input_filename);
    std::ofstream output_file(output_filename);

    if (!input_file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть входной файл " << input_filename << std::endl;
        return;
    }

    if (!output_file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть выходной файл " << output_filename << std::endl;
        input_file.close();
        return;
    }

    std::string line;
    std::vector<std::string> page_lines;
    bool first_page = true;
    int current_page_number = -1;
    std::string first_line_of_page;

    while (std::getline(input_file, line)) {
        // Если встречаем символ перевода страницы
        if (!line.empty() && line.find('\f') != std::string::npos) {
            // Обрабатываем предыдущую страницу, если она есть
            if (!page_lines.empty()) {
                // Удаляем последнюю строку (там будет символ \f)
                if (!page_lines.empty() && !page_lines.back().empty() &&
                    page_lines.back().find('\f') != std::string::npos) {
                    page_lines.pop_back();
                }

                // Добавляем номер страницы в конец
                if (current_page_number != -1) {
                    page_lines.push_back(std::to_string(current_page_number));
                }

                // Записываем страницу в выходной файл
                for (size_t i = 0; i < page_lines.size(); ++i) {
                    if (i > 0 || !first_page) {
                        output_file << std::endl;
                    }
                    output_file << page_lines[i];
                }

                first_page = false;
            }

            // Начинаем новую страницу
            page_lines.clear();

            // Считываем первую строку новой страницы (предположительно с номером)
            if (std::getline(input_file, first_line_of_page)) {
                // Извлекаем номер страницы из первой строки
                std::string formatted_number = format_page_number(first_line_of_page);
                if (!formatted_number.empty()) {
                    current_page_number = std::stoi(formatted_number);
                }
                else {
                    current_page_number = -1;
                }
                // Не добавляем эту строку в содержимое страницы
            }
        }
        else {
            // Добавляем строку в текущую страницу
            page_lines.push_back(line);
        }
    }

    // Обрабатываем последнюю страницу
    if (!page_lines.empty()) {
        // Добавляем номер страницы в конец
        if (current_page_number != -1) {
            page_lines.push_back(std::to_string(current_page_number));
        }

        // Записываем последнюю страницу
        for (size_t i = 0; i < page_lines.size(); ++i) {
            if (i > 0 || !first_page) {
                output_file << std::endl;
            }
            output_file << page_lines[i];
        }
    }

    input_file.close();
    output_file.close();

    std::cout << "Файл успешно обработан. Результат записан в " << output_filename << std::endl;
}

int main() {
    setlocale(LC_ALL, "");

    std::string input_filename, output_filename;

    std::cout << "Введите имя входного файла: ";
    std::cin >> input_filename;

    std::cout << "Введите имя выходного файла: ";
    std::cin >> output_filename;

    process_file(input_filename, output_filename);

    return 0;
}
