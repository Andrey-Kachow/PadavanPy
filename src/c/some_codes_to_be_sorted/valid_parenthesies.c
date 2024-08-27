bool isClosing(char c) {
    return c == '}'
        || c == ']'
        || c == ')';
}

bool matches(char a, char b) {
    return a == '(' && b == ')'
        || a == '[' && b == ']'
        || a == '{' && b == '}';
}

struct stack_elem {
    char *character;
    struct stack_elem *prev;
};

typedef struct stack_elem stack_elem_t;

typedef struct {
    stack_elem_t *top;
} stack_t;

stack_t *stack_allocate(void) {
    stack_t *stack = malloc(sizeof(stack_t));
    if (stack == NULL) {
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

bool stack_push(stack_t *stack, char *character) {
    stack_elem_t *elem = malloc(sizeof(stack_elem_t));
    if (elem == NULL) {
        return false;
    }
    elem->character = character;
    elem->prev = stack->top;
    stack->top = elem;
    return true;
}

char *stack_pop(stack_t *stack) {
    stack_elem_t *popped = stack->top;
    if (popped == NULL) {
        return NULL;
    }
    stack->top = popped->prev;
    char *res = popped->character;
    free(popped);
    return res;
}

bool stack_is_empty(stack_t *stack) {
    return stack->top == NULL;
}

bool isValid(char *s){
    stack_t *stack = stack_allocate();
    if (stack == NULL) {
        return false;
    }
    for (int i = 0; s[i] != '\0'; i++) {
        if (isClosing(s[i])) {
            char *prev = stack_pop(stack);
            if (
                prev == NULL || 
                !matches(*prev, s[i])
            ) {
                return false;
            }
        }
        else if (!stack_push(stack, s + i)) {
            return false;
        }
    }
    return stack_is_empty(stack);
}