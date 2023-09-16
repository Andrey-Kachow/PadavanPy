#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "listimpl.h"

/*
  Creates new entry and assigns the given value to it.
*/
static struct ListEntry* create_entry(void* value) {
    struct ListEntry* new_entry = malloc(sizeof * new_entry);
    if (new_entry == NULL) {
        return NULL;
    }
    new_entry->next = NULL;
    new_entry->prev = NULL;
    new_entry->value = value;
    return new_entry;
}

/*
  Returns empty list
*/
list_t* list_create(void) {
    list_t* new_list = malloc(sizeof(list_t));
    if (new_list == NULL) {
        return NULL;
    }
    new_list->head = NULL;
    new_list->tail = NULL;
    return new_list;
}

/*
  Create a list, which is populated with values of the given array.
  @param arr is the array of arbitrary type values
  @param arr_size is the size of the array arr.
*/
list_t* list_create_from_arr(void** arr, int arr_size) {
    list_t* new_list = list_create();
    if (new_list == NULL) {
        return NULL;
    }
    for (int i = 0; i < arr_size; i++) {
        list_push_tail(new_list, arr[i]);
    }
    return new_list;
}

/*
  Clears the content of a list, including values if DESTROY_VALUES mode is used.
  Then frees the list itself.
*/
void list_destroy(list_t* list, list_destructor_mode_t mode) {
    struct ListEntry* current_entry;
    while (!list_is_empty(list)) {
        current_entry = list_pop_head(list);
        if (mode == DESTROY_VALUES) {
            free(current_entry->value);
        }
        free(current_entry);
    }
    free(list);
}

static bool illegal_state(list_t* list) {
    return (list->head != list->tail && (list->head == NULL || list->tail == NULL));
}

static bool populate_empty(list_t* list, void* value) {
    if (illegal_state(list)) {
        return false;
    }
    struct ListEntry* new_entry = create_entry(value);
    if (new_entry == NULL) {
        return false;
    }
    list->head = new_entry;
    list->tail = new_entry;
    return true;
}

bool list_push_tail_entry(list_t *list, struct ListEntry *new_entry) {
  if (list_is_empty(list)) {
    list->head = new_entry;
    list->tail = new_entry;
    new_entry->prev = NULL;
    new_entry->next = NULL;
    return true;
  }
  list->tail->next = new_entry;
  new_entry->prev = list->tail;
  list->tail = new_entry;
  new_entry->next = NULL;
  return true;
}

bool list_push_tail(list_t* list, void* value) {
    if (list_is_empty(list)) {
        return populate_empty(list, value);
    }
    struct ListEntry* new_entry = create_entry(value);
    if (new_entry == NULL) {
        return false;
    }
    return list_push_tail_entry(list, new_entry);
}

bool list_push_head(list_t* list, void* value) {
    if (list_is_empty(list)) {
        return populate_empty(list, value);
    }

    struct ListEntry* new_entry = create_entry(value);
    if (new_entry == NULL) {
        return false;
    }

    list->head->prev = new_entry;
    new_entry->next = list->head;
    list->head = new_entry;
    return true;
}

bool list_add(list_t* list, const int index, void* value) {
    if (index < 0) {
        return false;
    }
    if (list_is_empty(list)) {
        return populate_empty(list, value);
    }

    int count = 0;
    struct ListEntry* current_entry = list->head;
    struct ListEntry* next_entry = list->head->next;

    while (count < index - 1) {
        if (next_entry == NULL) {
            return false;
        }
        current_entry = next_entry;
        next_entry = next_entry->next;
        count++;
    }

    if (next_entry == NULL) {
        return list_push_tail(list, value);
    }

    struct ListEntry* new_entry = create_entry(value);
    if (new_entry == NULL) {
        return false;
    }

    struct ListEntry* left_adjacent = current_entry->prev;
    struct ListEntry* right_adjacent = current_entry;
    left_adjacent->next = new_entry;
    right_adjacent->prev = new_entry;
    new_entry->prev = left_adjacent;
    new_entry->next = right_adjacent;
    return true;
}

bool list_is_empty(list_t* list) {
    return list->head == NULL && list->tail == NULL;
}

struct ListEntry* list_pop_head(list_t* list) {
    if (list_is_empty(list)) {
        return NULL;
    }

    struct ListEntry* entry = list->head;
    list->head = entry->next;

    if (list->head == NULL) {
        list->tail = NULL;
    }
    else {
        list->head->prev = NULL;
    }

    entry->prev = NULL;
    entry->next = NULL;

    return entry;
}

struct ListEntry* list_pop_tail(list_t* list) {
    if (list_is_empty(list)) {
        return NULL;
    }

    struct ListEntry* entry = list->tail;
    list->tail = entry->prev;

    if (list->tail == NULL) {
        list->head = NULL;
    }
    else {
        list->tail->next = NULL;
    }

