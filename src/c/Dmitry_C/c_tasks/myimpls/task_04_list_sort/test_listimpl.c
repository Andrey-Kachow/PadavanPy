#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listimpl.h"

static bool assert_log(bool expr, char *msg) {
  if (!expr) {
    printf("(!) %s\n", msg);
  }
  return expr;
}

/*----------------------------------------------------------------------------*/

bool test_list_value(void) {
  int x = 4;
  struct ListEntry entry = (struct ListEntry){&x, NULL, NULL};
  int value = list_value(int, &entry);
  return assert_log(value == x, "list_value not working");
}

bool test_create_empty_list(void) {
  list_t *list = list_create();
  bool res = assert_log(list_is_empty(list), "list is not empty");
  list_destroy(list, IGNORE_VALUES);
  return res;
}

bool test_list_push_tail_stack_vars() {
  list_t *list = list_create();

  int x = 4;
  int y = 6;

  if (!assert_log(list_push_tail(list, &x), "Could not push tail 4 to empty list")) {
    return false;
  }
  if (!assert_log(list_push_tail(list, &y), "Could not push tail 6 to [4]")) {
    return false;
  }
  if (!assert_log(list_value(int, list_pop_head(list)) == x, "Could not pop 4 from [4, 6]")) {
    return false;
  }
  if (!assert_log(list_value(int, list_pop_head(list)) == y, "Could not pop 6 from [6]")) {
    return false;
  }
  return true;
}

bool test_list_push_head_stack_vars() {
  list_t *list = list_create();

  int x = 4;
  int y = 6;

  if (!assert_log(list_push_head(list, &x), "Could not push head 4 to empty list")) {
    return false;
  }
  if (!assert_log(list_push_head(list, &y), "Could not push head 6 to [4]")) {
    return false;
  }
  if (!assert_log(list_value(int, list_pop_tail(list)) == x, "Could not pop 4 from [6, 4]")) {
    return false;
  }
  if (!assert_log(list_value(int, list_pop_tail(list)) == y, "Could not pop 6 from [6]")) {
    return false;
  }
  return true;
}

bool test_create_list_from_arr_and_destroy() {

  int ARR_SIZE = 5;

  int **test_data = malloc(sizeof(*test_data) * ARR_SIZE);
  for (int i = 0; i < ARR_SIZE; i++) {
    test_data[i] = (int *) malloc(sizeof(int));
    test_data[i][0] = i;
  }
  list_t *new_list = list_create_from_arr((void*) test_data, ARR_SIZE);
  if (!assert_log(new_list != NULL, "create list from {0, 1, 2, 3, 4}")) {
    for (int i = 0; i < ARR_SIZE; i++) {
      free(test_data[i]);
    }
    free(test_data);
    return false;
  }
  for (int i = 0; i < ARR_SIZE; i++) {
    free(test_data[i]);
  }
  free(test_data);

  for (int i = 0; i < ARR_SIZE; i++) {
    if (!assert_log(list_value(int, list_get_entry(new_list, i)) == i, "Could not read ith elem")) {
      return false;
    }
  }
  list_destroy(new_list, DESTROY_VALUES);
  return true;
}

/*----------------------------------------------------------------------------*/

static bool (*test_funcs[])(void) = {
  test_list_value,
  test_create_empty_list,
  test_list_push_tail_stack_vars,
  test_list_push_head_stack_vars,
  NULL
};

int main(void) {
  int success_count = 0;
  int fail_count = 0;
  int i = 0;
  for (; test_funcs[i] != NULL; i++) {
    printf("Test %d\n", i);
    if (test_funcs[i]()) {
      printf("+  pass\n");
      success_count++;
    }
    else {
      printf("-  FAILED!!!\n");
      fail_count++;
    }
    printf("\n");
  }
  int total_count = i;
  printf("successfull: %d\nFAILED: %d\nout of %d tests\n",
         success_count, fail_count, total_count);
  if (fail_count == 0) {
    printf("Good job!\n");
  }
  else {
    printf("Too bad!\n");
  }
}
