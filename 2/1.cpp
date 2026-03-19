#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#define N 5

// 1. Минимум матрицы
float matrixMin(float matrix[N][N]) {
    float minVal = matrix[0][0]; // Инициализируем минимальное значение первым элементом матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j]; // Обновляем минимум, если найден меньший элемент
            }
        }
    }
    return minVal; // Возвращаем найденное минимальное значение
}

// 2. Максимум матрицы
float matrixMax(float matrix[N][N]) {
    float maxVal = matrix[0][0]; // Инициализируем максимальное значение первым элементом матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j]; // Обновляем максимум, если найден больший элемент
            }
        }
    }
    return maxVal; // Возвращаем найденное максимальное значение
}

// 3. Максимум нижнетреугольной части матрицы
float lowerTriangleMax(float matrix[N][N]) {
    float maxVal = matrix[0][0]; // Инициализируем максимум первым элементом
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) { // j <= i - условие для нижнетреугольной части
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j]; // Обновляем максимум для нижнего треугольника
            }
        }
    }
    return maxVal; // Возвращаем максимальное значение нижнего треугольника
}

// 4. Максимум верхнетреугольной части матрицы
float upperTriangleMax(float matrix[N][N]) {
    float maxVal = matrix[0][0]; // Инициализируем максимум первым элементом
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) { // j >= i - условие для верхнетреугольной части
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j]; // Обновляем максимум для верхнего треугольника
            }
        }
    }
    return maxVal; // Возвращаем максимальное значение верхнего треугольника
}

// 5. Минимум нижнетреугольной части матрицы
float lowerTriangleMin(float matrix[N][N]) {
    float minVal = matrix[0][0]; // Инициализируем минимум первым элементом
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) { // j <= i - условие для нижнетреугольной части
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j]; // Обновляем минимум для нижнего треугольника
            }
        }
    }
    return minVal; // Возвращаем минимальное значение нижнего треугольника
}

// 6. Минимум верхнетреугольной части матрицы
float upperTriangleMin(float matrix[N][N]) {
    float minVal = matrix[0][0]; // Инициализируем минимум первым элементом
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) { // j >= i - условие для верхнетреугольной части
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j]; // Обновляем минимум для верхнего треугольника
            }
        }
    }
    return minVal; // Возвращаем минимальное значение верхнего треугольника
}

// 7. Минимум главной диагонали матрицы
float mainDiagonalMin(float matrix[N][N]) {
    float minVal = matrix[0][0]; // Инициализируем минимум первым элементом диагонали
    for (int i = 0; i < N; i++) {
        // Элементы главной диагонали имеют индексы [i][i]
        if (matrix[i][i] < minVal) {
            minVal = matrix[i][i]; // Обновляем минимум главной диагонали
        }
    }
    return minVal; // Возвращаем минимальное значение главной диагонали
}

// 8. Максимум главной диагонали матрицы
float mainDiagonalMax(float matrix[N][N]) {
    float maxVal = matrix[0][0]; // Инициализируем максимум первым элементом диагонали
    for (int i = 0; i < N; i++) {
        // Элементы главной диагонали имеют индексы [i][i]
        if (matrix[i][i] > maxVal) {
            maxVal = matrix[i][i]; // Обновляем максимум главной диагонали
        }
    }
    return maxVal; // Возвращаем максимальное значение главной диагонали
}

// 9. Минимум второстепенной диагонали матрицы
float secondaryDiagonalMin(float matrix[N][N]) {
    // Инициализируем минимум первым элементом второстепенной диагонали (правый верхний угол)
    float minVal = matrix[0][N - 1];
    for (int i = 0; i < N; i++) {
        // Элементы второстепенной диагонали: [i][N-1-i]
        if (matrix[i][N - 1 - i] < minVal) {
            minVal = matrix[i][N - 1 - i]; // Обновляем минимум второстепенной диагонали
        }
    }
    return minVal; // Возвращаем минимальное значение второстепенной диагонали
}

// 10. Максимум второстепенной диагонали матрицы
float secondaryDiagonalMax(float matrix[N][N]) {
    // Инициализируем максимум первым элементом второстепенной диагонали (правый верхний угол)
    float maxVal = matrix[0][N - 1];
    for (int i = 0; i < N; i++) {
        // Элементы второстепенной диагонали: [i][N-1-i]
        if (matrix[i][N - 1 - i] > maxVal) {
            maxVal = matrix[i][N - 1 - i]; // Обновляем максимум второстепенной диагонали
        }
    }
    return maxVal; // Возвращаем максимальное значение второстепенной диагонали
}

// 11. Среднеарифметическое значение элементов матрицы
float matrixAverage(float matrix[N][N]) {
    float sum = 0; // Переменная для накопления суммы всех элементов
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += matrix[i][j]; // Суммируем все элементы матрицы
        }
    }
    // Возвращаем среднее арифметическое: сумма делится на общее количество элементов
    return sum / (N * N);
}

