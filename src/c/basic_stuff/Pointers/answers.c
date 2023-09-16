#include <stdio.h>

void sum(int first, int second, int *result) {
    *result = first + second;
}

void quot_rem(int dividiend, int divisor, int *output_quotient, int *output_remainder) {
    *output_quotient = dividiend / divisor;
    *output_remainder = dividiend % divisor;
}

void challenge_quot_rem(int dividiend, int divisor, int *output_quotient, int *output_remainder) {
    int division_accumulator = 0;
    while (dividiend >= divisor) {
        dividiend -= divisor;
        division_accumulator++;
    }
    *output_quotient = division_accumulator;
    *output_remainder = dividiend;
}

void string_copy(char *source, char *destination) {
    char *current_source = source;
    char *current_destination = destination;
    while (*current_source != '\0') {
        *current_destination = *current_source;
        current_destination++;
        current_source++;
    }
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
    printf("+---+---+---+\n");
    printf("| %c | %c | %c |\n", field[0][0], field[0][1], field[0][2]);    
    printf("+---+---+---+\n");
    printf("| %c | %c | %c |\n", field[1][0], field[1][1], field[1][2]);    
    printf("+---+---+---+\n");
    printf("| %c | %c | %c |\n", field[2][0], field[2][1], field[2][2]);    
    printf("+---+---+---+\n");
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