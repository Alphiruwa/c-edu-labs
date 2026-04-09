#include <iostream>
#include <fstream>
#include <stdlib.h>

int main(void)
{
    char name[12];
    std::fstream fin; // Неоткрытый объект-поток
    std::cout << "Введите имя файла: ";
    std::cin >> name;

    // Открыли входной поток
    fin.open(name, std::ios::in);

    if (fin) // Проверяем состояние потока
    {
        std::cout << "Файл открыт " << name << std::endl;
        fin.close(); // Закрываем файл
    }
    else
    {
        std::cout << "Не открыт выходной файл " << name << std::endl;
    }

    return 0;
}
