#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <clocale>

int main()
{
    setlocale(LC_ALL, "");

    char ch, name[50];
    FILE* in;
    int empty_count = 0, non_empty_count = 0;

    printf("Введите имя файла для просмотра: ");
    scanf("%s", name);

    if (!(in = fopen(name, "r")))
        printf("Файл %s не открыт", name);
    else
    {
        printf("\nСодержимое файла:\n");
        printf("----------------------------------------\n");

        while ((ch = getc(in)) != EOF)
        {
            putchar(ch);

            // Подсчёт символов
            // "Пустые" символы: пробел (32) + управляющие символы (0-31) + DEL (127)
            if (ch == ' ' || (ch >= 0 && ch <= 31) || ch == 127)
                empty_count++;
            else
                non_empty_count++;
        }

        printf("----------------------------------------\n");
        printf("\nСтатистика символов:\n");
        printf("Пустые символы: %d\n", empty_count);
        printf("Непустые символы: %d\n", non_empty_count);
        printf("Всего символов: %d\n", empty_count + non_empty_count);

        fclose(in);
    }

    return 0;
}
