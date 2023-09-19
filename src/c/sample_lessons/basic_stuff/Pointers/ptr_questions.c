#include <stdio.h>

void sum(int first, int second, int *result) {
    // todo
}

void quot_rem(int dividiend, int divisor, int *output_quotient, int *output_remainder) {
    // todo
}

void challenge_quot_rem(int dividiend, int divisor, int *output_quotient, int *output_remainder) {
    // todo
}

void string_copy(char *source, char *destination) {
    // todo
}

/**
 *  Display Something like this for the input: {{'X', 'O', '-'}, {'O', 'X', '-'}, {'O', '-', 'X'}};
 *  +---+---+---+
 *  | X | O |   |
 *  +---+---+---+
 *  | O | X |   |
 *  +---+---+---+
 *  | O |   | X |
 *  +---+---+---+
 *
 */
void display_tic_tac_toe(char field[3][3]) {
}

int main() {

    char * thing_to_copy = "This string must be copied!";
    char copy_buffer[100];
    string_copy(thing_to_copy, copy_buffer);
    printf("%s\n", copy_buffer);
    printf("%s\n", thing_to_copy);

    int q;
    int r;
    challenge_quot_rem(10, 3, &q, &r);
    printf("%d  %d\n", q, r);

    char input_tic_tac_toe[3][3] = {{'X', 'O', '-'}, {'O', 'X', '-'}, {'O', '-', 'X'}};
    display_tic_tac_toe(input_tic_tac_toe);
}