/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

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
    return -1;
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
    return -1;
}

/*
    Задание 3
    Напишите функцию Форматирования текста в нижний регистр.
    Даны два аргумента - указателя на тексты.
    Первый аргумент содержит исходный текст,
    а второй аргумент output - адрес назначения для видоизмененного текста,
    в котором все буквы приведены к нижнему регистру. Например: 
    "HelLLO WoRld" будет преобразован в "hello world"
    Обратите внимание, что функция не возвращает каких либо значений.
    Нужно лишь совершить операции записи в массив output нужных символов.
    
    Примечание: Исходный текст содержит символ завершения строки: '\0'.
        Незабудь те завершить текст вывода завершающим символом.
*/
void to_lower_case(char* original, char* output) {

}

/*
    Задание 4.
    Аналогично Заданию 3, Напишите функцию Форматирования текста в верхний регистр.
    "Hello WorLD" -> "HELLO WORLD"
*/
void to_upper_case(char* original, char* output) {

}

/*
    Задание 4.
    Аналогично Заданию 3, Напишите функцию Форматирования текста в заголовочный формат.
    В этом формате каждое слово начинается с большой буквы, но остальные буквы пишутся
    в нижнем регистре. 
    "HelLo WorLD" -> "Hello World"
*/
void capitalize(char* original, char* output) {

}


int main(void) {

    verify_my_solutions();
}

#include <iostream>
#include <string.h>
#include <vector>
#include <string>

void verify_my_solutions() {
    char *sentences[] = {
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
    
    bool find_string_length_is_correct = true;
    for (int count = 0; count < sentence_count; count++) {
        int expectation = strlen(sentences[count]);
        int actual = find_string_length(sentences[count]); 
        if (expectation != actual) {
            printf("ERROR in function find_string_length");
            printf(". With input \"%s\". ", sentences[count]);
            printf("Expected %d, but actually got %d.\n", expectation, actual);
            find_string_length_is_correct = true;
        }
    }
    if (find_string_length_is_correct) {
        printf("OK! - find_string_length\n");
    }

    bool safely_find_string_length_is_correct = true;
    for (int count = 0; count < sentence_count; count++) {
        for (int limit = 0; limit < 30; limit++) {
            int expectation = strnlen(sentences[count], limit);
            int actual = safely_find_string_length(sentences[count], limit); 
            if (expectation != actual) {
                printf("ERROR in function safely_find_string_length");
                printf(". \nExpression: safely_find_string_length(\"%s\", %d)\n", sentences[count], limit);
                printf("Expected result %d, but actually got %d.\n", expectation, actual);
                safely_find_string_length_is_correct = true;
            }
        }
    }
    if (safely_find_string_length_is_correct) {
        printf("OK! - safely_find_string_length\n");
    }

    std::vector<std::vector<char*>> testCases = {
        {
            "The quick brown fox jumps over the lazy dog.",
            "the quick brown fox jumps over the lazy dog.",
            "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.",
            "The Quick Brown Fox Jumps Over The Lazy Dog."
        },
        {
            "C programming requires careful memory management and attention to detail.",
            "c programming requires careful memory management and attention to detail.",
            "C PROGRAMMING REQUIRES CAREFUL MEMORY MANAGEMENT AND ATTENTION TO DETAIL.",
            "C Programming Requires Careful Memory Management And Attention To Details"
        },
        {
            "This is a simple example of a string with spaces and punctuation.",
            "this is a simple example of a string with spaces and punctuation.",
            "THIS IS A SIMPLE EXAMPLE OF A STRING WITH SPACES AND PUNCTUATION.",
            "This Is A Simple Example Of A String With Spaces And Punctuation.",
        },
        {
            "Learning low level programming can be both challenging and rewarding.",
            "learning low level programming can be both challenging and rewarding.",
            "LEARNING LOW LEVEL PROGRAMMING CAN BE BOTH CHALLENGING AND REWARDING.",
            "Learning Low Level Programming Can Be Both Challenging And Rewarding."
        }
    };
    bool lowerCaseIsCorrect = true;
    bool upperCaseIsCorrect = true;
    bool capitalizeIsCorrect = true;

    char buffer[124];
    for (auto& testCase : testCases) {
        char* original = testCase[0];
        char* lowerCase = testCase[1];
        to_lower_case(original, buffer);
        if (0 != strcmp(lowerCase, buffer)) {
            printf("Error: incorrectly converted");
            printf(" \"%s\" ", original);
            printf("to lowercase:\n");
            printf("   \"%s\"\n", buffer);
            lowerCaseIsCorrect = false;
        }
    }
    for (auto& testCase : testCases) {
        char* original = testCase[0];
        char* upperCase = testCase[2];
        to_upper_case(original, buffer);
        if (0 != strcmp(upperCase, buffer)) {
            printf("Error: incorrectly converted");
            printf(" \"%s\" ", original);
            printf("to uppercase:\n");
            printf("   \"%s\"\n", buffer);
            upperCaseIsCorrect = false;
        }
    }
    for (auto& testCase : testCases) {
        char* original = testCase[0];
        char* capitalized = testCase[3];
        capitalize(original, buffer);
        if (0 != strcmp(capitalized, buffer)) {
            printf("Error: incorrectly capitalized");
            printf(" \"%s\" ", original);
            printf("Got:\n");
            printf("   \"%s\"\n", buffer);
            printf("Instead of:\n");
            printf("   \"%s\"\n", capitalized);
            capitalizeIsCorrect = false;
        }
    }

    if (lowerCaseIsCorrect) {
        printf("OK! - to_upper_case\n");
    }
    if (upperCaseIsCorrect) {
        printf("OK! - to_lower_case\n");
    }
    if (capitalizeIsCorrect) {
        printf("OK! - capitalize\n");
    }
}