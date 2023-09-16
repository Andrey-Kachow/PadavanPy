#include <stdio.h>

#define MAX_BINARY_STRING_SIZE 33

int binary_string_to_int(char *binary_string) {
    int sum = 0;
    int index = 0;
    while(binary_string[index] != '\0') {
        sum *= 2;
        if (binary_string[index] == '1') {
            sum += 1;
        }
        index++;
    }
    return sum;
}

int decimal_string_to_int(char *decimal_string) {
    int sum = 0;
    int index = 0;
    while(decimal_string[index] != '\0') {
        sum *= 10;
        int decimal_digit_value = (int) decimal_string[index] - '0';
        sum += decimal_digit_value;
        index++;
    }
    return sum;
}

void build_binary_string_from_int(int value, char *output_string) {
    output_string[MAX_BINARY_STRING_SIZE - 1] = '\0';
    int current_position = MAX_BINARY_STRING_SIZE - 2;
    while (value != 0) {
        if (value % 2 == 1) {
            output_string[current_position] = '1';
        } else {
            output_string[current_position] = '0';
        }
        current_position--;
        value /= 2;
    }
    int stop_position = current_position + 1;
    for (int shift_position = stop_position; shift_position < MAX_BINARY_STRING_SIZE; shift_position++) {
        output_string[shift_position - stop_position] = output_string[shift_position];
        output_string[shift_position] = '\0';
    }
}

void test(void) {
    int error_counter = 0;
    char binary_string_buffer[MAX_BINARY_STRING_SIZE];
    for (int number = 0; number < 10000000; number++) {
        build_binary_string_from_int(number, binary_string_buffer);
        int returned_number = binary_string_to_int(binary_string_buffer);
        if (number != returned_number) {
            printf("Error on test value %d. got %d\n", number, returned_number);
            error_counter++;
        }
    }
    if (error_counter == 0) {
        printf("PASS\n");
    }
}

int main(int argc, char **argv) {

    if (argc == 1) {
        test();
        return 0;
    }

    if (argc != 3) {
        printf("Please enter the input in the folowing format:\n> .\\binary.exe [d|b] [decimal|binary]\n");
        return 1;
    }    

    if ((argv[1][0] != 'b' && argv[1][0] != 'd') || argv[1][1] != '\0') {
        printf("Please enter the input in the folowing format:\n> .\\binary.exe [d|b] [decimal|binary]\n");
        return 1;
    }

    if (argv[1][0] == 'b') {
        printf("%d\n", binary_string_to_int(argv[2]));
    } else {
        char binary_string_buffer[MAX_BINARY_STRING_SIZE];
        int value = decimal_string_to_int(argv[2]);

        build_binary_string_from_int(value, binary_string_buffer);
        printf("%s\n", binary_string_buffer);
    }

    return 0;
}