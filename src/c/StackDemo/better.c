#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void) {

    char first_name[5];
    char last_name[5];
    
    char waste_char;
    bool is_buffer_overflow;

    // -----------------

    printf("Please, enter your first name:\n>  ");
    fgets(first_name, 5, stdin);

    is_buffer_overflow = true;
    for (int i = 0; i < 5; i++) {
        if (first_name[i] == '\n') {
            first_name[i] = '\0';
            is_buffer_overflow = false;
        }
    }
    if (is_buffer_overflow) {
        do {
            waste_char = getchar();
        } while (waste_char != '\n' && waste_char != EOF);
    }



    // ------------------

    printf("Please, enter your last name:\n>  ");
    fgets(last_name, 5, stdin);

    is_buffer_overflow = true;
    for (int i = 0; i < 5; i++) {
        if (last_name[i] == '\n') {
            last_name[i] = '\0';
            is_buffer_overflow = false;
        }
    }
    if (is_buffer_overflow) {
        do {
            waste_char = getchar();
        } while (waste_char != '\n' && waste_char != EOF);
    }

    // ------------------

    printf("Welcome to the program, %s %s\n", first_name, last_name);

    return 0;
}