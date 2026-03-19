#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <clocale>

// Функция поиска подстроки в файле
void findSubstring(const char* filename, const char* substring, const char* resultFile) {
    FILE* in = fopen(filename, "r");
    FILE* out = fopen(resultFile, "w");

    if (!in || !out) {
        printf("Ошибка открытия файлов!\n");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    fprintf(out, "Результаты поиска подстроки \"%s\" в файле %s:\n\n", substring, filename);

    char line[256];
    int lineNum = 1;
    int foundCount = 0;

    while (fgets(line, sizeof(line), in)) {
        // Ищем подстроку в строке
        if (strstr(line, substring) != NULL) {
            foundCount++;
            fprintf(out, "Найдено в строке %d: %s", lineNum, line);
        }
        lineNum++;
    }

    if (foundCount == 0) {
        fprintf(out, "Подстрока не найдена.\n");
    }
    else {
        fprintf(out, "\nВсего найдено: %d совпадений.\n", foundCount);
    }

    fclose(in);
    fclose(out);
}

int main() {
    setlocale(LC_ALL, "");

    char ch, filename[50];
    char substring[100];

    printf("Введите имя файла для просмотра: ");
    scanf("%s", filename);

    printf("Введите подстроку для поиска: ");
    scanf("%s", substring);

    FILE* in = fopen(filename, "r");
    if (!in) {
        printf("Файл %s не открыт\n", filename);
        return 1;
    }

    printf("\nСодержимое файла:\n");
    while ((ch = getc(in)) != EOF) {
        putchar(ch);
    }
    fclose(in);

    // Выполняем поиск
    findSubstring(filename, substring, "results.txt");
    printf("\nРезультаты поиска сохранены в файле results.txt\n");

    return 0;
}

