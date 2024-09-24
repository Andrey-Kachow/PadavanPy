#include <stdio.h>

int main() {
    int times = 0;
    scanf("%d", &times);

    int count_numbers = 0;
    int count = 0;
    int total = 0;
    while (count != times) {
        int number = 0;
        scanf("%d", &number);

        int value = number;
        if (value % 10 == 8 && value % 7 == 0) {
            total += value;
            count_numbers += 1;
        }

        count += 1;
    }
    int difference = total - count_numbers;
    printf("%d", difference);

    return 0;
}