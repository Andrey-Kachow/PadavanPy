#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned int* BigNum;

typedef struct {
    size_t size;
    BigNum words;
    bool is_negative;
} big_int_t;

#define HEX_A_IN_DECIMAL 10
#define UNSIGNED_INT_ERROR 0xffffffff
#define IN
#define OUT

BigNum big_num_add(BigNum, BigNum, BigNum, size_t, size_t, size_t*);
BigNum big_num_sub(BigNum, BigNum, BigNum, size_t, size_t, size_t*);


unsigned int hex_char_to_number(char symbol) {

    if ('0' <= symbol && symbol <= '9') {
        return symbol - '0';
    }
    else if ('A' <= symbol && symbol <= 'F') {
        return symbol - 'A' + HEX_A_IN_DECIMAL;
    }
    else if ('a' <= symbol && symbol <= 'f') {
        return symbol - 'a' + HEX_A_IN_DECIMAL;
    }

    return UNSIGNED_INT_ERROR;
}

BigNum get_big_num_by_str(IN const char* str, OUT size_t* bigNumSize) {

    if (!(str[0] == '0' && str[1] == 'x')) {
        printf("Invalid HEX numeric string.\n");
        return NULL;
    }

    char* actual_number_start = (char *) str + 2;
    while (*actual_number_start == '0') {
        actual_number_start++;
    }
    int hex_string_len = strlen(actual_number_start);
    if (hex_string_len <= 2) {
        printf("Invalid HEX numeric string.\n");
        return NULL;
    }
    *bigNumSize = ((hex_string_len) / 8);
    if (hex_string_len % 8 != 0) {
        *bigNumSize += 1;
    }
    BigNum bigNum = calloc (*bigNumSize, sizeof(unsigned int));
    if (bigNum == NULL) {
        printf("Memory error.\n");
        return NULL;
    }

    char* cur_ch = (char*)actual_number_start + hex_string_len - 1;
    unsigned int* cur_word = bigNum;
    int cur_hex_pos = 0;
    while (*cur_ch != 'x') {

        unsigned int hex_digit_value = hex_char_to_number(*cur_ch);
        if (hex_digit_value == UNSIGNED_INT_ERROR) {
            printf("Incorrect char %c in expected HEX string.", *cur_ch);
            free(bigNum);
            return NULL;
        }
        int shift = cur_hex_pos * 4;
        hex_digit_value = hex_digit_value << shift;
        *cur_word |= hex_digit_value;

        cur_hex_pos++;
        if (cur_hex_pos == 8) {
            cur_word++;
            cur_hex_pos = 0;
        }
        cur_ch--;
    }


    return bigNum;
}

big_int_t* big_int_create(char* hex_str) {

    big_int_t* new_big_int = malloc(sizeof(big_int_t));
    if (new_big_int == NULL) {
        printf("Memory error.\n");
        return NULL;
    }

    char* pointer_hex_literal_begin = hex_str;
    if (*pointer_hex_literal_begin == '-') {
        new_big_int->is_negative = true;
        pointer_hex_literal_begin++;
    }
    else {
        new_big_int->is_negative = false;
    }

    new_big_int->words = get_big_num_by_str(pointer_hex_literal_begin, &new_big_int->size);
    if (new_big_int->words == NULL) {
        free(new_big_int);
        return NULL;
    }

    return new_big_int;
}

void print_big_num(BigNum num, size_t size) {
  printf("0x");
  for (int i = size - 1; i >= 0; i--) {
      if (i == size - 1) {
          printf("%x", num[i]);
      }
      else {
          printf("%08x", num[i]);
      }
  }
}

void print_big_int(big_int_t* big_int) {

    if (big_int->is_negative) {
        printf("-");
    }
    print_big_num(big_int->words, big_int->size);
}

bool big_num_less(BigNum first, BigNum second, size_t first_size, size_t second_size) {

    if (first_size != second_size) {
        return first_size < second_size;
    }

    for (int i = first_size - 1; i >= 0; i--) {
        if (first[i] == second[i]) {
            continue;
        }
        return first[i] < second[i];
    }

    return false;
}

big_int_t* big_int_add(big_int_t* first, big_int_t* second) {

    size_t result_size = (first->size > second->size) ? first->size : second->size;
    big_int_t* result = malloc(sizeof(big_int_t));
    if (result == NULL) {
        printf("Memory error.\n");
        return NULL;
    }
    BigNum sum = calloc(result_size, sizeof(*sum));
    if (sum == NULL) {
        printf("Memory error.\n");
        free(result);
        return NULL;
    }

    if (first->is_negative == second->is_negative) {
        sum = big_num_add(first->words, second->words, sum, first->size, second->size, &result->size);
        if (sum == NULL) {
            printf("Addition error.\n");
            free(result);
            return NULL;
        }
        result->words = sum;
        result->is_negative = first->is_negative;
    }
    else {
        big_int_t* subtrahend;
        big_int_t* subtractor;

        if (big_num_less(first->words, second->words, first->size, second->size)) {
            subtrahend = second;
            subtractor = first;
        }
        else {
            subtrahend = first;
            subtractor = second;
        }

        result->is_negative = subtrahend->is_negative;
        result->words = big_num_sub(subtrahend->words, subtractor->words, sum, subtrahend->size, subtractor->size, &result->size);
        if (result->words == NULL) {
            printf("Addition error.\n");
            free(result);
            return NULL;
        }
    }

    return result;
}

