#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
    TASK:
    Sudoku field is 9x9 square each containing a decimal digit.
    The exercise represents sudoku as an array of 45 bytes.

    Every cell is modeled as 4 bits with 0b0000 being a special value for empty cell.
    Every row is modeled as 5 consecutive bytes, where every 4-bit segment (also known as nibble) represents the corresponding cell value.
    Therefore a single byte can store two cells (1 Byte = 8 bits)
    5 bytes store 9 cells, therefore the first byte in each row is zero-padded on the left (four of the most significant bits are always zero)
    As a result the whole 9x9 field is modeled as nine rows or a byte array of size 45.

    NOTICE that the type used for one byte is uint8_t which is equivalent of unsigned char.

    The goal is to implement functions get_digit_at, set_digit_at, and display_field and achieve the desired expected output, shown below the main function.
    You are provided with skeletons and description comments for each function.

    You are also provided with the main function for self assessment.


    Bellow is a hardcoded array that represents the initial sudoku field, refer to display_field function comment for more details.
*/

uint8_t sudoku_field_bits[45] = {
    0x0, 0x00, 0x26, 0x07, 0x01,
    0x6, 0x80, 0x07, 0x00, 0x90,
    0x1, 0x90, 0x00, 0x45, 0x00,
    0x8, 0x20, 0x10, 0x00, 0x40,
    0x0, 0x04, 0x60, 0x29, 0x00,
    0x0, 0x50, 0x00, 0x30, 0x28,
    0x0, 0x09, 0x30, 0x00, 0x74,
    0x0, 0x40, 0x05, 0x00, 0x36,
    0x7, 0x03, 0x01, 0x80, 0x00,
};

/*
    Reads the required 4-bit segment in the byte array and returns the integer that represents the contents of the cell.
    The parameters 'row' and 'column' are the integers between 0 and 8 that represent horizontal and vertical positions of the cell.
*/
int get_digit_at(int row, int column) {
    // TODO
    return -1;
}

/*
    Writes the given value to the required 4-bit segment in the byte array.
    The parameters 'row' and 'column' are the integers between 0 and 8 that represent horizontal and vertical positions of the cell.
    Parameter 'value' is the integer between 1 and 9 that represents the digit of the cell.
*/
void set_digit_at(int row, int column, int value) {
    // TODO
}

/*
    Prints the contents of the field in a (arguably) beautiful way.
    Empty cell is displayed as a dot and spaces are used to separate digits.
    For example, it prints the initial field like this:
    +-------+-------+-------+
    | . . . | 2 6 . | 7 . 1 |
    | 6 8 . | . 7 . | . 9 . |
    | 1 9 . | . . 4 | 5 . . |
    +-------+-------+-------+
    | 8 2 . | 1 . . | . 4 . |
    | . . 4 | 6 . 2 | 9 . . |
    | . 5 . | . . 3 | . 2 8 |
    +-------+-------+-------+
    | . . 9 | 3 . . | . 7 4 |
    | . 4 . | . 5 . | . 3 6 |
    | 7 . 3 | . 1 8 | . . . |
    +-------+-------+-------+
*/
void display_field() {
    // TODO
}

/*
    Bonus Challenge:
    Write a program that takes sudoku field as input and solves it, displaying the answer.
    You can use the sudoku board representation from the previous task.
    Feel free to use your own representation of the sudoku board if you prefer.
*/

int main() {

    if (get_digit_at(1, 1) != 8) {
        printf("get_digit_at function is incorrect!\n");
    }

    display_field();
    set_digit_at(2, 2, 5);
    display_field();

    return 0;
}

/*

    Expected output:

    +-------+-------+-------+
    | . . . | 2 6 . | 7 . 1 |
    | 6 8 . | . 7 . | . 9 . |
    | 1 9 . | . . 4 | 5 . . |
    +-------+-------+-------+
    | 8 2 . | 1 . . | . 4 . |
    | . . 4 | 6 . 2 | 9 . . |
    | . 5 . | . . 3 | . 2 8 |
    +-------+-------+-------+
    | . . 9 | 3 . . | . 7 4 |
    | . 4 . | . 5 . | . 3 6 |
    | 7 . 3 | . 1 8 | . . . |
    +-------+-------+-------+
    +-------+-------+-------+
    | . . . | 2 6 . | 7 . 1 |
    | 6 8 . | . 7 . | . 9 . |
    | 1 9 5 | . . 4 | 5 . . |
    +-------+-------+-------+
    | 8 2 . | 1 . . | . 4 . |
    | . . 4 | 6 . 2 | 9 . . |
    | . 5 . | . . 3 | . 2 8 |
    +-------+-------+-------+
    | . . 9 | 3 . . | . 7 4 |
    | . 4 . | . 5 . | . 3 6 |
    | 7 . 3 | . 1 8 | . . . |
    +-------+-------+-------+
*/