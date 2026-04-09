#include <iostream>
#include <fstream>
using namespace std;

const char fname[] = "NewFile.txt";

int main(void)
{
    // Создаем новый файл, если только он уже не существует
    ofstream ofs(fname, ios::out | ios::_Nocreate);

    if (!ofs)
    {
        // Проверка состояния потока
        cout << "Ошибочная ситуация! Файл "
            << fname
            << " уже существует. "
            << endl;
        return 0;
    }
    else
    {
        ofs << "Эта строка записывается "
            << "в новый файл";
        ofs.close(); // Закрываем файл

        fstream fs; // Определяем новый объект
        // Открываем файл и устанавливаем на EOF
        fs.open(fname, ios::out | ios::app);
        fs << "Сейчас к ней сделано добавление";
        fs.close(); // Закрываем файл

        // Открываем файл как входной
        ifstream ifs(fname);
        if (ifs) {
            cout << "В старом файле содержится"
                << "..." << endl;
            char Line[80];
            ifs.getline(Line, sizeof(Line));
            cout << Line;
        }
        else
        {
            cout << "Ошибочная ситуация "
                << "при повторном открытии "
                << fname
                << endl;
        }
    }
    return 0;
}
