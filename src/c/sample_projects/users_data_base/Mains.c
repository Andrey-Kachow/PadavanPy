#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
char data[15][3][10];

int main() {
    int row = 0;
    while (row < 10) {
        int col = 0;
        while (col < 3) {
            int letter = 0;
            while (letter < 15) {
                data[row][col][letter] = 0;
                letter += 1;
            }
            col += 1;
        }
        row += 1;
    }

    int n = 50;
    char buffer[50];
    fgets(buffer, n, stdin);
    int row_count = 0;

    while (row_count < 10) {
        fgets(buffer, n, stdin);
        printf("%s\n", buffer);
        if (*buffer == '\0' || *buffer == EOF) {
            break;
        } 
        char * letter_pointer = buffer;
        int count = 0;
        int word = 0;
        while (true) {
            data[row_count][word][count] = *letter_pointer;
            letter_pointer += 1;
            count += 1;
            if (*letter_pointer == ',') {
                data[row_count][word][count] = 0;
                count = 0;
                word += 1;
                letter_pointer += 1;
            }
            printf("%s %d, %d, %d\n", data[row_count][word], row_count, word, count);
            if (*letter_pointer == '\n' || *letter_pointer == '\0' || *letter_pointer == EOF) {
                data[row_count][word][count] = 0;
                word = 0;
                count = 0;
                break;
            }
        }
        row_count += 1;
    }


    printf("%s\n", data[0][0]);
    printf("%s\n", data[0][1]);
    printf("%s\n", data[0][2]);
    printf("%s\n", buffer);
    row = 0;
    while (row < row_count) {
        int col = 0;
        while (col < 3) {
            col += 1;
            printf("%s\t", data[row][col]);
        }
        printf("\n");
        row += 1;
    }

    return 0;
}
