#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "sort.h"

#define PRINT_IDENTIFIER_NAME(IDENTIFIER_TO_PRINT) \
  do{printf("%s",#IDENTIFIER_TO_PRINT);}while(0)

#define ASSERTION__(EXPR,MSG) \
  do{if(!assert_log(EXPR,MSG)){return(false);}}while(0)

#define ASSERTION_RESULT__(EXPR,MSG) (assert_log(EXPR,MSG))

#define ASSERTION_WITH_REACTION__(EXPR,MSG,REACTION...) \
  if(!assert_log(EXPR,MSG)){do{REACTION}while(false);return(false);}

#define TEST__(TEST_NAME,TEST_BODY...)   \
  bool TEST_NAME (void) {                 \
    PRINT_IDENTIFIER_NAME(TEST_NAME);      \
    printf(" begin:\n\n");                  \
    {TEST_BODY};                             \
    return(true);                             \
  }

static bool assert_log(bool expr, char* msg) {
  if (!expr) {
    printf("(!) %s\n", msg);
  }
  return expr;
}

/*----------------------------------------------------------------------------*/
TEST__(test_sanity, {
  ASSERTION__(1 + 1 == 2, "For some reason 1 + 1 != 2 \n");
})

struct int_holder {
  int value;
  struct list_elem elem;
};

TEST__(test_list_push_pop_front, {
  struct int_holder holder_0 = (struct int_holder) {0, {NULL, NULL}};
  struct int_holder holder_1 = (struct int_holder) {1, {NULL, NULL}};
  struct int_holder holder_2 = (struct int_holder) {2, {NULL, NULL}};
  struct int_holder holder_3 = (struct int_holder) {3, {NULL, NULL}};

  struct int_holder *holders[4] = {&holder_0, &holder_1, &holder_2, &holder_3};

  struct list *list = list_create();
  ASSERTION__(list != NULL, "list_create memory error!");

  for (int i = 0; i < 4; i++) {
    list_push_front(list, &holders[i]->elem);
    struct list_elem *front = list_front(list);
    ASSERTION_WITH_REACTION__(front != NULL, "list_elem NULL check failed", {
      free(list);
    })
    struct int_holder *holder = list_entry(front, struct int_holder, elem);
    ASSERTION_WITH_REACTION__(holder->value == i, "list_elem after push content equality check failed", {
      printf("i == %d\n", i);
      free(list);
    })
  }
  for (int i = 3; i >= 0; i--) {
    struct list_elem *popped_front = list_pop_front(list);
    struct int_holder *holder = list_entry(popped_front, struct int_holder, elem);
    ASSERTION_WITH_REACTION__(holder->value == i, "list_elem after pop content equality check failed", {
      printf("i == %d\n", i);
      free(list);
    });
  }
})

// TEST__(test_list_concat_empty, {
//   struct int_holder holder_0 = (struct int_holder) {0, {NULL, NULL}};
//   struct int_holder holder_1 = (struct int_holder) {1, {NULL, NULL}};
//
//   struct list * list_left_empty = list_create();
//   struct list * list_right_empty = list_create();
//   struct list * list_both_empty_01 = list_create();
//   struct list * list_both_empty_02 = list_create();
//   struct list * singleton_1 = list_create();
//   struct list * singleton_2 = list_create();
//
//   list_push_front(singleton_1, &holder_0.elem);
//   list_push_front(singleton_2, &holder_1.elem);
//
//   ASSERTION_WITH_REACTION__(list_empty(list_concat(list_both_empty_01, list_both_empty_02)))
// })

TEST__(test_list_concat, { ////////////////////? TOOOOODOOOOOOOO //////////////////////////
  struct int_holder holder_0 = (struct int_holder) {0, {NULL, NULL}};
  struct int_holder holder_1 = (struct int_holder) {1, {NULL, NULL}};
  struct int_holder holder_2 = (struct int_holder) {2, {NULL, NULL}};
  struct int_holder holder_3 = (struct int_holder) {3, {NULL, NULL}};

  struct int_holder *holders[4] = {&holder_0, &holder_1, &holder_2, &holder_3};

  struct list *sublist1 = list_create();
  struct list *sublist2 = list_create();
  ASSERTION__(sublist1 != NULL, "list_create memory error!");
  ASSERTION__(sublist2 != NULL, "list_create memory error!");

  list_push_front(sublist1, &holders[1]->elem);
  list_push_front(sublist1, &holders[0]->elem);
  list_push_front(sublist2, &holders[3]->elem);
  list_push_front(sublist2, &holders[2]->elem);

  struct list *concat_result_list = list_concat(sublist1, sublist2);
  ASSERTION__(
    concat_result_list == sublist1,
    "Addresses of the left sublist and result do not match"
  );
  for (int i = 0; i < 4; i++) {
    struct list_elem *popped_front = list_pop_front(concat_result_list);
    struct int_holder *holder = list_entry(popped_front, struct int_holder, elem);
    ASSERTION_WITH_REACTION__(holder->value == i, "list_elem after pop content equality check failed", {
      printf("i == %d\n", i);
      printf("value == %d\n", holder->value);
      free(concat_result_list);
    });
  }
})

TEST__(test_bubble_sort, {
  // INITIALIZATION
  char words[6][6] = {"hello", "Andre", "apple", "phone", "clock", "mouse"};
  struct list* test_list = list_create();
  ASSERTION__(test_list != NULL, "list_create fail");
  for (int i = 0; i < 6; i++) {
    char *word = malloc(sizeof(char) * 6);
    ASSERTION__(word != NULL, "malloc_fail");
    memcpy(word, words[i], 6);
    struct string_holder *holder = string_holder_create();
    ASSERTION__(holder != NULL, "malloc_fail");
    holder->chars = word;
    list_push_back(test_list, &holder->elem);
  }
  printf("Before: ");
  list_of_string_holders_print(test_list);
  printf("\n");

  bubble_sort_list(test_list, strcmp_list_elem, NULL);

  printf("After: ");
  list_of_string_holders_print(test_list);
  printf("\n");

  ASSERTION_WITH_REACTION__(
    list_is_sorted(test_list, strcmp_list_elem, NULL),
    "Bubble sort didn't work.",
    {
      list_destroy(test_list, string_literal_holder_elem_destroy);
    }
  )
  list_destroy(test_list, string_literal_holder_elem_destroy);
})

TEST__(test_quick_sort, {
  // INITIALIZATION
  char words[6][6] = {"hello", "Andre", "apple", "phone", "clock", "mouse"};
  struct list* test_list = list_create();
  ASSERTION__(test_list != NULL, "list_create fail");
  for (int i = 0; i < 6; i++) {
    char *word = malloc(sizeof(char) * 6);
    ASSERTION__(word != NULL, "malloc_fail");
    memcpy(word, words[i], 6);
    struct string_holder *holder = string_holder_create();
    ASSERTION__(holder != NULL, "malloc_fail");
    holder->chars = word;
    list_push_back(test_list, &holder->elem);
  }
  // Tests itself
  printf("Before: ");
  list_of_string_holders_print(test_list);
  printf("\n");

  test_list = quick_sort_list(test_list, strcmp_list_elem, NULL);

  printf("After: ");
  list_of_string_holders_print(test_list);
  printf("\n");

  bool result = ASSERTION_RESULT__(
      list_is_sorted(test_list, strcmp_list_elem, NULL),
      "Quick sort didn't work. list is not sorted"
  );
  ASSERTION_WITH_REACTION__(
    result && list_size(test_list) == 6,
    "Expected sorted list of size 6",
    {
      printf(". actual length %ld\n", list_size(test_list));
      list_destroy(test_list, string_holder_elem_destroy);
    }
  );
  list_destroy(test_list, string_holder_elem_destroy);
  return result;
})
/*----------------------------------------------------------------------------*/

static bool (*test_funcs[])(void) = {
  test_sanity,
  test_list_push_pop_front,
  // test_list_concat,
  test_bubble_sort,
  test_quick_sort,
  NULL
};

void test(void) {
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
