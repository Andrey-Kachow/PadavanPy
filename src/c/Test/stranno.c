#include <stdio.h>

int main(void) {
    char name[4];
    int age;

    printf("Please, enter your age:\n");

    scanf("%d", &age);

    printf("Please, enter your name:\n");

    scanf("%s", name);

    if (age < 18) {
        printf("%s cannot drive.\n", name);
    } else {
        printf("%s can drive legally.\n", name);
    }

    printf("%08x\n", &name);
    printf("%08x\n", name);
    printf("%08x\n", &age);
    return 0;
}