// 12. Среднеарифметическое значение элементов нижнетреугольной части матрицы
float lowerTriangleAverage(float matrix[N][N]) {
    float sum = 0; // Сумма элементов нижнего треугольника
    int count = 0; // Счетчик элементов нижнего треугольника
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) { // j <= i - условие для нижнетреугольной части
            sum += matrix[i][j]; // Суммируем элемент
            count++; // Увеличиваем счетчик
        }
    }
    return sum / count; // Возвращаем среднее арифметическое
}
// 13. Среднеарифметическое значение элементов верхнетреугольной части матрицы
float upperTriangleAverage(float matrix[N][N]) {
    float sum = 0; // Сумма элементов верхнего треугольника
    int count = 0; // Счетчик элементов верхнего треугольника
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) { // j >= i - условие для верхнетреугольной части
            sum += matrix[i][j]; // Суммируем элемент
            count++; // Увеличиваем счетчик
        }
    }
    return sum / count; // Возвращаем среднее арифметическое
}

// 14. Суммы строк матрицы
void rowSums(float matrix[N][N], float sums[N]) {
    for (int i = 0; i < N; i++) {
        sums[i] = 0; // Инициализируем сумму i-й строки нулем
        for (int j = 0; j < N; j++) {
            sums[i] += matrix[i][j]; // Суммируем элементы строки i
        }
    }
    // Результат сохраняется в переданном массиве sums
}

// 15. Суммы столбцов матрицы
void columnSums(float matrix[N][N], float sums[N]) {
    for (int j = 0; j < N; j++) {
        sums[j] = 0; // Инициализируем сумму j-го столбца нулем
        for (int i = 0; i < N; i++) {
            sums[j] += matrix[i][j]; // Суммируем элементы столбца j
        }
    }
    // Результат сохраняется в переданном массиве sums
}

// 16. Минимальные значения строк
void rowMins(float matrix[N][N], float mins[N]) {
    for (int i = 0; i < N; i++) {
        mins[i] = matrix[i][0]; // Инициализируем минимум первым элементом строки
        for (int j = 1; j < N; j++) {
            if (matrix[i][j] < mins[i]) {
                mins[i] = matrix[i][j]; // Обновляем минимум для текущей строки
            }
        }
    }
    // Результат сохраняется в переданном массиве mins
}

// 17. Минимальные значения столбцов
void columnMins(float matrix[N][N], float mins[N]) {
    for (int j = 0; j < N; j++) {
        mins[j] = matrix[0][j]; // Инициализируем минимум первым элементом столбца
        for (int i = 1; i < N; i++) {
            if (matrix[i][j] < mins[j]) {
                mins[j] = matrix[i][j]; // Обновляем минимум для текущего столбца
            }
        }
    }
    // Результат сохраняется в переданном массиве mins
}

// 18. Максимальные значения строк
void rowMaxs(float matrix[N][N], float maxs[N]) {
    for (int i = 0; i < N; i++) {
        maxs[i] = matrix[i][0]; // Инициализируем максимум первым элементом строки
        for (int j = 1; j < N; j++) {
            if (matrix[i][j] > maxs[i]) {
                maxs[i] = matrix[i][j]; // Обновляем максимум для текущей строки
            }
        }
    }
    // Результат сохраняется в переданном массиве maxs
}

// 19. Максимальные значения столбцов
void columnMaxs(float matrix[N][N], float maxs[N]) {
    for (int j = 0; j < N; j++) {
        maxs[j] = matrix[0][j]; // Инициализируем максимум первым элементом столбца
        for (int i = 1; i < N; i++) {
            if (matrix[i][j] > maxs[j]) {
                maxs[j] = matrix[i][j]; // Обновляем максимум для текущего столбца
            }
        }
    }
    // Результат сохраняется в переданном массиве maxs
}

// 20. Среднеарифметические значения строк
void rowAverages(float matrix[N][N], float averages[N]) {
    for (int i = 0; i < N; i++) {
        float sum = 0; // Сумма элементов текущей строки
        for (int j = 0; j < N; j++) {
            sum += matrix[i][j]; // Суммируем элементы строки i
        }
        averages[i] = sum / N; // Вычисляем среднее для строки i
    }
    // Результат сохраняется в переданном массиве averages
}

// 21. Среднеарифметические значения столбцов
void columnAverages(float matrix[N][N], float averages[N]) {
    for (int j = 0; j < N; j++) {
        float sum = 0; // Сумма элементов текущего столбца
        for (int i = 0; i < N; i++) {
            sum += matrix[i][j]; // Суммируем элементы столбца j
        }
        averages[j] = sum / N; // Вычисляем среднее для столбца j
    }
    // Результат сохраняется в переданном массиве averages
}

