#include <cstring>
#include <ostream>

#include "LinkedList.h"

// Структура, описывающая автобус
struct Bus {
private:
    int number;        // номер автобуса (уникальный идентификатор)
    char name[100]{};  // ФИО водителя
    int route;         // номер маршрута

public:
    // Конструктор: инициализирует все поля автобуса
    Bus(int number, const char* name, int route) {
        this->number = number;
        this->route = route;
        this->name[0] = '\0';
        strcpy_s(this->name, name);
    }

    // Сравнение по номеру автобуса (уникальный ключ)
    friend bool operator==(const Bus& lhs, const Bus& rhs) {
        return lhs.number == rhs.number;
    }

    friend bool operator!=(const Bus& lhs, const Bus& rhs) {
        return !(lhs.number == rhs.number);
    }

    // Вывод информации об автобусе
    friend std::ostream& operator<<(std::ostream& out, const Bus& bus) {
        out << "[" << bus.number << ' ' << bus.name << ' ' << bus.route << "]";
        return out;
    }
};

// Класс, управляющий автобусным парком
class Park {
    LinkedList<Bus> onpark;   // автобусы в парке
    LinkedList<Bus> onroute;  // автобусы на маршруте
    Bus bus_ = Bus(0, "", 0); // временный объект для поиска

public:
    Park() = default;
    ~Park() = default;

    // Выезд из парка на маршрут
    void leavePark(int number) {
        // Ищем автобус по номеру в парке
        Bus* bus = onpark.find(Bus(number, "", 0));
        if (bus != nullptr) {
            onpark.remove(*bus);   // удаляем из парка
            onroute.add(*bus);     // добавляем на маршрут
        }
    }

    // Заезд в парк с маршрута
    void enterPark(int number) {
        // Ищем автобус по номеру на маршруте
        Bus* bus = onroute.find(Bus(number, "", 0));
        if (bus != nullptr) {
            onroute.remove(*bus);  // удаляем с маршрута
            onpark.add(*bus);      // добавляем в парк
        }
    }

    // Добавление нового автобуса в парк
    void add(Bus const& bus) {
        onpark.add(bus);
    }

    // Вывод списка автобусов в парке
    void printPark() {
        std::cout << "В парке :" << onpark << std::endl;
    }

    // Вывод списка автобусов на маршруте
    void printRoute() {
        std::cout << "На маршруте :" << onroute << std::endl;
    }
};

int main() {
    Park park;

    // Добавляем автобусы в парк
    park.add(Bus(1, "Филонов Г.В.", 10));
    park.add(Bus(2, "Миронов И.И.", 2));
    park.add(Bus(3, "Витальева Г.Г.", 4));
    park.add(Bus(4, "Артемов Д.А.", 25));
    park.add(Bus(5, "Крисп А.А.", 33));
    park.add(Bus(6, "Смирнова Е.И.", 11));
    park.add(Bus(7, "Кочетков А.Г.", 122));

    park.printPark();  // все автобусы в парке

    std::cout << "=======================" << std::endl;
    // Отправляем несколько автобусов на маршрут
    park.leavePark(1);
    park.leavePark(2);
    park.leavePark(7);

    park.printPark();   // оставшиеся в парке
    park.printRoute();  // уехавшие на маршрут

    std::cout << "=======================" << std::endl;
    // Возвращаем два автобуса с маршрута в парк
    park.enterPark(1);
    park.enterPark(2);

    park.printPark();
    park.printRoute();

    std::cout << "=======================" << std::endl;
    // Отправляем ещё два автобуса на маршрут
    park.leavePark(3);
    park.leavePark(4);

    park.printPark();
    park.printRoute();
}