    entry->prev = NULL;
    entry->next = NULL;

    return entry;
}

struct ListEntry* list_remove(list_t* list, const int index) {
    if (index < 0 || list_is_empty(list)) {
        return NULL;
    }

    int count = 0;
    struct ListEntry* current_entry = list->head;

    while (count < index) {
        if (current_entry == NULL) {
            return NULL;
        }
        current_entry = current_entry->next;
        count++;
    }

    struct ListEntry* left_adjacent = current_entry->prev;
    struct ListEntry* right_adjacent = current_entry->next;
    if (right_adjacent != NULL) {
        right_adjacent->prev = left_adjacent;
    }
    if (left_adjacent != NULL) {
        left_adjacent->next = right_adjacent;
    }
    current_entry->prev = NULL;
    current_entry->next = NULL;
    return current_entry;
}

int list_length(list_t* list) {
    if (list_is_empty(list)) {
        return 0;
    }
    int count = 0;
    struct ListEntry* current_entry = list->head;
    while (current_entry != NULL) {
        current_entry = current_entry->next;
        count++;
    }
    return count;
}

bool list_contains(list_t* list, void* value, list_comparator* comp) {

    struct ListEntry value_holder_entry = (struct ListEntry){ value, NULL, NULL };

    for (struct ListEntry* current_entry = list_start(list);
        has_next(current_entry);
        current_entry = get_next(current_entry)) {

        if (comp(&value_holder_entry, current_entry, NULL) == 0) {
            return true;
        }
    }
    return false;
}

struct ListEntry* list_start(list_t* list) {
    return list->head;
}

bool has_next(struct ListEntry* current) {
    return current->next != NULL;
}

struct ListEntry* get_next(struct ListEntry* current) {
    return current->next;
}

struct ListEntry* list_end(list_t* list) {
    return list->tail;
}

bool has_prev(struct ListEntry* current) {
    return current->prev != NULL;
}

struct ListEntry* get_prev(struct ListEntry* current) {
    return current->prev;
}

void list_swap(struct ListEntry* first, struct ListEntry* second) {
    void* temp = first->value;
    first->value = second->value;
    second->value = temp;
}

void list_swap_indices(list_t* list, int i, int j) {
    int upper = (i < j) ? i : j;
    int count = 0;
    struct ListEntry* current_entry = list->head;
    struct ListEntry* first = NULL;
    struct ListEntry* second = NULL;

    while (first != NULL && second != NULL && count <= upper) {
        if (current_entry == NULL) {
            break;
        }
        if (count == i) {
            first = current_entry;
        }
        if (count == j) {
            second = current_entry;
        }
        current_entry = current_entry->next;
        count++;
    }
    if (first != NULL && second != NULL) {
        list_swap(first, second);
    }
}

bool list_is_sorted(list_t* list, list_comparator* comp, void* aux) {
    if (list_is_empty(list)) {
        return true;
    }
    struct ListEntry* current_entry = list->head;
    struct ListEntry* next_entry = list->head->next;

    while (next_entry != NULL) {
        if (comp(current_entry, next_entry, aux) > 0) {
            return false;
        }
        current_entry = next_entry;
        next_entry = next_entry->next;
    }
    return true;
}

struct ListEntry* list_get_entry(list_t* list, int index) {
    if (index < 0 || list_is_empty(list)) {
        return NULL;
    }

    int count = 0;
    struct ListEntry* current_entry = list->head;

    while (count < index) {
        if (current_entry == NULL) {
            return NULL;
        }
        current_entry = current_entry->next;
        count++;
    }
    return current_entry;
}

void list_of_strings_print(list_t *list) {
  int limit = 7;
  int count = 0;

  printf("[");
  if (!list_is_empty(list)) {

    struct ListEntry *current_entry = list->head;
    while (current_entry != NULL) {

      if (count >= limit) {
        printf("...");
        break;
      }

      char *str = current_entry->value;
      printf("\"%s\"", str);

      current_entry = current_entry->next;
      if (current_entry != NULL) {
        printf(", ");
      }
      count++;
    }
  }
  printf("]");
}

list_t *list_concat(list_t *first, list_t *second, list_destructor_mode_t dmode) {
  enum emptiness_bitmap e_bm =
    ((!list_is_empty(first)) << 1) + !list_is_empty(second);
  switch (e_bm) {
    case BOTH_EMPTY:
    case ONLY_GT_EMPTY:
      second->head = NULL;
      second->tail = NULL;
      list_destroy(second, dmode);
      return first;
    case ONLY_LTE_EMPTY:
      first->head = NULL;
      first->tail = NULL;
      list_destroy(first, dmode);
      return second;
    case NEIGHER_EMPTY:
      first->tail->next = second->head;
      second->head->prev = first->tail;
      first->tail = second->tail;
      second->head = NULL;
      second->tail = NULL;
      list_destroy(second, dmode);
  }
  return first;
}
