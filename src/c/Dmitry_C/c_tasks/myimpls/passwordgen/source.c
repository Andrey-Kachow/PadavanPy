#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define NUM_LETTERS 26
#define NUM_DIGITS 10
#define NUM_SPECIALS 25
#define DECIMAL_RADIX 10

char *symbols_a = "qwertyuiopasdfghjklzxcvbnm";
char *symbols_A = "QWERTYUIOPASDFGHJKLZXCVBNM";
char *symbols_D = "1357924680";
char *symbols_S = "!@#$%%^&*()_-+=/{}[];:'`|\\";

int randint(int min_num, int max_num) {
  return min_num + rand() % (max_num - min_num + 1);
}

void print_usage(void) {
  //TODO!
}

bool allowed_types_invalid(char *char_type_set) {
  size_t size = strlen(char_type_set);
  if (size > 4 || size <= 0) {
    return false;
  }
  printf("You initialized typeset of size %ld. Checking validity...\n", size);
  bool a_init = false;
  bool A_init = false;
  bool D_init = false;
  bool S_init = false;
  for (int count = 0; count < size; count++) {
    switch (char_type_set[count]) {
      case 'a':
        if (a_init) {
          printf("All characters should be unique. 'a' occured more than once!\n");
          return false;
        }
        a_init = true;
        break;
      case 'A':
        if (A_init) {
          printf("All characters should be unique. 'A' occured more than once!\n");
          return false;
        }
        A_init = true;
        break;
      case 'D':
        if (D_init) {
          printf("All characters should be unique. 'D' occured more than once!\n");
          return false;
        }
        D_init = true;
        break;
      case 'S':
        if (S_init) {
          printf("All characters should be unique. 'S' occured more than once!\n");
          return false;
        }
        S_init = true;
        break;
      default:
        printf("Character '%c' should not be in the typeset. Please use only chars from {aASD}\n",
               char_type_set[count]);
        return false;
    }
    printf("Allowed character typeset is correct!\n");
    return true;
  }
  if (a_init + A_init + S_init + D_init != size) {
    printf("The number of initalized type characters doesn't match the input type set size!\n");
    return false;
  }
  return true;
}

bool arguments_are_valid(int argc, char **argv, size_t *min_pw_len, size_t *max_pw_len,
                         size_t *num_pws, char **char_alphabet_or_allowed,
                         int *len_alphabet_or_allowed, bool *is_alphabet) {
  bool use_min_max = false;
  bool use_precise_size = false;
  bool use_allowed_char_types = false;
  bool use_precise_alphabet = false;
  for (int i = 1; i < argc; i += 2) {
    if (argv[i] == NULL) {
      break;
    }
    if (i + 1 >= argc) {
      printf("Odd number of arguments!\n");
      return false;
    }
    printf("Reading %s %s\n", argv[i], argv[i + 1]);

    char *error_pointer = NULL;
    long long parsed_num = -1;

    if (strcmp(argv[i], "-m1") == 0) {
      if (use_precise_size) {
        printf("Options -n and -m1 & -m2 are incompatible!\n");
        return false;
      }
      parsed_num = strtol(argv[i + 1], &error_pointer, DECIMAL_RADIX);
      *min_pw_len = (size_t) parsed_num;
      use_min_max = true;
    }
    else if (strcmp(argv[i], "-m2") == 0) {
      if (use_precise_size) {
        printf("Options -n and -m1 & -m2 are incompatible!\n");
        return false;
      }
      parsed_num = strtol(argv[i + 1], &error_pointer, DECIMAL_RADIX);
      *max_pw_len = (size_t) parsed_num;
      use_min_max = true;
    }
    else if (strcmp(argv[i], "-c") == 0) {
      parsed_num = strtol(argv[i + 1], &error_pointer, DECIMAL_RADIX);
      *num_pws = (size_t) parsed_num;
    }
    else if (strcmp(argv[i], "-n") == 0) {
      if (use_min_max) {
        printf("Options -n and -m1 & -m2 are incompatible!\n");
        return false;
      }
      parsed_num = strtol(argv[i + 1], &error_pointer, DECIMAL_RADIX);
      *max_pw_len = (size_t) parsed_num;
      *min_pw_len = (size_t) parsed_num;
      use_precise_size = true;
    }
    else if (strcmp(argv[i], "-a") == 0) {
      if (use_allowed_char_types) {
        printf("Options -C and -a are incompatible!\n");
        return false;
      }
      *char_alphabet_or_allowed = argv[i + 1];
      use_precise_alphabet = true;
    }
    else if (strcmp(argv[i], "-C") == 0) {
      if (use_precise_alphabet) {
        printf("Options -a and -C are incompatible!\n");
        return false;
      }
      if (!allowed_types_invalid(argv[i + 1])) {
        printf("Incorrect allowed character typeset!\n");
        return false;
      }
      *char_alphabet_or_allowed = argv[i + 1];
      use_allowed_char_types = true;
    }

    if (error_pointer != NULL) {
      if (*error_pointer != '\0') {
        printf("Could not parse number!\n");
        return false;
      }
      else if (parsed_num < 1){
        printf("You should not enter any negative number!\n");
        return false;
      }
      else if (*max_pw_len > 100){
        printf("Max password size can be no more than 100 characters\n");
        printf("Let's be real...\nYou are not going to type such a long password every time, aren't you?\n");
        return false;
      }
    }
  }

  if (*char_alphabet_or_allowed == NULL) {
    printf("Password alphabet cannot be initialized!\n");
    return false;
  }
  *len_alphabet_or_allowed = strlen(*char_alphabet_or_allowed);
  *is_alphabet = use_precise_alphabet;

  if (*min_pw_len <= 0) {
    printf("Minimal password length must be positive number\n");
    return false;
  }
  if (*max_pw_len < *min_pw_len) {
    printf("Maximum password length must be at least as large as minimal password length\n");
    return false;
  }
  if (*num_pws == 0) {
    printf("Desired number of passwords to generate is undefined. Generating 1 password by default...\n");
    *num_pws = 1;
  }
  if (*len_alphabet_or_allowed < 0) {
    printf("Something went wrong! Cannot determine the size of the allowed alphabet or type characters.\n");
    return false;
  }
  if ((use_min_max ^ use_precise_size == 0)) {
    printf("You should either specify the precise password length or allowed password size range.\n");
    return false;
  }
  if (use_precise_alphabet ^ use_allowed_char_types == 0) {
    printf("Please, specify the allowed character typeset (i.e. aS, aSDA or ...) or alphabet (i.e. abco123_$^ or somithing).\n");
    return false;
  }
  return true;
}

