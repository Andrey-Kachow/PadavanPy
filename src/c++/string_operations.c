/*
    Домашнее задание на тему "Pointers, Arrays, C-style Strings"

    Примечание: 
        - При решении задачи нельзя пользоваться функциями из <string.h> стандартной библиотеки C,
            такие как strlen, strnlen
        - Нельзя также переводить массив символов в тип str::string из стандартной библиотеки C++
*/
/**
 * Объявление функции учителя. Не трогать :)
 */
void verify_my_solutions();



/*
    Задание 1.

    Реализовать функцию нахождения длины текста.
    На вход подается аргумент типа char * - указатель на начало текста
    Размер текста не доступен, но известно, что текст завершается 
    символом '\0'.  Длина текста - количество символов, не считая
    символа '\0' в конце текста. (он же zero-byte, нуль-терминатор, zero-char) 
*/
int find_string_length(char *str) {

}

/*
    Задание 3.

    Иногда встречаются массивы символов текста, которые не заканчиваются нуль-терминатором.
    Но зато известен предел размера текста N (limit). Например если считывается текстовый файл,
    то это делается частями (chunks), а не весь файл целиком. Иначе можно переполнить память.

    Так вот, напишите более безопасную версию функции нахождения длины текста, 
    которая ограничивается
*/
int safely_find_string_length(char *str, int limit) {

}

void to_lower_case(char* original, char* output) {

}

void to_lower_case(char* original, char* output) {

}

void capitalize(char* original, char* output) {

}


int main(void) {

    verify_my_solutions();
}

void verify_my_solutions() {
const char *sentences[] = {
        "The quick brown fox jumps over the lazy dog.",
        "C programming requires careful memory management and attention to detail.",
        "This is a simple example of a string with spaces and punctuation.",
        "Learning low level programming can be both challenging and rewarding.",
        "Every string in this array contains proper capitalization and structure.",
        "Debugging code often takes more time than writing it in the first place.",
        "Understanding pointers is essential for mastering the C language.",
        "Sometimes the simplest solution is also the most elegant one.",
        "Writing clean and readable code is an important professional skill.",
        "This sentence is included to increase the size of the array significantly.",
        "Another example sentence appears here with proper grammar and spacing.",
        "Testing edge cases helps ensure that programs behave correctly.",
        "This array could be used for testing string length functions.",
        "Always remember to terminate C strings with a null character.",
        "Longer sentences can help test performance and memory handling.",
        "Short sentences are useful but do not cover all scenarios.",
        "Consistency in naming conventions improves code readability.",
        "A well structured program is easier to debug and maintain.",
        "Practice makes perfect when learning systems programming.",
        "This is yet another sentence to expand the dataset further.",
        "The compiler will treat each of these as constant string literals.",
        "Efficient algorithms can drastically improve application performance.",
        "Readable code is often more valuable than overly clever solutions.",
        "This sentence exists purely to increase the size of the array.",
        "Arrays of strings are commonly used in text processing applications.",
        "Memory safety is a critical concern in the C programming language.",
        "Using tools like valgrind can help detect memory leaks.",
        "Every programmer encounters bugs that take hours to resolve.",
        "Patience is an important virtue when working with complex systems.",
        "Well written documentation makes collaboration much easier.",
        "Refactoring code can improve both structure and performance.",
        "This dataset continues to grow with more natural language sentences.",
        "Edge case testing is a hallmark of robust software development.",
        "Clear logic and structure help prevent subtle programming errors.",
        "Understanding how strings are stored is key to avoiding bugs.",
        "This example demonstrates a large collection of string literals.",
        "Some sentences are longer while others remain relatively short.",
        "Maintaining consistent formatting improves overall code quality.",
        "The goal here is to simulate realistic textual data inputs.",
        "Developers often rely on such datasets for testing purposes.",
        "Each sentence here is deliberately written in proper English.",
        "Proper spacing and punctuation make strings more realistic.",
        "Testing with varied input ensures better program reliability.",
        "This continues to expand into a fairly large array of strings.",
        "Large datasets can reveal performance bottlenecks in code.",
        "Programs should handle both small and large inputs efficiently.",
        "This is another well formed sentence included in the array.",
        "You can iterate through this array using a simple loop.",
        "Each element can be passed to a function for processing.",
        "Finally, this concludes the example of a large string array."
    };

    const int sentence_count = sizeof(sentences) / sizeof(sentences[0]);

    for (int count = 0; count < sentence_count; count++) {
        
    }
}