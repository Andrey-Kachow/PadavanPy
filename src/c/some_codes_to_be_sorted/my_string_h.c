// KK code
#include <stdio.h>
#include <stdbool.h>

int mystrlen(char * text) {
    int count = 0;
    while (text[count] != '\0') {
        count += 1;
    }
    return count;
}

int my_strlen(char * text, int n) {
    bool status = false;
    int count = 0;
    for (int i=0; status != true && i != n; i++) {
        if (text[i] == '\0') {
            status = true;
        } else {
            count += 1;
        }
    }
    return count;
}

int mystrcmp(char * first, char * second) {
    int status_return = 0;
    bool status = false;
    for (int i=0; status != true; i++) {
        if (first[i] == '\0' && second[i] != '\0') {
            return -1;
        }
        if (first[i] != '\0' && second[i] == '\0') {
            return  1;
        }
        if (first[i] != second[i]) {
            int first_num = first[i];
            int second_num = second[i];
            if (first_num < second_num) {
                return -1;
            }
            if (first_num > second_num) {
                return 1;
            }
        }
        if (first[i] == '\0' && second[i] == '\0') {
            status = true;
        }
    }
    return 0;
}

int my_strncmp(char * first, char * second, int n) {
    int status_return = 0;
    bool status = false;
    for (int i=0; status != true && i != n; i++) {
        if (first[i] == '\0' && second[i] != '\0') {
            return -1;
        }
        if (first[i] != '\0' && second[i] == '\0') {
            return  1;
        }
        if (first[i] != second[i]) {
            int first_num = first[i];
            int second_num = second[i];
            if (first_num < second_num) {
                return -1;
            }
            if (first_num > second_num) {
                return 1;
            }
        }
        if (first[i] == '\0' && second[i] == '\0') {
            status = true;
        }
    }
    return 0;
}

void my_memcpy(char * source, char * destination, int num_bytes) {
    for (int i=0; i < num_bytes; i++) {
        if (i != num_bytes) {
            destination[i] = source[i];
        }
    }
}

// void demo() {
//     char str1[] = "Geeks";
//     char str2[] = "Quiz";

//     puts("str1 before memcpy ");
//     puts(str1);

//     // Copies contents of str2 to str1
//     memcpy(str1, str2, sizeof(str2));

//     puts("\nstr1 after memcpy ");
//     puts(str1);

//     return 0;
// }

void my_memset(char * memptr, int val, int num) {
    for (int i=0; i < num; i++) {
        memptr[i] = val;
    }
}

int strcasecmp(char * str1, char * str2) {
    for (int i=0; str1[i] != '\0' || str2[i] != '\0'; i++) { // проверка букв
        int first = str1[i];
        int second = str2[i];
        if (first >= 65 && first <= 92) {
            first += 32;
        }
        if (second >= 65 && second <= 92) {
            second += 32;
        }
        if (first != 0 && second != 0) {
            if (first != second) {
                return -1;
            }
        } else {
            if (first == 0 && second != 0) {
                return -1;
            }
            if (first != 0 && second == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int strncasecmp(char * str1, char * str2, int n) {
    for (int i=0; (str1[i] != '\0' || str2[i] != '\0') && i != n; i++) { // проверка букв
        int first = str1[i];
        int second = str2[i];
        if (first >= 65 && first <= 92) {
            first += 32;
        }
        if (second >= 65 && second <= 92) {
            second += 32;
        }
        if (first != 0 && second != 0) {
            if (first != second) {
                return -1;
            }
        } else {
            if (first == 0 && second != 0) {
                return -1;
            }
            if (first != 0 && second == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void strcat(char * str1, char * str2) {
    bool status = false;
    int i = 0;
    while (status != true) {
        if (str1[i] == '\0') {
            str1[i] = " ";
            int j = 0;
            while (str2[j] != '\0') {
                str1[i] = str2[j];
                i += 1;
                j += 1;
            }
            status = true;
        }
        i += 1;
    }
}

char * my_substring(char * str, int start, int len) {
    int i = 0;
    i += start;
    char * new = (char*)malloc((len + 1) * sizeof(char));
    int j = 0;
    // !(A && B) <=> !A || !B
    // !(A || B) <=> !A && !B
    // while (!(str[i] == '\0' || j == len)) {
    while (str[i] != '\0' && j != len) {
        new[j] = str[i];
        i += 1;
        j += 1;
    }
    new[j] = '\0';
    return new;
}

char ** my_split_lines(char * text, int * size) {
    int count_n = 0;
    for (int i=0; text[i]!='\0'; i++) {
        if (text[i] == '\n') {
            count_n += 1;
        }
    }
    char ** strings = malloc((count_n+1) * sizeof(char*)); //// home + сделать анимацию ракетного двигателя
    int j = 0;
    int k = 0;
    for (int i=0; i!=count_n + 1; i++) {
        if (text[i] != '\n') {
            j += 1;
        } else {
            strings[k] = malloc((j+1) * sizeof(char));
            my_memcpy(text + i - j, strings[k], j);
            strings[k][j] = '\0';
            j = 0;
            k += 1;
        }
    }
    *size = count_n + 1;
    return strings;
}
    // char * new = (char*)malloc((15 + 1) * sizeof(char));
    // char ** strings = malloc((3+1) * sizeof(char*));
    // for (int i=0; i!=4; i++) {
    //     strings[i] = malloc((17) * sizeof(char));
    // }
    // int j=0;
    // for (; text[j] != '\0'; j++) {
    //     if (text[j] == '\n') {
    //         new[j] = '\n';
    //         j += 1;
    //     }
    //     new[j] = text[j];
    // }
    // new[j] = '\0';
    // return new;

int main() {

    // // Массивы текстов на стеке
    // char text1[8] = {'h', 'e', 'l', 'l', 'o', 'o', 'o', '!'};
    // char text2[8] = {'H', 'E', 'L', 'L', 'O', 'O', 'O', '!'};
    // char * text3 = (char *) malloc(8);
    // memcpy(text3, "Goodbye!", 8);

    // printf("%s<====>", text1);
    // printf("%s\n", text2);
    // printf("%d %d\n", mystrlen(text1), mystrlen(text2));

    // printf("%s\n", text3);
    // printf("%d\n", mystrlen(text3));

    char text[20] = "Hello, world";
    char first[20] = "HIIIIIIII";
    char second[20] = "Hello";

    char text1[30] = "Every good programmer";
    char str1[15] = "helloO";
    char str2[15] = "hellOx";

    char text2[20] = "Hello World";
    char text3[18] = "Hello\nWorld\n!";
    // my_memset(text1, '_', 5);
    // printf("%s", text1);

    // strcat(str1, str2);
    // printf("%s", str1);


    // printf("%d\n", strcasecmp(str1, str2));
    // printf("%d", strncasecmp(str1, str2, 7));

    // printf("%s\n", my_substring("Hello World", 3, 5));
    int number_of_strings;
    char ** messages = my_split_lines(text3, &number_of_strings);
    for (int i=0; i!=number_of_strings; i++) {
        printf("%s", messages[i]);
    }

    // demo();
    // int n = 100;
    // int n1 = 19;
    // printf("%d", mystrlen(text));
    // printf("%d", my_strlen(text, n));
    // printf("%d", mystrcmp(first, second));
    // printf("%d", my_strncmp(first, second, n1));
    // my_memcpy(first, second, n1);
    // printf("%s", second);
    return 0;
}