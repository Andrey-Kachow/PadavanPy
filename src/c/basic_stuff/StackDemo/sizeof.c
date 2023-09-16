#include <stdio.h>

int main(void) {
    printf("%d\n", sizeof(char));   // 1
    printf("%d\n", sizeof(int));    // 4
    printf("%d\n", sizeof(long));   // 4
    printf("%d\n", sizeof(char *)); // 4
    printf("%d\n", sizeof(void *)); // 4
    printf("%d\n", sizeof(int *));  // 4
    printf("%d\n", sizeof(long *)); // 4
    printf("%d\n", sizeof(short));  // 2
}