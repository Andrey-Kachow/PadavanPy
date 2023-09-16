#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "bigint.h"

static inline int min(int a, int b) {
  return (a < b) ? a : b;
}

static inline int max(int a, int b) {
  return (a < b) ? b : a;
}

/* Calculates the addition carry bit from the sum of two unsigned words */
static bool add_has_carry(uint32_t first, uint32_t second) {
  uint32_t extra = (first & 1) && (second & 1);
  uint32_t shifted1 = first >> 1;
  uint32_t shifted2 = second >> 1;
  return ((shifted1 + shifted2 + extra) & MSB_MASK) != 0;
}

/* Converts the hex digit to a 4-bit number
   returns UNSIGNED_ERROR_CODE if the char c is not a hex digit */
uint32_t hex_digit_to_nibble(char c) {
  if ('0' <= c && c <= '9') {
    return (c - '0');
  }
  else if ('a' <= c && c <= 'f') {
    return HEX_A_IN_DECIMAL + (uint32_t) (c - 'a');
  }
  else if ('A' <= c && c <= 'F'){
    return HEX_A_IN_DECIMAL + (uint32_t) (c - 'A');
  }
  return UNSIGNED_ERROR_CODE;
}

/* Determines whether the char is a valid hex digit. Not case sensitive */
bool is_hex_digit(char c) {
  return ('0' <= c && c <= '9') || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F');
}

/* Creates unitialized big_int_t structure with array of words initialized with zero */
static big_int_t *allocate_big_int(int word_count) {
  big_int_t *new_big_int = malloc(sizeof(big_int_t));
  if (new_big_int == NULL) {
    return NULL;
  }
  new_big_int->words = calloc(word_count, sizeof(uint32_t));
  if (new_big_int->words == NULL) {
    free(new_big_int);
    return NULL;
  }
  new_big_int->size = word_count;
  return new_big_int;
}

/* Reads the first two characters in a hex literal string and
   returns true if they are "0x" which is a valid hex prefix */
bool read_hex_prefix(char *cur_ch) {
  return cur_ch[0] != '\0'
    && cur_ch[0] == '0'
    && cur_ch[1] != '\0'
    && cur_ch[1] == 'x';
}

/* Reads the hex number prefix of a hex string
   and counts the number of hex digits in a hex number. */
int parse_hex_get_word_count(char *numeric_literal) {
  char *cur_ch = numeric_literal;
  if (!read_hex_prefix(cur_ch)) {
    return -1;
  }
  cur_ch += 2;
  int hex_digit_count = 0;
  while (*cur_ch != '\0') {
    if (!is_hex_digit(*cur_ch)) {
      return -1;
    }
    cur_ch++;
    hex_digit_count++;
  }
  return hex_digit_count / HEX_DIGITS_PER_WORD;
}

/* Return type of the init_byte function.
     REACHED_MSB means only one nibble was initialized
     INIT_CONTINUE means that both nibbles were initalized
                   and we can continue. */
enum byte_init_status {
  REACHED_MSB,
  INIT_CONTINUE
};

/* Initializes the byte given the pointer to current LSB of the hex numeric string */
enum byte_init_status init_byte(big_int_t *new_big_int,
                                char *cur_ch,
                                int word_index,
                                int byte_index) {
  uint32_t first_nibble = hex_digit_to_nibble(*cur_ch);
  uint32_t second_nibble = 0;
  cur_ch--;
  if (*cur_ch != 'x') {
    int shift_left = NIBBLE_SIZE_BITS + BYTES_IN_WORD * byte_index;
    second_nibble = hex_digit_to_nibble(*cur_ch) << shift_left;
  } else {
    new_big_int->words[word_index] = first_nibble;
    return REACHED_MSB;
  }
  new_big_int->words[word_index] = second_nibble | first_nibble;
  return INIT_CONTINUE;
}

void init_bytes(big_int_t *new_big_int, char *cur_ch) {
  bool reached_msb = false;
  for (int word_index = 0; *cur_ch != 'x' && !reached_msb; word_index++) {

    for (int byte_index = 0;
         *cur_ch != 'x' && byte_index < BYTES_IN_WORD && !reached_msb;
         cur_ch--, byte_index++) {

      if (init_byte(new_big_int, cur_ch, word_index, byte_index) == REACHED_MSB) {
        reached_msb = true;
      }
    }
  }
}

big_int_t *big_int_create(const char *numeric_literal) {
  char *cur_ch = (char *) numeric_literal;

  int word_count = parse_hex_get_word_count(cur_ch);
  if (word_count == -1) {
    return NULL;
  }

  big_int_t *new_big_int = allocate_big_int(word_count);
  if (new_big_int == NULL) {
    return NULL;
  }
  cur_ch--;
  init_bytes(new_big_int, cur_ch);
  return new_big_int;
}

static big_int_t *extend(big_int_t *old_big_int) {
  big_int_t *new_big_int = allocate_big_int(old_big_int->size + 1);
  for (size_t i = 0; i < old_big_int->size; i++) {
    new_big_int->words[i] = old_big_int->words[i];
  }
  big_int_destroy(old_big_int);
  return new_big_int;
}

void big_int_destroy(big_int_t *big_int) {
  free(big_int->words);
  free(big_int);
}

big_int_t *big_int_add(big_int_t *first, big_int_t *second) {
  big_int_t *sum = allocate_big_int(max(first->size, second->size));
  uint32_t carry = 0;
  for (size_t i = 0; i < min(first->size, second->size); i++) {
    /* code */
  }
  return NULL;
}

big_int_t *big_int_sub(big_int_t *, big_int_t *);

void big_int_print(big_int_t *);