void generate_passwords(size_t min_pw_len, size_t max_pw_len,
                        char *char_alphabet_or_allowed, int len_alphabets,
                        bool is_alphabet) {

  size_t actual_size = (size_t) randint(min_pw_len, max_pw_len);
  int max_index = len_alphabets - 1;

  printf("-->  ");
  if (is_alphabet) {
    for (int i = 0; i < actual_size; i++) {
      int rand_index = randint(0, max_index);
      printf("%c", char_alphabet_or_allowed[rand_index]);
    }
    printf("< ");
    printf("\n\n");
    return;
  }

  for (int i = 0; i < actual_size; i++) {
    int rand_index = randint(0, max_index);
    char rand_allowed_char = char_alphabet_or_allowed[rand_index];
    int rand_char_index;
    char *char_type;
    switch (rand_allowed_char) {
      case 'a':
        rand_char_index = randint(0, NUM_LETTERS - 1);
        char_type = symbols_a;
        break;
      case 'A':
        rand_char_index = randint(0, NUM_LETTERS - 1);
        char_type = symbols_A;
        break;
      case 'D':
        rand_char_index = randint(0, NUM_DIGITS - 1);
        char_type = symbols_D;
        break;
      case 'S':
        rand_char_index = randint(0, NUM_SPECIALS - 1);
        char_type = symbols_S;
        break;
      default:
        printf("ERROR!\n");
        return;
    }
    printf("%c", char_type[rand_char_index]);
  }
  printf("\n\n");
}

int main(int argc, char **argv) {
  time_t t;

  /* Random Generator initialization */
  srand((unsigned) time(&t));

  size_t min_pw_len = 0;
  size_t max_pw_len = 0;
  size_t num_pws = 0;
  char * char_alphabet_or_allowed = NULL;
  bool is_alphabet = 0xffffffff;
  int len_alphabet_or_allowed = -1;

  if (!arguments_are_valid(argc, argv, &min_pw_len, &max_pw_len,
                           &num_pws, &char_alphabet_or_allowed,
                           &len_alphabet_or_allowed, &is_alphabet)) {
    printf("Incorrect arguments! Please see the following usage!\n");
    print_usage();
    return 1;
  }

  printf("\nYou passed correct arguments! Here is the result:\n\n");
  for (int i = 0; i < num_pws; i++) {
    generate_passwords(
       min_pw_len,
       max_pw_len,
       char_alphabet_or_allowed,
       len_alphabet_or_allowed,
       is_alphabet
     );
  }

  // generate_passwords(5, 10, "abcdef", 6, true);
  // generate_passwords(7, 15, "abcdef2914", 10, true);
  // generate_passwords(10, 10, "aD", 2, false);
  // generate_passwords(9, 9, "aDSA", 4, false);
  // generate_passwords(8, 8, "aS", 2, false);
  // generate_passwords(7, 7, "aA", 2, false);

  return 0;
}
