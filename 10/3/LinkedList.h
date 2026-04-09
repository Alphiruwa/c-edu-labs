#include <iostream>

template<class T>
class LinkedList {
    struct Node {
        T d;          // данные узла
        Node* next;   // указатель на следующий узел
    };

protected:
    Node* pbeg;  // указатель на начало списка
    Node* pend;  // указатель на конец списка

public:
    // Конструктор: создаёт первый узел
    LinkedList(T data) {
        Node* pv = new Node;
        pv->d = data;
        pv->next = nullptr;
        pbeg = pv;
        pend = pv;
    }

    // Деструктор: удаляет все узлы, начиная с первого
    ~LinkedList() {
        while (pbeg) {
            Node* temp = pbeg;
            pbeg = pbeg->next;
            delete temp;
        }
        pend = nullptr;
    }

    // Добавление в конец списка
    void add(T data) {
        Node* pv = new Node;
        pv->d = data;
        pv->next = nullptr;
        pend->next = pv;  // последний узел ссылается на новый
        pend = pv;        // обновляем указатель на конец
    };

    // Поиск узла с заданными данными
    Node* find(T data) {
        Node* pv = pbeg;
        while (pv) {
            if (pv->d == data) break;
            pv = pv->next;
        }
        return pv;  // вернёт nullptr, если не найден
    }

    // Удаление первого узла с заданными данными
    int remove(T data) {
        Node* prev = nullptr;
        Node* target = pbeg;
        
        // Поиск узла для удаления
        while (target) {
            if (target->d == data) break;
            prev = target;
            target = target->next;
        }

        if (target) {
            // Случай единственного узла
            if (target == pend && target == pbeg) {
                pbeg = nullptr;
                pend = nullptr;
            }
            else {
                // Удаление из начала
                if (target == pbeg) {
                    pbeg = pbeg->next;
                }
                // Удаление из конца
                else if (target == pend) {
                    pend = prev;
                    pend->next = nullptr;
                }
                // Удаление из середины (связь через prev->next)
                else {
                    prev->next = target->next;
                }
            }
            delete target;
            return 1;  // успешно удалён
        }
        return 0;  // узел не найден
    }

    // Вставка узла на позицию pos (0 - в начало)
    Node* insert(int pos, T data) {
        Node* pv = new Node;
        pv->d = data;
        pv->next = nullptr;
        
        // Вставка в начало или в пустой список
        if (!pos || !pbeg) {
            pv->next = pbeg;
            pbeg = pv;
        }
        else {
            // Ищем узел, перед которым будем вставлять
            Node* prev = pbeg;
            for (int i = 0; i < pos - 1 && prev->next; i++) {
                prev = prev->next;
            }
            pv->next = prev->next;
            prev->next = pv;
        }
        return pv;
    }

    // Добавление с сохранением сортировки (по возрастанию)
    void add_sort(T data) {
        Node* pv = new Node;
        pv->d = data;
        pv->next = nullptr;
        
        if (pbeg == nullptr) {
            pbeg = pv;
            pend = pv;
            return;
        }
        
        Node* prev = nullptr;
        Node* pt = pbeg;
        
        // Ищем место для вставки (первый элемент > data)
        while (pt) {
            if (pt->d > data) {
                pv->next = pt;
                if (prev == nullptr) {
                    pbeg = pv;      // вставка в начало
                } else {
                    prev->next = pv; // вставка в середину
                }
                return;
            }
            prev = pt;
            pt = pt->next;
        }
        
        // Вставка в конец (data больше всех)
        pv->next = nullptr;
        pend->next = pv;
        pend = pv;
    }

    // Перегрузка оператора вывода: печать всех элементов через пробел
    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
        Node* pv = list.pbeg;
        while (pv) {
            out << pv->d << ' ';
            pv = pv->next;
        }
        return out;
    }
};