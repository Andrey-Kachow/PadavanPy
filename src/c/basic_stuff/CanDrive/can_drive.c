#include <stdio.h>

int main(void) {

    printf("Please, enter your name:\n");
    
    char name[20];
    scanf("%s", name);

    printf("Please, enter your age:\n");

    int age;
    scanf("%d", &age);

    if (age < 18) {
        printf("%s cannot drive.", name);
    } else {
        printf("%s can drive legally.", name);
    }

    return 0;
}
