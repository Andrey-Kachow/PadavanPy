// Находит длину строки, то есть количество символов в строке не считая '\0'
int mystrlen(char *str) {
	return -1;
}

// Находит длину строки, но не проверяет дальше n-ого индекса
int my_strnlen(char *str, int n) {
	return -1;
}

// Сравнивает две стоки и возвращает одно из трех значений:
// 0  -  если строки одинаковые
// 1  -  если первая строка идет раньше по алфавиту (ascii), чем вторая
// -1 -  если вторая строка идет раньше по алфавиту чем первая.
int mystrcmp(char *first, char *second) {
	return 0;
}


// То же самое, что и myu_strcmp, но проверяет не дальше n-ого индекса.
int my_strncmp(char *first, char *second, int n) {
	return -1;
}

// Копирует num_bytes байт из строки source в строку destination
void my_memcpy(char source, char *destination, int num_bytes) {

}
