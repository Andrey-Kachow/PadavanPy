#include <stdio.h>
#include <time.h>
#include <windows.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct List {
    struct ListNode* head;
};

void push_back(struct List* l1, int num) {
    struct ListNode * current = l1->head;
    if (current == NULL) {
        l1->head = malloc(sizeof(struct ListNode));
        l1->head->val = num;
        l1->head->next = NULL;
        return;
    }
    while (current != NULL) {
        if (current->next == NULL) {
            current->next = malloc(sizeof(struct ListNode));
            current->next->val = num;
            current->next->next = NULL;
            break;
        } else {
            current = current->next;
        }
    }
}

void print_list(struct List* list) {
    printf("[");
    struct ListNode * current = list->head;
    while (current != NULL) {
        if (current != list->head) {
            printf(", ");
        }
        printf("%d", current->val);
        current = current->next;
    }
    printf("]\n");
}

struct List * new_list() {
    struct List* result = malloc(sizeof(struct List));
    if (result == NULL) {
        return NULL;
    } 
    result->head = NULL;
    return result;
}

void list_add_x(struct List* l1, int x) {
    int count = 0;
    while (count != x) {
        push_back(l1, count);
        count += 1;
    }
}

void list_free(struct List* l1) {
    struct ListNode * current = l1->head;
    while (current != NULL) {
        struct ListNode * temp = current;
        current = current->next;
        free(temp);
    }
    free(l1);
}

void some_function(int n) {
    for (int i = 0; i < n; i++) {
        for (volatile long j = 0; j < 1000000; j++); // Simulate work
    }
}

int main() {

    
    // Clock time CPU
    for (int i = 0, n = 1; i < 20; i++, n *= 2) {
        int number_of_elements = 100 * n;
        struct List *list = new_list();
        clock_t start = clock();
        list_add_x(list, number_of_elements);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; // Convert to seconds
        list_free(list);
        printf("CPU time taken: %f seconds. \t Elements added: %d\n", time_taken, number_of_elements);
    }


    return 0;
}