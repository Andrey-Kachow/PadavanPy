#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "bigint.h"

#define PRINT_IDENTIFIER_NAME(IDENTIFIER_TO_PRINT) \
  do{printf("%s",#IDENTIFIER_TO_PRINT);}while(0)

#define ASSERTION__(EXPR,MSG) \
  do{if(!assert_log(EXPR,MSG)){return(false);}}while(0)

#define ASSERTION_RESULT__(EXPR,MSG) (assert_log(EXPR,MSG))

#define ASSERTION_WITH_REACTION__(EXPR,MSG,REACTION...) \
  do{if(!assert_log(EXPR,MSG)){do{REACTION}while(false);return(false);}}while(false)

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

/*----------------------------------TESTS-------------------------------------*/
TEST__(test_sanity, {
  ASSERTION__(1 + 1 == 2, "For some reason 1 + 1 != 2 \n");
})

TEST__(test_read_hex_prefix, {
  char *test_string = "0xab";
  char *test_cur_ch = test_string;
  ASSERTION__(read_hex_prefix(test_cur_ch), "Didn't read hex prefix");
  ASSERTION__(test_cur_ch = test_string + 2, "Didn't get expected prefix");

  char *test_string2 = "ab";
  char *test_cur_ch2 = test_string2;
  ASSERTION__(!read_hex_prefix(test_cur_ch2), "Shouldn't read hex prefix");
})

TEST__(test_parse_hex_get_word_count, {
  ASSERTION_WITH_REACTION__(parse_hex_get_word_count("0xab") == 1, "|0xab| != 1", {
    printf("Actual word count is %d\n", parse_hex_get_word_count("0xab"));
  });
  ASSERTION_WITH_REACTION__(parse_hex_get_word_count("0xabcd") == 1, "|0xabcd| != 1", {
    printf("Actual word count is %d\n", parse_hex_get_word_count("0xabcd"));
  });
  ASSERTION_WITH_REACTION__(parse_hex_get_word_count("0xabc") == 1, "|0xabc| != 1", {
    printf("Actual word count is %d\n", parse_hex_get_word_count("0xabc"));
  });
  ASSERTION_WITH_REACTION__(parse_hex_get_word_count("0x123456789") == 2, "|0x12345678| != 2", {
    printf("Actual word count is %d\n", parse_hex_get_word_count("0x12345678"));
  });
  ASSERTION_WITH_REACTION__(
    parse_hex_get_word_count("0xabdeerasxcqweqweqweqw") == 3,
    "|0xabdeerasxcqweqweqweqw| != 3",
    {
      printf("Actual word count is %d\n", parse_hex_get_word_count("0xabdeerasxcqweqweqweqw"));
    }
  );
  ASSERTION_WITH_REACTION__(parse_hex_get_word_count("0x0") == 1, "|0x0| != 1", {
    printf("Actual word count is %d\n", parse_hex_get_word_count("0x0"));
  });
})

TEST__(test_big_int_create, {
  char *test_hex_string = "0x0123456789abcdef";
  uint32_t expectation[4] = {0xcdef, 0x89ab, 0x4567, 0x0123};

  big_int_t *result = big_int_create(test_hex_string);

  ASSERTION__(result->size == 4, "Wrong size! Expected 4");

  for (int i = 0; i < 4; i++) {
    ASSERTION_WITH_REACTION__(result->words[i] == expectation[i], "Didn't match expectation", {
      big_int_destroy(result);
    });
  }
})

/*----------------------------------------------------------------------------*/

static bool (*test_funcs[])(void) = {
  test_sanity,
  test_read_hex_prefix,
  test_parse_hex_get_word_count,
  test_big_int_create,
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
    return 0;
}
