#ifndef LISTIMPL_H
#define LISTIMPL_H
#include <stdbool.h>

/*
  Macro for obtaining value from the struct ListEntry *ENTRY
  and casting it to proper type

  Usage for a lit of integers:

  int value = list_value(int, entry);
*/
#define list_value(ENTRY_TYPE,ENTRY) (*((ENTRY_TYPE*)((ENTRY)->value)))

struct ListEntry {
    void* value;
    struct ListEntry* next;
    struct ListEntry* prev;
};

typedef struct {
    struct ListEntry* head;
    struct ListEntry* tail;
} list_t;

/*
  Enum which determines the mode of destroying list items.
  <> DESTROY_VALUES mode should be used, when the list values are allocated
     in the dynamic memory (heap) and needs to be freed.
  <> IGNORE_VALUES mode should be used when the list values are either
     stack values or global variables.
*/
typedef enum {
    DESTROY_VALUES,
    IGNORE_VALUES
} list_destructor_mode_t;

/* 2-digit bitmap, where if the flag is set then the corresponding list is not empty */
enum emptiness_bitmap {
  BOTH_EMPTY     = 0b00,
  ONLY_LTE_EMPTY = 0b01,
  ONLY_GT_EMPTY  = 0b10,
  NEIGHER_EMPTY  = 0b11
};

/*
  The type signature for the function which compares two elements of a list
  @params first and second are pointers to the list elements
  @param aux is a pointer to a structure, which holds auxiluary arguments or context
  @returns the integer value, which works in the following way:
    first less than second    --> returns negative value,
    first equals to second    --> returns zero,
    first greater than second --> returns positive value
*/
typedef int list_comparator(const struct ListEntry* first,
    const struct ListEntry* second,
    void* aux);

list_t* list_create(void);
list_t* list_create_from_arr(void** arr, int arr_size);
void list_destroy(list_t*, list_destructor_mode_t);

/* Adding element to list */
bool list_push_tail(list_t*, void* value);
bool list_push_tail_entry(list_t *list, struct ListEntry *new_entry);
bool list_push_head(list_t*, void* new_entry);
bool list_add(list_t*, const int index, void* value);

/* Removing element from list */
struct ListEntry* list_pop_head(list_t*);
struct ListEntry* list_pop_tail(list_t*);
struct ListEntry* list_remove(list_t*, const int index);

/* Utilities */
bool list_is_empty(list_t*);
int list_length(list_t*);
bool list_contains(list_t*, void* value, list_comparator*);
struct ListEntry* list_get_entry(list_t* list, int index);
list_t *list_concat(list_t *first, list_t *second, list_destructor_mode_t dmode);


/* Iteration */
/*
  Usages for some list_t *l:

  // head to tail walkthrough
  for (struct ListEntry *cur = list_start(l); has_next(cur); get_next(cur)) {
    // code
  }
  // tail to head walkthrough
  for (struct ListEntry *cur = list_end(l); has_prev(cur); get_prev(cur)) {
    // code
  }
*/
struct ListEntry* list_start(list_t*);
bool has_next(struct ListEntry* current);
struct ListEntry* get_next(struct ListEntry* current);
struct ListEntry* list_end(list_t*);
bool has_prev(struct ListEntry* current);
struct ListEntry* get_prev(struct ListEntry* current);

/* Swapping  and sorting */
void list_swap(struct ListEntry*, struct ListEntry*);
void list_swap_indices(list_t*, int, int);
bool list_is_sorted(list_t*, list_comparator*, void *aux);

#endif
