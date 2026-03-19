#include <iostream>
#include <clocale>

// Функция для сортировки части массива методом пузырька
void sortInterval(int arr[], int start, int end) {
    for (int i = start; i < end; i++) {
        for (int j = start; j < end - (i - start); j++) {
            if (arr[j] > arr[j + 1]) {
                // Обмен элементов
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
	setlocale(LC_ALL, "");
	
    int mas[] = { 2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9 };
    int n = sizeof(mas) / sizeof(mas[0]);

    std::cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << mas[i] << " ";
    }
    std::cout << std::endl;

    // Ввод интервала от пользователя
    int start_index, end_index;
    std::cout << "Введите начальный индекс интервала (от 0 до " << n - 1 << "): ";
    std::cin >> start_index;
    std::cout << "Введите конечный индекс интервала (от " << start_index << " до " << n - 1 << "): ";
    std::cin >> end_index;

    // Проверка корректности введенных индексов
    if (start_index < 0 || end_index >= n || start_index > end_index) {
        std::cout << "Ошибка: некорректный интервал индексов!" << std::endl;
        return 1;
    }

    // Сортировка на указанном интервале
    sortInterval(mas, start_index, end_index);

    std::cout << "Массив после сортировки на интервале [" << start_index << ", " << end_index << "]: ";
    for (int i = 0; i < n; i++) {
        std::cout << mas[i] << " ";
    }
    std::cout << std::endl;

    // Демонстрация с фиксированными интервалами
    int test_mas[] = { 2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9 };

    std::cout << "\nДемонстрация с интервалом [3, 8]:" << std::endl;
    std::cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << test_mas[i] << " ";
    }
    std::cout << std::endl;

    sortInterval(test_mas, 3, 8);

    std::cout << "После сортировки: ";
    for (int i = 0; i < n; i++) {
        std::cout << test_mas[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
