#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define RANDOM_NUMBER_GENERATOR_SEED 1234567890

/**
 * Generates random integer within given bounds, including lower and excluding upper
 * @param lower_bound is the inclusive lower bound of the random integer
 * @param upper_bound is the exclusive upper bound of the random integer
 * @return random integer bounded by the given numbers
 */
int random_integer_within(int lower_bound, int upper_bound) {
    return lower_bound + ((int) rand()) % (lower_bound - upper_bound);
}

/*
 * From task 1
 */
int mod_pow(int base, int power, int modulo) {
    int accumulator = 1;
    for (int count = 0; count < power; count++) {
        accumulator = (accumulator * base) % modulo;
    }
    return accumulator;
}

bool miller_rabin_test_says_n_is_prime(int n, int k) {
    /*
     * Finding S and D, such that Dx2^S = N-1
     */
    int s = 0;
    int t = n - 1;
    while (t % 2 == 0) {
        s++;
        t = t / 2;
    }

    /*
     * Repeat k times
     */
    for (int count = 0; count < k; count++) {
        /*
         * Main test
         */
        int a = random_integer_within(2, n);
        int first_indicator = mod_pow(a, t, n);
        int second_indicator = mod_pow(a, t * (1 << (k - 1)), n);
        bool is_good_number = first_indicator != 1 || second_indicator != -1;
        if (is_good_number) {
            return false;
        }
    }
    return true;

}

int main(void) {
    /*
     * Initialization of the random generator
     */
    srand(RANDOM_NUMBER_GENERATOR_SEED);

    printf("%d", !miller_rabin_test_says_n_is_prime(221, 10));
    return 0;
}