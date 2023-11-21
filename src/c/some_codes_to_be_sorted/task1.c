#include <stdio.h>

int to_11th_power(int base);

void test_task_1();

int mod_pow(int base, int power, int modulo);


int task1_calculation(int group_number, int student_number, int third_letter_ordinal) {
    // return (to_11th_power(group_number + student_number) + third_letter_ordinal) % 11;
    return (mod_pow(group_number + student_number, 11, 11) + third_letter_ordinal % 11) % 11;
}

/*
 * Spoilers: BAD approach
 */
int to_11th_power(int base) {
    int accumulated_result = base;
    for (int power_count = 1; power_count < 11; power_count++) {
        accumulated_result *= base;
    }
    return accumulated_result;
}

/*
 * Spoilers: GOOD approach
 */
int mod_pow(int base, int power, int modulo) {
    int accumulator = 1;
    for (int count = 0; count < power; count++) {
        accumulator = (accumulator * base) % modulo;
    }
    return accumulator;
}

int main() {
    test_task_1();

    int group_number;
    int student_number;
    int third_letter_ordinal;

    scanf("%d", &group_number);
    scanf("%d", &student_number);
    scanf("%d", &third_letter_ordinal);

    printf("%d\n", task1_calculation(group_number, student_number, third_letter_ordinal));

    return 0;
}

void test_task_1() {
    if (task1_calculation(25, 17, 17) != 4) {
        printf("Error in the code\n");
    } else {
        printf("Tests pass!\n");
    }
}
