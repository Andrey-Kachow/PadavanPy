#include <stdio.h>
// #include <string.h> // ???

int eval(int first, int second, char * operation) {
    int total;
    if (operation[0] == '+') {
        total = first + second;
    }
    else if (operation[0] == '-') {
        total = first - second;
    }
    else if (operation[0] == '*') {
        total = first * second;
    }
    else if (operation[0] == '/') {
        total = first / second;
    }
    else if (strcmp(operation, "pow") == 0) {
        total = 1;
        int count = 0;
        while (second != count) {
            total *= first;
            count += 1;
        }
    } else {
        printf("Error.\n");
    }
    return total;
}

int interactive_main() {
    int total;
    char go[20];
    go[0] = '\0';

    printf("Welcome to Calculator.\n");

    while (strcmp(go, "no") != 0) {
        // Первое число
        printf("Enter number:\n");
        int first;
        scanf("%d", &first);
        // Операция
        printf("Enter operation:\n");
        char operation[20];
        scanf("%s", operation);
        // Второе число
        printf("Enter number:\n");

        int second;
        scanf("%d", &second);  

        int total = eval(first, second, operation);

        printf("Answer is %d.\n", total);
        printf("Would you like to continue (yes, no)?\n");
        scanf("%s", go);
        if (strcmp(go, "no") == 0) {
            break;
        }
    }
    printf("Thank you for using the program.");
    return 0;
}

int decimal_string_to_int (char * decimal_string) {
    int index_current1 = 0;
    int result1 = 0;

    while(decimal_string[index_current1] != '\0') {
        result1 = result1 * 10 + decimal_string[index_current1] - '0';
        index_current1 += 1;
    }
    return result1;
}

int utility_main(char * first, char * operation, char * second) {
    int first_number = decimal_string_to_int(first);
    int second_number = decimal_string_to_int(second);

    int total = eval(first_number, second_number, operation);

    printf("%d\n", total);
    return 0;
}

int main(int argc, char ** argv) {
    if (argc != 1 && argc != 5) {
        return 1;
    }
    if (argc == 1) {
        return interactive_main();
    }
    if (strcmp(argv[1], "--calculate") == 0) {
        return utility_main(argv[2], argv[3], argv[4]);
    } 

    return 0;
}