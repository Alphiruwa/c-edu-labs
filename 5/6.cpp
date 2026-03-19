#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <clocale>

// Функция для шифрования/дешифрования
void xor_crypt(const std::string& input_file,
    const std::string& output_file,
    const std::string& key) {

    // Открываем входной файл в бинарном режиме
    std::ifstream in_file(input_file, std::ios::binary);
    if (!in_file) {
        std::cerr << "Ошибка: не удалось открыть входной файл '"
            << input_file << "'" << std::endl;
        return;
    }

    // Открываем выходной файл в бинарном режиме
    std::ofstream out_file(output_file, std::ios::binary);
    if (!out_file) {
        std::cerr << "Ошибка: не удалось открыть выходной файл '"
            << output_file << "'" << std::endl;
        in_file.close();
        return;
    }

    // Если ключ пустой, просто копируем файл
    if (key.empty()) {
        out_file << in_file.rdbuf();
        std::cout << "Ключ пустой - файл скопирован без изменений"
            << std::endl;
        in_file.close();
        out_file.close();
        return;
    }

    // Читаем файл посимвольно и применяем XOR
    char ch;
    size_t key_index = 0;
    size_t key_length = key.length();

    while (in_file.get(ch)) {
        // Применяем операцию XOR с текущим символом ключа
        char encrypted_char = ch ^ key[key_index];
        out_file.put(encrypted_char);

        // Переходим к следующему символу ключа (циклически)
        key_index = (key_index + 1) % key_length;
    }

    // Закрываем файлы
    in_file.close();
    out_file.close();

    std::cout << "Файл '" << input_file
        << "' успешно обработан. Результат записан в '"
        << output_file << "'" << std::endl;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    // Проверяем количество аргументов
    if (argc != 4) {
        std::cout << "Использование: " << argv[0]
            << " <входной_файл> <выходной_файл> <ключ>" << std::endl;
        std::cout << "Пример: " << argv[0]
            << " input.txt encrypted.txt secretkey" << std::endl;
        std::cout << "\nДля проверки правильности работы:" << std::endl;
        std::cout << "1. " << argv[0]
            << " original.txt encrypted.txt key" << std::endl;
        std::cout << "2. " << argv[0]
            << " encrypted.txt decrypted.txt key" << std::endl;
        std::cout << "3. Сравните original.txt и decrypted.txt" << std::endl;
        return 1;
    }

    // Получаем аргументы командной строки
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::string key = argv[3];

    // Выполняем шифрование/дешифрование
    xor_crypt(input_file, output_file, key);

    return 0;
}
