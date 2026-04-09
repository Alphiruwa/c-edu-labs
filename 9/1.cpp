#include <iostream>
#include <ostream>

template<class T>
void Sort(T array[], size_t size) {
    int i, j;
    T tmp;
    // Для каждого элемента с начала
    for (i = 0; i < size - 1; i++)
        // Сравниваем с элементами с конца до i
        for (j = size - 1; i < j; j--)
            // Если левый больше правого — меняем их
            if (array[i] > array[j]) {
                tmp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = tmp;
            }
}

int main() {
    int i;
    int mas[] = { 10, 20, 30, 11, 25, 32, 0 };
    
    // Сортируем массив
    Sort(mas, sizeof(mas) / sizeof(mas[0]));
    
    // Выводим результат
    for (i = 0; i < sizeof(mas) / sizeof(mas[0]); i++)
        std::cout << "mas[" << i << "] = " << mas[i] << std::endl;
    
    return 0;
}