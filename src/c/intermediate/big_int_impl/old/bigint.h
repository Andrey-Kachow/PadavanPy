#ifndef BIGINT_H
#define BIGINT_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define HEX_DIGITS_PER_WORD 8
#define HEX_A_IN_DECIMAL 10
#define NIBBLE_SIZE_BITS 4
#define BYTES_IN_WORD 4
#define MSB_MASK 0x80000000
#define UNSIGNED_ERROR_CODE 0xffffffff

typedef struct {
  uint32_t *words;
  size_t size;
} big_int_t;

uint32_t hex_digit_to_nibble(char);
bool is_hex_digit(char);

int parse_hex_get_word_count(char *numeric_literal);

big_int_t *big_int_create(const char *numeric_literal);
void big_int_destroy(big_int_t *);

big_int_t *big_int_add(big_int_t *, big_int_t *);
big_int_t *big_int_sub(big_int_t *, big_int_t *);

void big_int_print(big_int_t *);

#endif
