#include <stdio.h>
#include <stdlib.h>
#include "test_list.h"
#include "list.h"
#include "sort.h"

#define MAX_LINE_INPUT 256

void zero_new_line(const char *string) {
	unsigned char *cur_ch = (unsigned char *) string;
	int count = 0;
	while (*cur_ch != '\n' && count < MAX_LINE_INPUT) {
		cur_ch++;
		count++;
	}
	if (*cur_ch == '\n') {
		*cur_ch = '\0';
	}
}

int main() {
	int input = 0;
	int number_of_lines = 0;

	printf("Select the program option:\n1) Test start.\n2) Default start.\nYour choice: ");
	scanf("%d", &input);
	printf("\n");

	if (input != 1 && input != 2) {
		printf("Please choose 1 or 2.");
		return 1;
	}
	if (input == 1) {
		test();
		return 0;
	}

	struct list *List = list_create();
	printf("How many lines do you want to enter?\nEnter: ");
	scanf("%d", &number_of_lines);
	if (!number_of_lines) {
		printf("Incorrect input. Please enter a digit.");
		return 1;
	}

	printf("Enter strings:\n");
	for (int i = 0; i < number_of_lines; i++) {

		struct string_holder *holder = string_holder_create();
		char* string = (char*)malloc((MAX_LINE_INPUT + 1) * sizeof(char));
		holder->chars = string;

		string[MAX_LINE_INPUT] = '\0';
		if (i == 0) {
			fgets(string, MAX_LINE_INPUT, stdin);
		}
		if (!fgets(string, MAX_LINE_INPUT, stdin)) {
			string_holder_destroy(holder);
			list_destroy(List, string_holder_elem_destroy);
			printf("Something went wrong.");
			return 1;
		}
		zero_new_line(string);
		list_push_back(List, &holder->elem);
		/*if (fgets(string, MAX_LINE_INPUT, stdin)) {
			free(string);
			list_destroy(List, DESTROY_VALUES);
			printf("String is too large. Max string size %d", MAX_LINE_INPUT);
			return 1;
		}*/
	}

	printf("You entered: ");
	list_of_string_holders_print(List);
	printf("\n");

	printf("Select the sort option:\n1) Quick sort.\n2) Bubble sort.\nYour choice: ");
	scanf("%d", &input);
	printf("\n");

	if (input != 1 && input != 2) {
		printf("Please choose 1 or 2.");
		return 1;
	}
	if (input == 1) {
		List = quick_sort_list(List, strcmp_list_elem, NULL);
	}
	else {
		bubble_sort_list(List, strcmp_list_elem, NULL);
	}

	printf("Sorting...\n");

	printf("The result is:\n");
	list_of_string_holders_print(List);
	printf("\n");

	list_destroy(List, string_holder_elem_destroy);
	return 0;
}
