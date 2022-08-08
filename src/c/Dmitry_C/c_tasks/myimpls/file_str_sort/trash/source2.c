/*
  Чтобы использовать программу, нужно отправить два аргумента - имена файлов
  Например in.txt и out.txt

  main.exe in.txt out.txt
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

#define STRINGS_COUNT 10
#define MAX_STRING_SIZE 5
#define EXTRA_BYTE_FOR_0_CHAR 1

#define FILE_READ_MODE "r"
#define FILE_WRITE_MODE "w"

#define PRINT_QUOTES true
#define DONT_PRINT_QUOTES false

char initial_buffer[STRINGS_COUNT][MAX_STRING_SIZE];

size_t actual_string_count = STRINGS_COUNT;

char *extra_space[STRINGS_COUNT];

static size_t min(size_t a, size_t b) {
  return (a > b) ? b : a;
}


static void zero_new_line(const char *string, size_t line_size) {
	unsigned char *cur_ch = (unsigned char *) string;
	int count = 0;
	while (*cur_ch != '\n' && *cur_ch != '\0' && count < line_size) {
		cur_ch++;
		count++;
	}
	if (*cur_ch == '\n') {
		*cur_ch = '\0';
	}
}

void swap_strings(int first_index, int second_index) {
  for (int i = 0; i < MAX_STRING_SIZE; i++) {
    char swap_temp_ch = initial_buffer[first_index][i];
    initial_buffer[first_index][i] = initial_buffer[second_index][i];
    initial_buffer[second_index][i] = swap_temp_ch;
  }
  char *swap_temp_addr = extra_space[first_index];
  extra_space[first_index] = extra_space[second_index];
  extra_space[second_index] = swap_temp_addr;
}

int compare_strings(int first_index, int second_index) {
  int initial_comp_res =
      strncmp(initial_buffer[first_index], initial_buffer[second_index], MAX_STRING_SIZE);
  if (initial_comp_res != 0) {
    return initial_comp_res;
  }
  return strcmp(extra_space[first_index], extra_space[second_index]);
}


int quick_sort_partition(int lower, int higher) {
  int current_split_index = lower - 1;
  int sample_index = higher;

  for (int j = lower; j < higher; j++) {
    if (compare_strings(j, sample_index) < 0) {
      current_split_index++;
      swap_strings(current_split_index, j);
    }
  }
  current_split_index++;
  swap_strings(current_split_index, higher);
  return current_split_index;
}

void quick_sort_subarray(int lower, int higher) {
  if (higher <= lower) {
    return;
  }
  int split_index = quick_sort_partition(lower, higher);
  quick_sort_subarray(lower, split_index - 1);
  quick_sort_subarray(split_index + 1, higher);
}

void quick_sort_strings() {
  quick_sort_subarray(0, actual_string_count - 1);
}

void print_string(int index, FILE *stream, bool quotes) {
  char *cur_ch = initial_buffer[index];
  int count = 0;
  if (quotes) {
    fprintf(stream, "\"");
  }
  while (*cur_ch != '\0' && count < MAX_STRING_SIZE) {
    fprintf(stream, "%c", *cur_ch);
    cur_ch++;
    count++;
  }
  if (*cur_ch == '\0' && count <= MAX_STRING_SIZE) {
    if (quotes) {
      fprintf(stream, "\"");
    }
    return;
  }
  cur_ch = extra_space[index];
  while (*cur_ch != '\0') {
    fprintf(stream, "%c", *cur_ch);
    cur_ch++;
  }
  if (quotes) {
    fprintf(stream, "\"");
  }
}

void print_string_storage(void) {
  for (int i = 0; i < actual_string_count; i++) {
    print_string(i, stdout, PRINT_QUOTES);
    printf("\n");
  }
}

bool store_string(char *str, int dst_index, size_t *line_read_len) {
  memset(initial_buffer[dst_index], '\0', MAX_STRING_SIZE);
  int str_len;
  if (line_read_len != NULL) {
    str_len = *line_read_len;
  }
  else {
    str_len = strlen(str);
  }
  size_t fst_write_buf_size = min(str_len, MAX_STRING_SIZE);
  memcpy(initial_buffer[dst_index], str, fst_write_buf_size);

  if (str_len < MAX_STRING_SIZE) {
    extra_space[dst_index] = NULL;
    return true;
  }
  size_t extra_buf_size = str_len - MAX_STRING_SIZE + EXTRA_BYTE_FOR_0_CHAR;
  char *extra_buf = malloc(sizeof(char) * extra_buf_size);
  if (extra_buf == NULL) {
    return false;
  }
  extra_space[dst_index] = extra_buf;
  memcpy(extra_buf, str + fst_write_buf_size, extra_buf_size);
  extra_buf[extra_buf_size - 1] = '\0';
  return true;
}

void clean_up(void) {
  for (int i = 0; i < actual_string_count; i++) {
    free(extra_space[i]);
  }
}

bool file_io_read2(char *file_name)
{
    FILE *in_file = fopen(file_name, "r");
    if (in_file == NULL) {
      printf("No such file %s\n", file_name);
      return false;
    }

    struct stat sb;
    stat(file_name, &sb);

    char *file_contents = malloc(sb.st_size);
    if (file_contents == NULL) {
      printf("Error! Could not open file \"%s\"\n", file_name);
      return false;
    }

    int i = 0;
    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF && i < STRINGS_COUNT) {
      zero_new_line(file_contents, sb.st_size);
      store_string(file_contents, i, NULL);
      i++;
    }
    actual_string_count = i + 1;

    free(file_contents);
    fclose(in_file);
    return true;
}

bool file_io_read(char *file_name) {
  char * line = NULL;
  size_t line_read_len = 0;
  FILE *in_file  = fopen(file_name, FILE_READ_MODE);

  if (in_file == NULL) {
    printf("Error! Could not open file \"%s\"\n", file_name);
    return false;
  }
  for (int i = 0; i < STRINGS_COUNT; i++) {
    if (getdelim(&line, &line_read_len, '\n', in_file) == -1) {
      actual_string_count = i;
      break;
    }
    zero_new_line(line, line_read_len);
    if (line[line_read_len - 1] == '\n') {
      line[line_read_len - 1] = '\0';
      line_read_len--;
    }
    store_string(line, i, &line_read_len);
  }
  fclose(in_file);
  if (line) {
    free(line);
  }
  printf("\n");
  return true;
}

bool file_io_write(char *file_name) {
  FILE *out_file = fopen(file_name, FILE_WRITE_MODE);
  if (out_file == NULL) {
    printf("Error opening the file \"%s\"", file_name);
    return false;
  }
  for (int i = 0; i < actual_string_count; i++) {
    print_string(i, out_file, DONT_PRINT_QUOTES);
    fprintf(out_file, "\n");
  }
  fclose(out_file);
  return true;
}

static void test_mock_file_io(void) { // REQURES STRINGS_COUNT 10
  store_string("four", 0, NULL);
  store_string("five5", 1, NULL);
  store_string("sixsix", 2, NULL);
  store_string("seve777", 3, NULL);
  store_string("8_8_8_8_", 4, NULL);
  store_string("nine_nine", 5, NULL);
  store_string("ten10ten10", 6, NULL);
  store_string("elevenevele", 7, NULL);
  store_string("1", 8, NULL);
  store_string("", 9, NULL);
}

int main(int argc, char **argv) {

  if (argc != 3) {
    printf("Incorrect arguments!\n"
           "Please enter the path to the input file "
           "and the name of the output file.\n");
    return 1;
  }

  if (!file_io_read2(argv[1])) {
    return 1;
  }

  // test_mock_file_io();

  printf("Before sorting:\n\n");
  print_string_storage();

  quick_sort_strings();

  printf("\nAfter sorting:\n\n");
  print_string_storage();

  if (!file_io_write(argv[2])) {
    clean_up();
    return 1;
  }
  clean_up();
  return 0;
}
