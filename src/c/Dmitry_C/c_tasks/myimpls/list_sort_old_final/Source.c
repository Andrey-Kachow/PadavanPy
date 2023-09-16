#include <stdio.h>
#include <stdlib.h>
#include "test_listimpl.h"
#include "listimpl.h"
#include "sort.h"

#define MAX_LINE_INPUT 256

int main() {
	int input = 0;
	int number_of_lines = 0;

	printf_s("Select the program option:\n1) Test start.\n2) Default start.\nYour choice: ");
	scanf_s("%d", &input);
	printf_s("\n");

	if (input != 1 && input != 2) {
		printf_s("Please choose 1 or 2.");
		return 1;
	}
	if (input == 1) {
		test();
		return 0;
	}

	list_t* List = list_create();
	printf_s("How many lines do you want to enter?\nEnter: ");
	scanf_s("%d", &number_of_lines);
	if (!number_of_lines) {
		printf_s("Incorrect input. Please enter a digit.");
		return 1;
	}

	printf_s("Enter strings:\n");
	for (int i = 0; i < number_of_lines; i++) {
		char* string = (char*)malloc((MAX_LINE_INPUT + 1) * sizeof(char));
		string[MAX_LINE_INPUT] = '\0';
		if (i == 0) {
			gets_s(string, MAX_LINE_INPUT);
		}
		if (!fgets(string, MAX_LINE_INPUT, stdin)) {
			free(string);
			list_destroy(List, DESTROY_VALUES);
			printf_s("Something went wrong.");
			return 1;
		}
		list_push_tail(List, string);
		/*if (fgets(string, MAX_LINE_INPUT, stdin)) {
			free(string);
			list_destroy(List, DESTROY_VALUES);
			printf_s("String is too large. Max string size %d", MAX_LINE_INPUT);
			return 1;
		}*/
	}

	printf_s("You entered: ");
	list_of_strings_print(List);
	printf_s("\n");

	printf_s("Select the sort option:\n1) Quick sort.\n2) Bubble sort.\nYour choice: ");
	scanf_s("%d", &input);
	printf_s("\n");

	if (input != 1 && input != 2) {
		printf_s("Please choose 1 or 2.");
		return 1;
	}
	if (input == 1) {
		List = quick_sort_list(List, strcmp_entry, NULL, DESTROY_VALUES);
	}
	else {
		bubble_sort_list(List, strcmp_entry, NULL);
	}

	printf_s("Sorting...\n");

	printf_s("The result is:\n");
	list_of_strings_print(List);
	printf_s("\n");

	list_destroy(List, DESTROY_VALUES);
	return 0;
}

