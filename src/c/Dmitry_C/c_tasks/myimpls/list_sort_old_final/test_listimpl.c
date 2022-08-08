#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "listimpl.h"
#include "sort.h"

static bool assert_log(bool expr, char* msg) {
    if (!expr) {
        printf("(!) %s\n", msg);
    }
    return expr;
}

/*----------------------------------------------------------------------------*/

bool test_list_value(void) {
    int x = 4;
    struct ListEntry entry = (struct ListEntry){ &x, NULL, NULL };
    int value = list_value(int, &entry);
    return assert_log(value == x, "list_value not working");
}

bool test_list_value_pointer(void) {
    char* word = "Hello world!";
    struct ListEntry entry = (struct ListEntry){ word, NULL, NULL };
    char* value_ptr = (&entry)->value;
    return assert_log(strcmp(word, value_ptr) == 0, "list_value_pointer not working");
}

bool test_strcmp_entry(void) {
    char* x = "Hello";
    char* y = "World!";
    struct ListEntry entry1 = (struct ListEntry){ x, NULL, NULL };
    struct ListEntry entry2 = (struct ListEntry){ y, NULL, NULL };
    return assert_log(strcmp_entry(&entry1, &entry2, NULL) != 0, "strcmp_entry not working");
}

bool sanity_test(void) {
    char* literal = "hi there!";
    char c = *literal;
    literal++;
    char c2 = *literal;
    printf("%c%c---> there\n", c, c2);
    printf("%s %s---> there\n", literal, literal);
    return true;
}

bool test_create_empty_list(void) {
    list_t* list = list_create();
    bool res = assert_log(list_is_empty(list), "list is not empty");
    list_destroy(list, IGNORE_VALUES);
    return res;
}

bool test_list_push_tail_stack_vars(void) {
    list_t* list = list_create();

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
    if (!assert_log(list_is_empty(list), "After popping, illegl state. Expected empty list")) {
        return false;
    }
    return true;
}