big_int_t* big_int_sub(big_int_t* first, big_int_t* second) {
    second->is_negative = !second->is_negative;
    return big_int_add(first, second);
}

unsigned int need_extra(unsigned int first, unsigned int second) {

    return first - second > first;
}

 // Precondition: first >= second � unsigned int
BigNum big_num_sub(BigNum first, BigNum second, BigNum difference,
                   size_t first_size, size_t second_size, size_t* new_size) {

    print_big_num(first, first_size);
    printf(" - ");
    print_big_num(second, second_size);
    printf("\n\n...");


    size_t max_limit_counter = first_size;
    memcpy(difference, first, max_limit_counter * sizeof(unsigned int));

    for (size_t counter = 0; counter < max_limit_counter; counter++) {
        if (need_extra(first[counter], second[counter])) {
            size_t one_search = counter + 1;
            while (difference[one_search] == 0 && one_search < max_limit_counter) {
                difference[one_search]--;
                one_search++;
            }
            difference[one_search]--;
        }
        difference[counter] = first[counter] - second[counter];
    }

    *new_size = max_limit_counter;
    while (difference[*new_size - 1] == 0 && *new_size > 1) {
        (*new_size)--;
    }

    if (difference[max_limit_counter] == 0) {
        BigNum new_difference = (BigNum)realloc(difference, (*new_size) * sizeof(unsigned int));
        if (new_difference == NULL) {
            free(difference);
            return false;
        }
        difference = new_difference;
    }

    return difference;
}

unsigned int carry_of_sum(unsigned int first, unsigned int second) {

    return first + second < first;
}

BigNum big_num_add(BigNum first, BigNum second, BigNum sum,
                   size_t first_size, size_t second_size, size_t* new_size) {

    size_t min_limit_counter;
    size_t max_limit_counter;
    BigNum lower_num;
    BigNum upper_num;

    if (first_size > second_size) {
        min_limit_counter = second_size;
        max_limit_counter = first_size;
        lower_num = second;
        upper_num = first;
    }
    else {
        min_limit_counter = first_size;
        max_limit_counter = second_size;
        lower_num = first;
        upper_num = second;
    }

    *new_size = max_limit_counter;
    memcpy(sum, upper_num, max_limit_counter * sizeof(unsigned int));

    unsigned int last_carry = 0;
    size_t counter = 0;
    for (; counter < min_limit_counter; counter++) {
        sum[counter] += lower_num[counter] + last_carry;
        last_carry = carry_of_sum(first[counter], second[counter]);
    }
    while (last_carry != 0 && counter < max_limit_counter) {
        sum[counter] += last_carry;
        last_carry = carry_of_sum(upper_num[counter], 1);
    }

    if (last_carry != 0) {
        BigNum new_sum = realloc(sum, (max_limit_counter + 1) * sizeof(unsigned int));
        if (new_sum == NULL) {
            free(sum);
            return NULL;
        }
        *new_size += 1;
        new_sum[max_limit_counter] = 1;
        return new_sum;
    }

    return sum;
}

void big_int_destroy(big_int_t* big_int) {
    free(big_int->words);
    free(big_int);
}

void test(void) {
    char* test_hex_string = "0x0123456789abcdef";
    unsigned int expectation[2] = { 0x89abcdef, 0x01234567 };

    size_t big_int_size = 0;
    BigNum result = get_big_num_by_str(test_hex_string, &big_int_size);

    if (big_int_size != 2) {
        printf("Wrong size! Expected 2.\n");
        return;
    }
    for (int i = 0; i < 2; i++) {
        if (result[i] != expectation[i]) {
            printf("Wrong value at position %d! Expected 0x%08x but got 0x%08x.\n", i, expectation[i], result[i]);
            free(result);
            return;
        }
    }
    free(result);
    printf("Pass +\n");

    big_int_t* some_big_int = big_int_create("-0xfF123");
    if (!some_big_int->is_negative) {
        printf("big_int_create didn't work. Result should be negative.");
        big_int_destroy(some_big_int);
        return;
    }

    printf("Pass +\n");
}

int main(int argc, char* argv[]) {

    if (argc != 4) {
        printf("Incorrect arguments.\n");
        printf("Usage: %s 0x123 [+-] (-)?0x123\n", argv[0]);
        printf("Example 1: %s 0x123 + 0x123\n", argv[0]);
        printf("Example 2: %s 0x123 - -0x123\n", argv[0]);
        printf("Example 3: %s 0x123 + -0x123\n", argv[0]);
        printf("Example 4: %s -0x123 + 0x123\n", argv[0]);
        return 1;
    }

    big_int_t* first_number = big_int_create(argv[1]);
    big_int_t* second_number = big_int_create(argv[3]);
    big_int_t* result;
    if (strcmp(argv[2], "+") == 0) {
        result = big_int_add(first_number, second_number);
    }
    else if (strcmp(argv[2], "-") == 0) {
        result = big_int_sub(first_number, second_number);
    }
    else {
        printf("Incorrect operator. Please use \"+\" or \"-\".\n");
        return 1;
    }
    printf("Result: ");
    print_big_int(result);
    printf("\n");

    free(second_number->words);
    free(first_number->words);
    free(result->words);
    free(second_number);
    free(first_number);
    free(result);
    return 0;
}
