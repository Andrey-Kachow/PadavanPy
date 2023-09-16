#include "sorts.h"

int my_strcmp (const char *first, const char *second) {
  const unsigned char *a = (const unsigned char *) first;
  const unsigned char *b = (const unsigned char *) second;

  for (; *a != '\0' && *a == *b; a++, b++) {}

  return *a < *b ? -1 : *a > *b;
}
