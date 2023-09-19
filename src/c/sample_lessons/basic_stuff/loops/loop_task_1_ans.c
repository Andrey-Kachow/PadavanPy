#include <stdio.h>

void squaresTable(int number) {
    printf("x\tx^2\n");
    int count = 0;
    while (count < number) {
        printf("%d\t%d\n", count, count * count);
        count++;
    }
}

int sumDigits(int number) {
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

int xPower(int x, int power) {
    int product = 1;
    while (power > 0) {
        product *= x;
        power--;
    }
    return product;
}

/*
    X^123 = X * X^122 = X * X * 121 = ...

    X^122 = X * X^121
    X^121 = X * X^120
    ...
    X^N = X * X^(N - 1)
    ...
    X^1 = X * X^0
    X^0 = 1
*/
int r_power(int number, int power) {
    if (power == 0) {
        return 1;
    }
    return number * r_power(number, power - 1);
}

int main() {

    printf("Square table for 10 is as follows:\n");
    squaresTable(10);

    printf("\n\n");

    printf("Sum of the digits of the number %d is %d.\n", 12345, sumDigits(12345));

    printf("%d raised to the power of %d is %d\n", 2, 6, xPower(2, 6));

    return 0;
}