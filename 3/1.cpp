#include <iostream>
#include <vector>
#include <clocale>

int main() {
    setlocale(LC_ALL, "");

    // Исходный массив
    std::vector<int> mas = { 2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9 };

    // Вывод исходного массива
    std::cout << "Исходный массив: ";
    for (int val : mas) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    // Сортировка выбором минимума (Selection Sort)
    // На каждом шаге находим минимальный элемент в неотсортированной части
    // и меняем его с первым элементом неотсортированной части
    for (size_t i = 0; i < mas.size() - 1; ++i) {
        size_t min_index = i;  // Индекс минимального элемента

        // Поиск минимального элемента в оставшейся части массива
        for (size_t j = i + 1; j < mas.size(); ++j) {
            if (mas[j] < mas[min_index]) {
                min_index = j;
            }
        }

        // Обмен найденного минимального элемента с текущим
        std::swap(mas[i], mas[min_index]);
    }

    // Вывод отсортированного массива
    std::cout << "Отсортированный массив: ";
    for (int val : mas) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}