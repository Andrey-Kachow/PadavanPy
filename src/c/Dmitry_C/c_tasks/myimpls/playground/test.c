#include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>

#define PRINT_IDENTIFIER_NAME(IDENTIFIER_TO_PRINT) printf("%s\n",#IDENTIFIER_TO_PRINT)

int(jopa)(int x, int y) {
  return x + y;
}

int main(void) {
  PRINT_IDENTIFIER_NAME(something_as_it_is);
  ({
    printf("jopa\n");
  });
  return 0;
}
