#include "listimpl.h"
#include "sort.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void bubble_sort_list(list_t* list, list_comparator* comp, void* aux) {
    if (list_is_empty(list)) {
        return;
    }
    bool is_not_sorted = true;
    while (is_not_sorted) {
        is_not_sorted = false;
        struct ListEntry* current_entry = list->head;
        struct ListEntry* next_entry = list->head->next;

        while (next_entry != NULL) {
            if (comp(current_entry, next_entry, aux) > 0) {
                list_swap(current_entry, next_entry);
                is_not_sorted = true;
            }
            current_entry = next_entry;
            next_entry = next_entry->next;
        }
    }
}

list_t* quick_sort_list(
    list_t* list,
    list_comparator* comp,
    void* aux,
    list_destructor_mode_t dmode
) {
    if (list_length(list) <= 1) {
        return list;
    }

    list_t* lt_sample_entries = list_create();
    list_t* eq_sample_entries = list_create();
    list_t* gt_sample_entries = list_create();

    struct ListEntry* sample_entry = list->head;
    for (
        struct ListEntry* current_entry = list_pop_head(list);
        current_entry != NULL;
        current_entry = list_pop_head(list)
        ) {
        int comp_result = comp(current_entry, sample_entry, aux);
        if (comp_result < 0) {
            list_push_tail_entry(lt_sample_entries, current_entry);
        }
        else if (comp_result > 0) {
            list_push_tail_entry(gt_sample_entries, current_entry);
        }
        else {
            list_push_tail_entry(eq_sample_entries, current_entry);
        }
    }
    list->head = NULL;
    list->tail = NULL;
    list_destroy(list, dmode);

    lt_sample_entries = quick_sort_list(lt_sample_entries, comp, aux, dmode);
    gt_sample_entries = quick_sort_list(gt_sample_entries, comp, aux, dmode);

    return list_concat(
        lt_sample_entries,
        list_concat(eq_sample_entries, gt_sample_entries, dmode),
        dmode
    );
}

int my_strcmp(const char* first, const char* second) {
    const unsigned char* a = (const unsigned char*)first;
    const unsigned char* b = (const unsigned char*)second;

    for (; *a != '\0' && *a == *b; a++, b++) {}

    return *a < *b ? -1 : *a > *b;
}

int strcmp_entry(const struct ListEntry* first,
    const struct ListEntry* second,
    void* aux) {

    char* str1 = first->value;
    char* str2 = second->value;

    return my_strcmp(str1, str2);
}
