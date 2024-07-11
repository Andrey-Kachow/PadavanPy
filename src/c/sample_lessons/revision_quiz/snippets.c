#include <stdio.h>
#include <stdlib.h>

void snippet_1_floats() {
    int three = 3;
    int two = 2;

    float poltorashka = three / two;

    printf("%.6f\n", poltorashka);
}

void snippet_2_pointers() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr1 = arr;
    int *ptr2 = ptr1 + 3;

    printf("%d\n", *(ptr2 - 1));
}

typedef struct {
    char a;  // 1 byte
    int  b;   // 4 bytes
    char c;  // 1 byte
} JustANormalStruct;

void snippet_3_structs_in_memory() {
    JustANormalStruct sample_structure;
    printf("%zu\n", sizeof(sample_structure));
}

void snippet_4_temporal_dead_zone() {
    int x = 1;
    {
        int x = 2;
        printf("Inner x: %d\n", x);
    }
    printf("Outer x: %d\n", x);
}

#define PI 3.14159265359
#define SQUARE(x) (x*x)

void snippet_5_macros() {
    printf("%4.5f\n", SQUARE(PI));
}


void snippet_6_string_manipulation() {
    char str[20];
    strcpy(str, "hello");
    strcat(str, "world");

    printf("%s\n", str);
}


#define DO_TEN_TIMES(BLOCK) do{for(int i=0;i<10;i++){BLOCK}}while(0)

void snippet_1337_crazy_macros() {
    DO_TEN_TIMES ({
        printf("Hello\n");
    });
}

int main(void) {

    // snippet_1_floats();
    // snippet_2_pointers();
    // snippet_3_structs_in_memory();
    // snippet_4_temporal_dead_zone();
    // snippet_5_macros();
    // snippet_6_string_manipulation();
    // snippet_1337_crazy_macros();
 
    return 0;
}