// 22. Суммы нижне- и верхнетреугольных частей матрицы
void triangleSums(float matrix[N][N], float& lowerSum, float& upperSum) {
    lowerSum = 0; // Инициализация суммы нижнего треугольника
    upperSum = 0; // Инициализация суммы верхнего треугольника
    for (int i = 0; i < N; i++) {
        // Суммируем элементы нижнего треугольника (j <= i)
        for (int j = 0; j <= i; j++) {
            lowerSum += matrix[i][j];
        }
        // Суммируем элементы верхнего треугольника (j >= i)
        for (int j = i; j < N; j++) {
            upperSum += matrix[i][j];
        }
    }
    // Результаты возвращаются через ссылочные параметры
}

// 23. Элемент, наиболее близкий по значению к среднеарифметическому
float closestToAverage(float matrix[N][N]) {
    // Вычисляем среднее арифметическое всей матрицы
    float avg = matrixAverage(matrix);
    float closest = matrix[0][0]; // Инициализируем ближайший элемент
    float minDiff = abs(matrix[0][0] - avg); // Инициализируем минимальную разницу

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float diff = abs(matrix[i][j] - avg); // Вычисляем разницу с средним
            if (diff < minDiff) {
                minDiff = diff; // Обновляем минимальную разницу
                closest = matrix[i][j]; // Обновляем ближайший элемент
            }
        }
    }
    return closest; // Возвращаем элемент, наиболее близкий к среднему
}

void main()
{
    float m[N][N];
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) m[i][j] = rand() / 10.;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            std::cout << std::setw(8) << std::setprecision(5) << m[i][j];
    std::cout << std::endl;

    std::cout << "1. Matrix minimum: " << matrixMin(m) << std::endl;
    std::cout << "2. Matrix maximum: " << matrixMax(m) << std::endl;
    std::cout << "3. Lower triangle maximum: " << lowerTriangleMax(m) << std::endl;
    std::cout << "4. Upper triangle maximum: " << upperTriangleMax(m) << std::endl;
    std::cout << "5. Lower triangle minimum: " << lowerTriangleMin(m) << std::endl;
    std::cout << "6. Upper triangle minimum: " << upperTriangleMin(m) << std::endl;
    std::cout << "7. Main diagonal minimum: " << mainDiagonalMin(m) << std::endl;
    std::cout << "8. Main diagonal maximum: " << mainDiagonalMax(m) << std::endl;
    std::cout << "9. Secondary diagonal minimum: " << secondaryDiagonalMin(m) << std::endl;
    std::cout << "10. Secondary diagonal maximum: " << secondaryDiagonalMax(m) << std::endl;
    std::cout << "11. Matrix average: " << matrixAverage(m) << std::endl;
    std::cout << "12. Lower triangle average: " << lowerTriangleAverage(m) << std::endl;
    std::cout << "13. Upper triangle average: " << upperTriangleAverage(m) << std::endl;

    float sums[N];
    rowSums(m, sums);
    std::cout << "14. Row sums: ";
    for (i = 0; i < N; i++) std::cout << sums[i] << " ";
    std::cout << std::endl;

    columnSums(m, sums);
    std::cout << "15. Column sums: ";
    for (i = 0; i < N; i++) std::cout << sums[i] << " ";
    std::cout << std::endl;

    rowMins(m, sums);
    std::cout << "16. Row minimums: ";
    for (i = 0; i < N; i++) std::cout << sums[i] << " ";
    std::cout << std::endl;

    columnMins(m, sums);
    std::cout << "17. Column minimums: ";
    for (i = 0; i < N; i++) std::cout << sums[i] << " ";
    std::cout << std::endl;

    rowMaxs(m, sums);
    std::cout << "18. Row maximums: ";
    for (i = 0; i < N; i++) std::cout << sums[i] << " ";
    std::cout << std::endl;

    columnMaxs(m, sums);
    std::cout << "19. Column maximums: ";
    for (i = 0; i < N; i++) std::cout << sums[i] << " ";
    std::cout << std::endl;

    rowAverages(m, sums);
    std::cout << "20. Row averages: ";
    for (i = 0; i < N; i++) std::cout << sums[i] << " ";
    std::cout << std::endl;

    columnAverages(m, sums);
    std::cout << "21. Column averages: ";
    for (i = 0; i < N; i++) std::cout << sums[i] << " ";
    std::cout << std::endl;

    float lowerSum, upperSum;
    triangleSums(m, lowerSum, upperSum);
    std::cout << "22. Lower triangle sum: " << lowerSum << ", Upper triangle sum: " << upperSum << std::endl;

    std::cout << "23. Element closest to average: " << closestToAverage(m) << std::endl;
}
