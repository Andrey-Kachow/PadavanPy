#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//
// Allocate 32 characters plus a null-terminator '\0'
//
#define USER_INPUT_BUFFER_SIZE 33
#define USER_INPUT_FORMAT    "%32[^\n]s"
#define EXTRA_WHITE_SPACE 1

void get_rid_of_bad_characters() {
    char dump_char;
    while((dump_char = getchar()) != '\n' && dump_char != EOF);
}

void read_matrix_size(int *width, int *height) {
    int read_result;

    while (true) {
        printf("Please, enter the number of rows in the matrix.\n> ");
        read_result = scanf("%d", height);
        if (read_result == 1) {
            break;
        }
        get_rid_of_bad_characters();
    }  
    while (true) {
        printf("Please, enter the number of columns in the matrix.\n> ");
        read_result = scanf("%d", width);
        if (read_result == 1) {
            break;
        }
        get_rid_of_bad_characters();
    }
    printf("You entered size %dx%d.\n", *height, *width);
}

void fill_with_zeros(int *matrix, int width, int height) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            matrix[width * row + col] = 0;
        }
    }
    // Could also do:
    // memset(matrix, 0, width * height * sizeof(int));
}

void print_number_with_indent(int indent, int number) {
    printf("%*s%d", indent, "", number);
}

int compute_indent(int number) {
    int count = 0;
    while (number >= 10) {
        number = number / 10;
        count++;
    }
    return count;
}

int *get_column_widths(int *matrix, int width, int height) { 
    int *column_widths = malloc(sizeof(*column_widths) * width);
    if (NULL == column_widths) {
        return NULL;
    }
    for (int column_number = 0; column_number < width; column_number++) {
        int maximum_indent = 0;
        for (int row = 0; row < height; row++) {
            int indent = compute_indent(matrix[row * width + column_number]);
            if (indent > maximum_indent) {
                maximum_indent = indent;
            }
        }
        column_widths[column_number] = maximum_indent;
    }
    return column_widths;
}
        
void display_matrix(int *matrix, int width, int height) {
    int *column_widths = get_column_widths(matrix, width, height); 
    if (NULL == column_widths) {
        printf("Unfortunatelly, could not display a matrix.\n");
        return;
    }
    for (int row = 0; row < height; row++) {
        printf("|");
        for (int col = 0; col < width; col++) {
            int num = matrix[row * width + col];
            int indent_size = column_widths[col] + EXTRA_WHITE_SPACE - compute_indent(num);
            print_number_with_indent(indent_size, num);
        }
        printf(" |\n");
    }
    free(column_widths);
}

void fill_with_user_values(int *matrix, int width, int height) {
    printf("Please, initialize the matrix.\n");

    char user_input_buffer[USER_INPUT_BUFFER_SIZE];

    while (true) {
        get_rid_of_bad_characters();
        printf("Please, enter the value X at row I and column J in the form:\n");
        printf("\t\"<row> <column> <value>\"\n");
        printf("or enter \"show\" to see view the matrix.\n");
        printf("Once you entered all the values, enter \"done\".\n>  ");
        
        memset(user_input_buffer, '\0', USER_INPUT_BUFFER_SIZE);
        int input_read_result = scanf(USER_INPUT_FORMAT, user_input_buffer); 

        if (0 == strncmp(user_input_buffer, "show", 4)) {
            printf("The matrix is as follows:\n");
            display_matrix(matrix, width, height);
            continue;
        }

        if (0 == strncmp(user_input_buffer, "done", 4)) {
            printf("You successfully initialized matrix!\n");
            display_matrix(matrix, width, height);
            break;
        }
       
        int row;
        int column;
        int value;
        int entry_initialization_input_result = 
                sscanf(user_input_buffer, "%d%d%d", &row, &column, &value);
        
        if (entry_initialization_input_result != 3) {
            printf("\nIncorrect format. You entered \"%s\"\n\n", user_input_buffer);
            continue;
        }

        matrix[row * width + column] = value;
        printf("You set M[%d][%d] = %d\n", row, column, value);
    }
}

int *create_initial_matrix(int width, int height, bool matrix_should_be_empty) {
    int *matrix = malloc(sizeof(*matrix) * width * height);
    if (matrix == NULL) {
        return NULL;
    }
    fill_with_zeros(matrix, width, height);
    if (!matrix_should_be_empty) {
        fill_with_user_values(matrix, width, height);
    }
    return matrix;
}

int absmax(int first, int second) {
    if (first < 0) {
        first = -first;
    }
    if (second < 0) {
        second = -second;
    }
    if (first < second) {
        return second;
    }
    return first;
}

void adjacent_increment_matrix(int *matrix, int width, int height) {
    int center_row_pos;
    int center_col_pos;    
    int read_result;
    while (true) {
        printf("Please, enter the row position of the centre of matrix arrangement.\n> ");
        read_result = scanf("%d", &center_row_pos);
        if (read_result == 1) {
            break;
        }
        get_rid_of_bad_characters();
    }  
    while (true) {
        printf("Please, enter the column position of the entre of matrix arrangement.\n> ");
        read_result = scanf("%d", &center_col_pos);
        if (read_result == 1) {
            break;
        }
        get_rid_of_bad_characters();
    }
    printf("Placing 1 at the position (%d, %d)...\n", center_row_pos, center_col_pos);
    
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            matrix[row * width + col] = absmax(center_col_pos - col, center_col_pos - row) + 1;
        }
    }
}

int main(int argc, char **argv) {    
    int width;
    int height;

    read_matrix_size(&width, &height);

    bool is_empty_matrix = argc > 1;
    int *matrix = create_initial_matrix(width, height, is_empty_matrix);
    
    if (NULL == matrix) {
        printf("Failed to create matrix.\n");
        return 1;
    }

    adjacent_increment_matrix(matrix, width, height);
    display_matrix(matrix, width, height);

    free(matrix); 

    return 0;
    
}
