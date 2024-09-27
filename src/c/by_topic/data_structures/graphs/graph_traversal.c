#include <stdio.h>
#include <stdbool.h>

struct stack {
    int data[7];
    int top;
};

bool matrix[7][7] = {
//   A  Б  В  Г  Д  Е  Ж
    {0, 1, 1, 0, 1, 1, 0}, // А 
    {0, 0, 1, 1, 0, 0, 0}, // Б
    {0, 0, 0, 0, 1, 0, 0}, // В
    {1, 0, 0, 0, 1, 0, 1}, // Г
    {0, 0, 0, 0, 0, 0, 1}, // Д
    {0, 0, 0, 0, 0, 0, 1}, // Е
    {0, 0, 0, 0, 0, 0, 0}  // Ж
};

struct stack * stack_create() {
    struct stack * result = malloc(sizeof(struct stack));
    if (result == NULL) {
        return NULL;
    }
    result->top = -1;
    return result;
}

int stack_peek(struct stack * stack) {
    if (stack->top == -1) {
        printf("Empty stack peek\n");
        return -1;
    }
    return stack->data[stack->top];
}

void stack_pop(struct stack * stack) {
    if (stack->top == -1) {
        printf("Empty stack pop\n");
        return ;
    }
    stack->top -= 1;
}

void stack_push(struct stack * stack, int new_number) {
    if (stack->top >= 6) {
        printf("Stack over flow\n");
        return ;
    }
    stack->top += 1;
    stack->data[stack->top] = new_number;
}

void print_journal(struct stack * journal) {
    for (int i = 0; i <= journal->top; i++) {
        printf("%d", journal->data[i]);
    }
    printf("\n");
}

bool stack_contains(struct stack * stack, int item) {
    for (int i=0; i <= stack->top; i++) {
        if (stack->data[i] == item) {
            return true;
        }
    }
    return false;
}

// Depth First Search
void dfs(struct stack * journal, int end_city) {
    int current_city = stack_peek(journal);
    if (current_city == end_city) {
        print_journal(journal);
    }
    for (int next_city = 0; next_city < 7; next_city ++) {
        if (matrix[current_city][next_city] == 1 && !stack_contains(journal, next_city)) {
            stack_push(journal, next_city);
            dfs(journal, end_city);
            stack_pop(journal);
        }
    }
}

int main() {

    struct stack * journal = stack_create();
    int start_city = 0;
    int end_city = 6;

    stack_push(journal, start_city);
    dfs(journal, end_city);

    // stack_pop(journal);
    // stack_pop(journal);
    // stack_pop(journal);
    // stack_pop(journal);
    // printf("%d", stack_peek(journal));

    // stack_push(journal, 10);
    // printf("%d", stack_peek(journal));

    // stack_push(journal, 20);
    // printf("%d", stack_peek(journal));

    // stack_push(journal, 30);
    // printf("%d", stack_peek(journal));

    // stack_push(journal, 40);
    // printf("%d", stack_peek(journal));

    // stack_push(journal, 50);
    // printf("%d", stack_peek(journal));

    // stack_push(journal, 60);
    // printf("%d", stack_peek(journal));

    // stack_push(journal, 70);
    // printf("%d", stack_peek(journal));

    // stack_push(journal, 80);
    // printf("%d", stack_peek(journal));

    return 0;
}