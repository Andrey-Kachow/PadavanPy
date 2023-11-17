#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Schema - 
//     0         1             2
// +--------+----------+---------------+
// | name   | surname  | date of birth |
// +--------+----------+---------------+
// |   ...  |    ...   |    ...        |
// +--------+----------+---------------+
//
//
char data[10][3][15];

void zero_data() {
    int row = 0;
    while (row < 10) {
        int col = 0;
        while (col < 3) {
            int letter = 0;
            while (letter < 15) {
                data[row][col][letter] = 0;
                letter += 1;
            }
            col += 1;
        }
        row += 1;
    }
} 

void output(int row_count) {
    int rowe = 0;
    while (rowe < row_count) {
        int colum = 0;
        while (colum < 3) {
            printf("%s\t", data[rowe][colum]);
            colum += 1;
        }
        printf("\n");
        rowe += 1;
    }
}

void process_table_row(int row_count, char * buffer) {
    char * letter_pointer = buffer;
    int count = 0;
    int word = 0;
    while (true) {
        data[row_count][word][count] = *letter_pointer;
        letter_pointer += 1;
        count += 1;
        if (*letter_pointer == ',') {
            data[row_count][word][count] = 0;
            count = 0;
            word += 1;
            letter_pointer += 1;
        }
        
        if (*letter_pointer == '\n' || *letter_pointer == '\0' || *letter_pointer == EOF) {
            data[row_count][word][count] = 0;
            word = 0;
            count = 0;
            break;
        }
    }
} 

int decimal_string_to_int (char * decimal_string) {
    int index_current1 = 0;
    int result1 = 0;
    // printf("%s\n", decimal_string);
    while(decimal_string[index_current1] != '\0') {
        result1 = result1 * 10 + decimal_string[index_current1] - '0';
        index_current1 += 1;
    }
    return result1;
}

/*
    Assumption: date format is "dd/MM/yyyy" or "dd.MM.yyyy" or "dd <month-name> yyyy"
*/
int read_year_of_birth(int row_number) {
    char * current = data[row_number][2];
    while (*current != '\0') {
        current += 1;
    }
    current -= 4;
    return decimal_string_to_int(current);
}


/*
    dd[./a-zA-Z]...

    {'d', 'd', '\0'}
*/
int read_day_of_birth(int row_number) {
    int count = 0;
    char minibuffer[3];
    char * current = data[row_number][2];
    while ('0' <= *current && *current <= '9') {
        minibuffer[count] = *current;
        current += 1;
        count += 1;
    }
    minibuffer[count] = '\0';
    return decimal_string_to_int(minibuffer);
}


/*
    January, February, March, etc.

    use strcmp to march the month names

    For example "Elizaveta,Volkova,14 March 2001" ---> 3
*/

char months[12][9] = { // x == Sept, fix the month
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "Septeber",
    "October",
    "November",
    "December"
};

// // linear search function that searches the key in arr
// int linearSearch(int* arr, int size, int key)
// {
//     // starting traversal
//     for (int i = 0; i < size; i++) {
//         // checking condition
//         if (arr[i] == key) {
//             return i;
//         }
//     }
//     return -1;
// }

int find_month_index(char * minibuffer) {
    int number_month = 0;
    while(number_month < 12) {
        if (strcmp(minibuffer, months[number_month]) == 0) {
            return number_month;
        }
       number_month += 1; 
    }
    return -1;
}

int read_month_as_number(int row_number) {
    char buffer[3];
    char * date_of_birth = data[row_number][2];
    buffer[0] = date_of_birth[3];
    buffer[1] = date_of_birth[4];
    buffer[2] = '\0';
    return decimal_string_to_int(buffer);
}

int read_month_of_birth(int row_number) {
    int count = 0;
    char minibuffer1[14];
    char * current = data[row_number][2];
    while(!('A' <= *current && *current <= 'Z')) {
        if (*current == '\0') {
            break;
        } 
        current += 1;
    }
    while(('A' <= *current && *current <= 'Z') || ('a' <= *current && *current <= 'z')) {
        minibuffer1[count] = *current;
        current += 1;
        count += 1;
    }
    minibuffer1[count] = '\0';
    if (*minibuffer1 == '\0') { // if all bad
        return read_month_as_number(row_number);
    }
    return 1 + find_month_index(minibuffer1);
}

int main() {
    zero_data();

    int n = 50; 
    char buffer[50];
    fgets(buffer, n, stdin);
    int row_count = 0;
    while (row_count < 10) {
        fgets(buffer, n, stdin);
        if (*buffer == '\n') {
            break;
        }
        process_table_row(row_count, buffer); 
        row_count += 1;
    }
    
    output(row_count);
    // <Name> <Surname> was born in <year> and is <age> years old
    // for the person in the first row (row 0).

    // TODO - dynamically read the time

    int day = 8;
    int month = 11;
    int year = 2023;

    int count = 0;
    while (count != row_count) {
        int year_of_birth = read_year_of_birth(count);
        int day_birth = read_day_of_birth(count);
        int month_birth = read_month_of_birth(count);
        int birthday_passed = year_of_birth > year || (year_of_birth == year && month_birth > month) || (year_of_birth == year && month_birth == month && day_birth >= day);
        printf("%s %s was born in %d and is %d years old.\n", data[count][0], data[count][1], year_of_birth, year - year_of_birth - !birthday_passed);
        printf("and was born on day %d of the week\n", read_day_of_birth(count));
        printf("and was born in month %d of the year\n", read_month_of_birth(count));
        count += 1;
    }
    return 0;
}
