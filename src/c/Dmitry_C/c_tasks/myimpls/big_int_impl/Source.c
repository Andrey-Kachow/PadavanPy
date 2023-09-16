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

BigNum get_big_num_by_str(char* str, size_t* bigNumSize) {

    if (!(str[0] == '0' && str[1] == 'x')) {
        printf("Invalid HEX numeric string %s. '0x' prefix is required!\n", str);
        return NULL;
    }

    char* actual_number_start = str + 2;
    while (*actual_number_start == '0') {
        actual_number_start++;
    }
    int hex_string_len = strlen(actual_number_start);
    if (hex_string_len == 0) {
      hex_string_len = 1;
      actual_number_start--;
    }
    *bigNumSize = (hex_string_len / 8);
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

void print_big_int(big_int_t* big_int) {

    if (big_int->is_negative) {
        printf("-");
    }
    printf("0x");
    for (int i = big_int->size - 1; i >= 0; i--) {
        if (i == big_int->size - 1) {
            printf("%x", big_int->words[i]);
        }
        else {
            printf("%08x", big_int->words[i]);
        }
    }
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

    result->words = sum;
    if (first->is_negative == second->is_negative) {
        result->words = big_num_add(first->words, second->words, sum, first->size, second->size, &result->size);
        if (result->words == NULL) {
            printf("Addition error.\n");
            free(result);
            return NULL;
        }
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
    big_int_t *result = big_int_add(first, second);
    second->is_negative = !second->is_negative;
    return result;
}

unsigned int need_extra(unsigned int first, unsigned int second) {

    return first - second > first;
}

 //Ïðåäóñëîâèå: first >= second â unsigned int
BigNum big_num_sub(BigNum first, BigNum second, BigNum difference,
                   size_t first_size, size_t second_size, size_t* new_size) {

    printf("Using unsigned subtraction\n");

    size_t max_limit_counter = first_size;
    memcpy(difference, first, max_limit_counter * sizeof(unsigned int));

    for (size_t counter = 0; counter < second_size; counter++) {
        unsigned int need_extra_bit = need_extra(difference[counter], second[counter]);
        if (!need_extra_bit) {
          difference[counter] = difference[counter] - second[counter];
          continue;
        }
        size_t one_search = counter + 1;
        while (difference[one_search] == 0 && one_search < max_limit_counter) {
            difference[one_search]--;
            one_search++;
        }
        difference[one_search]--;

        if (difference[counter] == 0) {
          difference[counter] = 0xffffffff;
          continue;
        }

        unsigned int mask = second[counter];
        int mask_count = 0;
        while (mask != 1) {
          mask >>= 1;
          mask_count++;
        }
        if (mask_count != 0) {
          mask <<= mask_count;
          difference[counter] += mask + (((int) 0x80000000) >> (31 - mask_count));
        }
        difference[counter] = difference[counter] - second[counter];
    }

    *new_size = max_limit_counter;
    while (difference[*new_size - 1] == 0 && *new_size > 2) {
        (*new_size)--;
    }

    if (*new_size != max_limit_counter) {
        printf("Reallocating memory\n");
        printf("%ld old size and now %ld size\n", max_limit_counter, *new_size);
        BigNum new_difference = (BigNum)realloc(difference, (*new_size) * sizeof(unsigned int));
        if (new_difference == NULL) {
            free(difference);
            return NULL;
        }
        return new_difference;
    }

    return difference;
}

unsigned int carry_of_sum(unsigned int first, unsigned int second) {

    return first + second < first;
}

BigNum big_num_add(BigNum first, BigNum second, BigNum sum,
                   size_t first_size, size_t second_size, size_t* new_size) {

    printf("Using unsigned addition\n");
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
      unsigned int carry = carry_of_sum(sum[counter], lower_num[counter]);
      sum[counter] += lower_num[counter] + last_carry;
      last_carry = carry;
    }
    while (last_carry != 0 && counter < max_limit_counter) {
        int last_last_carry = last_carry;
        last_carry = carry_of_sum(sum[counter], 1);
        sum[counter] += last_last_carry;
        counter++;
    }

    if (last_carry != 0) {
        printf("Reallocating memory\n");
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
