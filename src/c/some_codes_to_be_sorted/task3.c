#include <stdio.h>

int greatest_common_divisor(int first_number, int second_number) {

    if (0 == first_number) {
        return second_number;
    }
    if (0 == second_number) {
        return first_number;
    }

    int greater_number = first_number;
    int lower_number = second_number;
    if (second_number > first_number) {
        greater_number = second_number;
        lower_number = first_number;
    }

    int difference = greater_number - lower_number;
    return greatest_common_divisor(lower_number, difference);
}

int main(void) {
    /*
     * Should print all ones
     */
    printf("%d\n", greatest_common_divisor(0, 0) == 0);
    printf("%d\n", greatest_common_divisor(1, 0) == 1);
    printf("%d\n", greatest_common_divisor(0, 1) == 1);
    printf("%d\n", greatest_common_divisor(42, 56) == 14);
    return 0;
}