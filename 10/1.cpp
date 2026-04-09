#include <iostream>

struct Node {
    int d;
    Node* next;
};

// Прототипы функций
Node* first(int d);
void add(Node** pend, int d);
Node* find(Node* pbeg, int d);
int remove(Node** pbeg, Node** pend, int key);
Node* insert(Node* pbeg, Node** pend, int key, int d);
void add_sort(Node** pbeg, Node** pend, int d);

int main() {
    // Создаём список 1 2 3 4 5
    Node* pbeg = first(1);
    Node* pend = pbeg;
    for (int i = 2; i < 6; i++) add(&pend, i);
    
    // Вставляем 200 после первого вхождения 2
    insert(pbeg, &pend, 2, 200);
    
    // Удаляем 5, если не найден — выводим сообщение
    if (!remove(&pbeg, &pend, 5)) std::cout << "не найден";
    
    // Вывод списка
    Node* pv = pbeg;
    while (pv) {
        std::cout << pv->d << ' ';
        pv = pv->next;
    }
    return 0;
}

// Создание первого узла
Node* first(int d) {
    Node* pv = new Node;
    pv->d = d;
    pv->next = 0;
    return pv;
}

// Добавление в конец списка
void add(Node** pend, int d) {
    Node* pv = new Node;
    pv->d = d;
    pv->next = 0;
    (*pend)->next = pv;  // текущий последний указывает на новый
    *pend = pv;          // обновляем указатель на последний
}

// Поиск узла по значению
Node* find(Node* const pbeg, int key) {
    Node* pv = pbeg;
    while (pv) {
        if (pv->d == key) break;
        pv = pv->next;
    }
    return pv;
}

// Удаление узла по ключу
int remove(Node** pbeg, Node** pend, int key) {
    Node* prev = 0;
    Node* target = *pbeg;
    
    // Поиск удаляемого узла
    while (target) {
        if (target->d == key) break;
        prev = target;
        target = target->next;
    }

    if (target) {
        // Случай 1: единственный элемент
        if (target == *pend && target == *pbeg) {
            *pbeg = 0;
            *pend = 0;
        }
        // Случай 2: удаляем первый
        else if (target == *pbeg) {
            *pbeg = (*pbeg)->next;
        }
        // Случай 3: удаляем последний
        else if (target == *pend) {
            *pend = prev;
            (*pend)->next = 0;
        }
        // Случай 4: удаляем из середины
        else {
            if (prev) {
                prev->next = target->next;
            }
        }
        delete target;
        return 1;
    }
    return 0;
}

// Вставка после первого вхождения key
Node* insert(Node* const pbeg, Node** pend, int key, int d) {
    Node* pkey = find(pbeg, key);
    if (pkey) {
        Node* pv = new Node;
        pv->d = d;
        pv->next = pkey->next;  // новый узел ссылается на следующий за key
        pkey->next = pv;         // key ссылается на новый узел
        if (pkey == *pend)       // если вставляем после последнего
            *pend = pv;
        return pv;
    }
    return 0;
}

// Добавление с сохранением сортировки по возрастанию
void add_sort(Node** pbeg, Node** pend, int d) {
    Node* pv = new Node;
    pv->d = d;
    pv->next = 0;

    if (*pbeg == 0) {
        *pbeg = pv;
        *pend = pv;
        return;
    }

    Node* prev = 0;
    Node* pt = *pbeg;
    while (pt) {
        if (d < pt->d) {           // нашли место для вставки
            pv->next = pt;
            if (prev == 0)         // вставка в начало
                *pbeg = pv;
            else                   // вставка в середину
                prev->next = pv;
            return;
        }
        prev = pt;
        pt = pt->next;
    }
    // вставка в конец
    (*pend)->next = pv;
    *pend = pv;
}