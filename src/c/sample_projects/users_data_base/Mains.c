#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
char data[10][3][15];

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
        if (*buffer == '\n') {
            break;
        }
        printf("0x%x %s", *buffer, buffer);
        char * letter_pointer = buffer;
        int count = 0;
        int word = 0;
        while (true) {
            printf(
                "row %d. word %d. letter %d. lp --> 0x%x '%c'\n",
                row_count,
                word,
                count,
                *letter_pointer,
                *letter_pointer
            );
            if (*letter_pointer == ',') {
                data[row_count][word][count] = '\0';
                count = 0;
                word += 1;
                letter_pointer += 1;
                continue;
            }
            if (*letter_pointer == '\n') {
                count = 0;
                word = 0;
                printf("breaking\n");
                break;
            }
            data[row_count][word][count] = *letter_pointer;
            printf(
                " -- | %s | %s | %s |\n",
                data[row_count][0],
                data[row_count][1],
                data[row_count][2]
            );
            letter_pointer += 1;
            count += 1;
        }
        row_count += 1;
    }


    row = 0;
    while (row < row_count) {
        printf("|  %s  |  %s  |  %s  |\n", data[row][0], data[row][1], data[row][2]);
        row++;
    }

    return 0;
}
