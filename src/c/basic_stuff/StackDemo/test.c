#include <stdio.h>

int main(void) {

    char first_name[5];
    char last_name[5];

    printf("Please, enter your first name:\n>  ");
    scanf("%s", first_name);

    printf("Please, enter your last name:\n>  ");
    scanf("%s", last_name);

    printf("Welcome to the program, %s %s\n", first_name, last_name);

    return 0;
}

/*
    // printf("%d\n%d\n", first_name, last_name);  
    abcdefghijkl
    mnopqrstu
*/

