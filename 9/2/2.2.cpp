#include <iostream>
#include <string>

// Шаблон: максимум из двух значений (для чисел и типов с оператором >)
template <class T>
T getmax(T t1, T t2)
{
	return t1 > t2 ? t1 : t2;
}

// Специализация для char*: сравнение строк через strcmp
char* getmax(char *s1, char *s2) {
	return strcmp(s1, s2) > 0 ? s1 : s2;
}

// Шаблон: максимум в массиве
template <class T> 
T getmax(T t[], size_t size) {
	T retval = t[0];
	int i;
	for (i = 0; i < size; i++)
		if (t[i] > retval) retval = t[i];
	return retval;
}
	
void main(void)
{
	int i1 = 3, i2 = 5;
	char *s1 = (char *)"строка 1";
	char *s2 = (char *)"строка 2";
	
	std::cout << "max int = " << getmax(i1, i2) << std::endl;   // Вызов шаблона для int
	std::cout << "max str = " << getmax(s1, s2) << std::endl;   // Вызов специализации для char*
}