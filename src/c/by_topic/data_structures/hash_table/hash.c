#include <stdio.h>

unsigned int getHashKey(unsigned long x) {
    return (x * 11400714819323198549ul) >> (64 - 7);
}

int main()
{
    for (int i = 0; i < 1000; i++) {
        printf("%d ", getHashKey(i));
    }

    return 0;
}
