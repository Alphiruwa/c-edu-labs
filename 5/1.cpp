#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <clocale>

int main()
{
	setlocale(LC_ALL, "");	
	
    char ch, name[50];
    FILE* in;
    printf("Введите имя файла для просмотра: ");
    scanf("%s", name);
    if (!(in = fopen(name, "r")))
        printf("Файл %s не открыт", name);
    else
        while ((ch = getc(in)) != EOF)
            putchar(ch);
}
