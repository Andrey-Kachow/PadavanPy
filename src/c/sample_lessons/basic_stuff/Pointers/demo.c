#include <stdio.h>

int main() {
    
    char *string = "Hello World!";

    printf("%d is a string's adress\n", string); 

    printf("%c\n", string[0]);
    printf("%c\n", *(string));


    printf("%c\n", string[1]);
    printf("%c\n", string[2]);
    printf("%c\n", *(string + 1));
    printf("%c\n", *(string + 2));
    return 0;
}