bool test_list_push_head_stack_vars(void) {
    list_t* list = list_create();

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

bool test_list_get_entry(void) {
    list_t* list = list_create();
    int x = 4;
    int y = 6;
    int z = 4;
    int w = 6;
    list_push_head(list, &w);
    list_push_head(list, &z);
    list_push_head(list, &y);
    list_push_head(list, &x);

    if (!assert_log(list_value(int, list_get_entry(list, 0)) == x, "0th is not x (4)")) {
        return false;
    }
    if (!assert_log(list_value(int, list_get_entry(list, 1)) == y, "0th is not x (4)")) {
        return false;
    }
    if (!assert_log(list_value(int, list_get_entry(list, 2)) == z, "0th is not x (4)")) {
        return false;
    }
    if (!assert_log(list_value(int, list_get_entry(list, 3)) == w, "0th is not x (4)")) {
        return false;
    }
    list_destroy(list, IGNORE_VALUES);

    list = list_create();
    char* c1 = "abc";
    assert_log(c1[3] == '\0', "literal strings have no zero byte char");
    char* c2 = "abc";
    char* c3 = "abc";
    char* c4 = "abc";
    list_push_head(list, c4);
    list_push_head(list, c3);
    list_push_head(list, c2);
    list_push_head(list, c1);

    if (!assert_log(list_get_entry(list, 0)->value == c1, "0th is not c1")) {
        return false;
    }
    if (!assert_log(list_get_entry(list, 1)->value == c2, "0th is not c2")) {
        return false;
    }
    if (!assert_log(list_get_entry(list, 2)->value == c3, "0th is not c3")) {
        return false;
    }
    if (!assert_log(list_get_entry(list, 3)->value == c4, "0th is not c4")) {
        return false;
    }

    list_destroy(list, IGNORE_VALUES);
    return true;
}

bool test_create_list_from_arr_and_destroy(void) {

    int ARR_SIZE = 5;

    int** test_data = malloc(sizeof(*test_data) * ARR_SIZE);
    if (test_data == NULL) {
        return false;
    }
    for (int i = 0; i < ARR_SIZE; i++) {
        test_data[i] = (int*)malloc(sizeof(int));
        if (test_data[i] == NULL) {
            return false;
        }
        *test_data[i] = i;
    }
    list_t* new_list = list_create_from_arr((void*)test_data, ARR_SIZE);
    if (!assert_log(new_list != NULL, "create list from {0, 1, 2, 3, 4}")) {
        for (int i = 0; i < ARR_SIZE; i++) {
            free(test_data[i]);
        }
        free(test_data);
        return false;
    }
    free(test_data);

    for (int i = 0; i < ARR_SIZE; i++) {
        printf("ith elem %d == %d\n", list_value(int, list_get_entry(new_list, i)), i);
        if (!assert_log(list_value(int, list_get_entry(new_list, i)) == i, "Could not read ith elem")) {
            return false;
        }
    }
    list_destroy(new_list, DESTROY_VALUES);
    return true;
}

bool test_list_push_head_and_read_items(void) {
    printf("Testing list push head and read items...\n");
    list_t* list = list_create();
    char* c1 = "abc";
    assert_log(c1[3] == '\0', "literal strings have no zero byte char");
    char* c2 = "cde";
    char* c3 = "efg";
    char* c4 = "ghi";
    list_push_tail(list, c1);
    list_push_tail(list, c2);
    list_push_tail(list, c3);
    list_push_tail(list, c4);

    struct ListEntry* current = list->head;
    char** cs = malloc(sizeof(char**) * 4);
    if (cs == NULL) {
        return false;
    }

    cs[0] = c1;
    cs[1] = c2;
    cs[2] = c3;
    cs[3] = c4;

    int i = 0;
    while (current != NULL) {
        printf("observing the %dth item\n", i);
        if (!assert_log(current->value == cs[i], "NOOOO")) {
            printf("%s != %s\n", (char*)current->value, cs[i]);
            free(cs);
            return false;
        }
        i++;
        current = current->next;
    }
    free(cs);
    return true;
}

int int_less_cmp_entry(const struct ListEntry* first,
    const struct ListEntry* second,
    void* aux) {

    // int a = first->value;
    // int b = second->value;
    int a = list_value(int, first);
    int b = list_value(int, second);

    printf("a == %d and b == %d\n", a, b);

    return a - b;
}

bool test_list_is_sorted(void) {
    printf("Testing list_is_sorted\n");

    list_t* empty_list = list_create();
    list_t* singleton = list_create();

    bool result = assert_log(
        list_is_sorted(empty_list, int_less_cmp_entry, NULL),
        "empty_list is not sorted"
    );
    if (!result) {
        return false;
    }

    list_destroy(empty_list, IGNORE_VALUES);

    int x = 0;
    list_push_head(singleton, &x);

    result = assert_log(
        list_is_sorted(singleton, int_less_cmp_entry, NULL),
        "singleton is not sorted"
    );
    if (!result) {
        return false;
    }

    list_destroy(singleton, IGNORE_VALUES);

    printf("general list\n");

    // int *ints = {1, 2, 3, 4, 5};
    int** ints = malloc(sizeof(int) * 5);
    if (ints == NULL) {
        return false;
    }
    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    int x4 = 4;
    int x5 = 5;
    ints[0] = &x1;
    ints[1] = &x2;
    ints[2] = &x3;
    ints[3] = &x4;
    ints[4] = &x5;
    list_t* general_list = list_create_from_arr(ints, 5);

    result = assert_log(
        list_is_sorted(general_list, int_less_cmp_entry, NULL),
        "[1, 2, 3, 4, 5] is not sorted"
    );
    if (!result) {
        return false;
    }

    list_destroy(general_list, IGNORE_VALUES);
    return true;
}

bool test_bubble_sort(void) {
    char* w1 = "hello";
    char* w2 = "Andre";
    char* w3 = "apple";
    char* w4 = "phone";
    char* w5 = "clock";
    char* w6 = "mouse";
    char** words = malloc(sizeof(char**) * 6);
    if (words == NULL) {
        return false;
    }

    words[0] = w1;
    words[1] = w2;
    words[2] = w3;
    words[3] = w4;
    words[4] = w5;
    words[5] = w6;
    list_t* test_list = list_create_from_arr(words, 6);
    bubble_sort_list(test_list, strcmp_entry, NULL);
    bool result = assert_log(
        list_is_sorted(test_list, strcmp_entry, NULL),
        "Bubble sort didn't work."
    );
    list_destroy(test_list, IGNORE_VALUES);
    free(words);
    return result;
}

bool test_quick_sort(void) {
    printf("Testing quick sort!\n");
    char* w1 = "hello";
    char* w2 = "Andre";
    char* w3 = "apple";
    char* w4 = "phone";
    char* w5 = "clock";
    char* w6 = "mouse";
    char** words = malloc(sizeof(char**) * 6);
    if (words == NULL) {
        return false;
    }

    words[0] = w1;
    words[1] = w2;
    words[2] = w3;
    words[3] = w4;
    words[4] = w5;
    words[5] = w6;
    list_t* test_list = list_create_from_arr(words, 6);
    printf("Before: ");
    list_of_strings_print(test_list);
    printf("\n");
    test_list = quick_sort_list(test_list, strcmp_entry, NULL, IGNORE_VALUES);
    bool result = assert_log(
        list_is_sorted(test_list, strcmp_entry, NULL),
        "Quick sort didn't work. list is not sorted"
    );
    printf("After: ");
    list_of_strings_print(test_list);
    printf("\n");
    if (!result) {
        return false;
    }
    if (!assert_log(list_length(test_list) == 6, "Expeced list of size 6")) {
        printf(". actual length %d\n", list_length(test_list));
        return false;
    }
    list_destroy(test_list, IGNORE_VALUES);
    free(words);
    return result;
}

/*----------------------------------------------------------------------------*/

static bool (*test_funcs[])(void) = {
  sanity_test,
  test_list_value,
  test_list_value_pointer,
  test_strcmp_entry,
  test_create_empty_list,
  test_list_push_tail_stack_vars,
  test_list_push_head_stack_vars,
  test_list_get_entry,
  test_create_list_from_arr_and_destroy,
  test_list_push_head_and_read_items,
  test_list_is_sorted,
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
