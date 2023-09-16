#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*----------------------------<Task_1>----------------------------------------*/

int sum_diagonal(int **matrix, int matrix_size) {
  int sum = 0;
  for (int counter = 0; counter < matrix_size; counter++) {
    sum += matrix[counter][counter];
  }
  return sum;
}

bool test_sum_diagonal(void) {

  /* Initiallizing Matrix as an array of pointers to int arrays */
  int row_0[5] = {1, 2, 2, 1, 5};
  int row_1[5] = {6, 4, 3, 8, 2};
  int row_2[5] = {4, 2, 2, 6, 5};
  int row_3[5] = {1, 0, 3, 8, 2};
  int row_4[5] = {7, 2, 3, 4, 0};
  int *matrix[5] = {row_0, row_1, row_2, row_3, row_4};
  int expected_sum = 15;

  /* Testing the initialized matrix with the expected sum */
  return expected_sum == sum_diagonal(matrix, 5);
}

/*----------------------------<Task_2>----------------------------------------*/

void int_div(int dividend, int divisor, int *quotient, int *remainder) {
  *quotient = 0;
  while (dividend >= divisor) {
    dividend -= divisor;
    *quotient += 1;
  }
  *remainder = dividend;
}

bool test_int_div(void) {
  int dividend = 20;
  int divisor = 3;

  int expected_quot = 6;
  int expected_rem = 2;
  int actual_quot, actual_rem;

  printf("%d / %d = ", dividend, divisor);
  int_div(dividend, divisor, &actual_quot, &actual_rem);
  printf("%d, (%d)\n", actual_quot, actual_rem);

  return actual_rem == expected_rem && actual_quot == expected_quot;
}

/*----------------------------<Task_3>----------------------------------------*/

void swap_variables(int *first, int *second) {
  *first = *first + *second;
  *second = *first - *second;
  *first = *first - *second;
}

void test_swap_variables(void) {
  int a = 10, b = 20;
  printf("Before swap a = %d, b = %d.\n", a, b);
  swap_variables(&a, &b);
  printf("After swap a = %d, b = %d.\n\n", a, b);
}

/*----------------------------<Task_4>----------------------------------------*/

int fact_product(int n) {
  int product = 1;
  int count = 1;
  int mult_count = 1;
  while (count <= n) {
    product = product * count;
    mult_count++;
    if (mult_count <= n - count + 1) {
      continue;
    }
    count++;
    mult_count = 1;
  }
  return product;
}

bool test_fact_product(void) {
  int Ns[] = {1, 3, 5, 6};
  int expectations[] = {1, 12, 34560, 24883200};
  int num_tests = 4;

  for (int count = 0; count < num_tests; count++) {
    if (expectations[count] != fact_product(Ns[count])) {
      return false;
    }
  }
  return true;
}

/*-----------------------------<MAIN>-----------------------------------------*/
int main(void) {

  if (!test_sum_diagonal()) {
    printf("Diagonal sum function doesn't work!\n");
    return 1;
  }
  else {
    printf("Diagonal sum function test passed!\n\n");
  }

  if (!test_int_div()) {
    printf("Integer division function doesn't work!\n");
    return 1;
  }
  else {
    printf("Integer division function test passed!\n\n");
  }

  test_swap_variables();

  if (!test_fact_product()) {
    printf("Factorial product function doesn't work\n");
    return 1;
  }
  else {
    printf("Factorial product function test passed!\n\n");
  }

  return 0;
}
