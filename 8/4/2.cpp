#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Task {
public:
    string description;
    bool completed;

    Task(string desc = "") : description(desc), completed(false) {}

    // Перегрузка операторов ввода/вывода
    friend istream& operator>>(istream& is, Task& task) {
        cout << "Описание задачи: ";
        getline(is, task.description);
        if (task.description.empty()) {
            is.setstate(ios::failbit);
            cerr << "Ошибка: описание не может быть пустым!\n";
        }
        return is;
    }

    friend ostream& operator<<(ostream& os, const Task& task) {
        os << (task.completed ? "[✓] " : "[ ] ") << task.description;
        return os;
    }
};

// Функция демонстрации состояния потока
void showState(const string& msg, ios& stream) {
    cout << "\n" << msg << ":\n";
    cout << "  good=" << stream.good()
        << " eof=" << stream.eof()
        << " fail=" << stream.fail()
        << " bad=" << stream.bad()
        << " rdstate=" << stream.rdstate() << endl;
}

int main() {
    cout << "=== МЕНЕДЖЕР ЗАДАЧ С ДЕМОНСТРАЦИЕЙ ПОТОКОВ ===\n";

    vector<Task> tasks;
    string filename = "tasks.txt";

    // 1. Загрузка задач из файла
    cout << "\n1. ЗАГРУЗКА ИЗ ФАЙЛА:\n";
    ifstream inFile(filename);

    if (!inFile) {
        cout << "Файл не найден. Создан новый список.\n";
        showState("Открытие несуществующего файла", inFile);
    }
    else {
        string line;
        while (getline(inFile, line)) {
            if (!line.empty()) {
                Task task(line.substr(4)); // Пропускаем "[ ] "
                task.completed = (line.substr(0, 4) == "[✓] ");
                tasks.push_back(task);
            }
        }

        if (inFile.eof()) {
            cout << "Файл прочитан до конца.\n";
        }

        if (inFile.fail() && !inFile.eof()) {
            cerr << "Ошибка чтения файла!\n";
        }

        showState("После чтения файла", inFile);
        inFile.close();
    }

    // 2. Ввод новой задачи с проверкой
    cout << "\n2. ДОБАВЛЕНИЕ НОВОЙ ЗАДАЧИ:\n";

    // Сохраняем состояние cin
    ios::iostate savedState = cin.rdstate();
    cin.clear(); // Сбрасываем возможные флаги

    Task newTask;
    cout << "Введите новую задачу:\n";

    if (!(cin >> newTask)) {
        cerr << "Ошибка ввода задачи!\n";
        showState("После ошибки ввода", cin);

        // Восстанавливаем состояние
        cin.clear(savedState);
        cin.ignore(1000, '\n');
    }
    else {
        tasks.push_back(newTask);
        cout << "Задача добавлена!\n";
        showState("После успешного ввода", cin);
    }

    // 3. Показать все задачи
    cout << "\n3. СПИСОК ЗАДАЧ (" << tasks.size() << "):\n";
    if (tasks.empty()) {
        cout << "Задач нет.\n";
    }
    else {
        for (size_t i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". " << tasks[i] << endl;
        }
    }

    // 4. Отметить задачу выполненной
    if (!tasks.empty()) {
        cout << "\n4. ОТМЕТИТЬ ЗАДАЧУ ВЫПОЛНЕННОЙ:\n";
        cout << "Введите номер задачи (1-" << tasks.size() << "): ";

        int taskNum;
        if (!(cin >> taskNum)) {
            cerr << "Ошибка ввода номера!\n";
            showState("После ошибки ввода номера", cin);

            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (taskNum > 0 && taskNum <= tasks.size()) {
            tasks[taskNum - 1].completed = true;
            cout << "Задача отмечена как выполненная!\n";
        }
        else {
            cerr << "Неверный номер задачи!\n";
        }
    }

    // 5. Сохранение в файл
    cout << "\n5. СОХРАНЕНИЕ В ФАЙЛ:\n";
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!\n";
        showState("Открытие для записи", outFile);
    }
    else {
        for (const auto& task : tasks) {
            outFile << task << endl;

            if (outFile.fail()) {
                cerr << "Ошибка записи задачи!\n";
                outFile.clear(outFile.rdstate() & ~ios::failbit);
            }
        }

        outFile << flush; // Принудительный сброс буфера

        if (outFile.bad()) {
            cerr << "Критическая ошибка записи!\n";
        }

        showState("После записи в файл", outFile);
        outFile.close();
        cout << "Задачи сохранены в " << filename << endl;
    }

    // 6. Демонстрация сброса состояния
    cout << "\n6. ДЕМОНСТРАЦИЯ СБРОСА СОСТОЯНИЯ:\n";

    // Создаем поток с ошибкой
    stringstream errorStream;
    errorStream.setstate(ios::failbit | ios::badbit);

    cout << "До сброса:\n";
    showState("Поток с ошибками", errorStream);

    // Сбрасываем только failbit
    errorStream.clear(errorStream.rdstate() & ~ios::failbit);

    cout << "После сброса failbit:\n";
    showState("Частичный сброс", errorStream);

    // Полный сброс
    errorStream.clear();

    cout << "После полного сброса:\n";
    showState("Полный сброс", errorStream);

    return 0;
}
