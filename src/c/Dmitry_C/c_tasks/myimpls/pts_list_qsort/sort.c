#include "list.h"
#include "sort.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct string_holder *string_holder_create(void) {
  struct string_holder *new_holder = malloc(sizeof(*new_holder));
  if (new_holder == NULL) {
    return NULL;
  }
  new_holder->chars = NULL;
  new_holder->elem.next = NULL;
  new_holder->elem.prev = NULL;

  return new_holder;
}

void string_holder_elem_destroy(struct list_elem *elem) {
  struct string_holder *holder = list_entry(elem, struct string_holder, elem);
  string_holder_destroy(holder);
}

void string_literal_holder_elem_destroy(struct list_elem *elem) {
  struct string_holder *holder = list_entry(elem, struct string_holder, elem);
  string_literal_holder_destroy(holder);
}

void string_holder_destroy(struct string_holder *holder) {
  free(holder->chars);
  free(holder);
}

void string_literal_holder_destroy(struct string_holder *holder) {
  free(holder);
}

void bubble_sort_list(struct list * list, list_comp_func* comp, void* aux) {
  if (list_empty(list)) {
    return;
  }
  bool is_not_sorted = true;
  while (is_not_sorted) {
    is_not_sorted = false;
    struct list_elem* current = list_begin(list);
    struct list_elem* next = list_next(current);
    while (next != list_end(list)) {
      if (comp(current, next, aux) > 0) {
        is_not_sorted = true;
        list_swap(current, next);
        next = list_next(current);
      }
      else {
        current = next;
        next = list_next(next);
      }
    }
  }
}

struct list* quick_sort_list(
  struct list * list,
  list_comp_func* comp,
  void* aux
) {
  if (list_size(list) <= 1) {
    return list;
  }
  struct list* lt_elems = list_create();
  struct list* eq_elems = list_create();
  struct list* gt_elems = list_create();

  struct list_elem* sample;
  struct list_elem* current;
  for (
    sample = list_pop_front(list), current = sample;
    !list_empty(list);
    current = list_pop_front(list)
  ) {
    int comp_result = comp(current, sample, aux);
    struct list *destination_list;
    if (comp_result < 0) {
      destination_list = lt_elems;
    }
    else if (comp_result > 0) {
      destination_list = gt_elems;
    }
    else {
      destination_list = eq_elems;
    }
    list_push_front(destination_list, current);
  }
  list->head.next = NULL;
  list->tail.prev = NULL;
  list_destroy(list, NULL);

  lt_elems = quick_sort_list(lt_elems, comp, aux);
  gt_elems = quick_sort_list(gt_elems, comp, aux);

  return list_concat(lt_elems, list_concat(eq_elems, gt_elems));
}


void list_of_string_holders_print(struct list *list) {
  printf("[");
  for (
    struct list_elem *current = list_begin(list);
    current != list_end(list);
    current = list_next(current)
  ) {
    if (current != list_begin(list)) {
      printf(", ");
    }
    struct string_holder *holder = list_entry (current, struct string_holder, elem);
    printf("\"%s\"", holder->chars);
  }
  printf("]");
}

static int my_strcmp(const char* first, const char* second) {
  const unsigned char* a = (const unsigned char*)first;
  const unsigned char* b = (const unsigned char*)second;

  for (; *a != '\0' && *a == *b; a++, b++) {}

  return *a < *b ? -1 : *a > *b;
}

int strcmp_list_elem(const struct list_elem *a,
                     const struct list_elem *b,
                     void* aux) {

  struct string_holder *holder_a = list_entry(a, struct string_holder, elem);
  struct string_holder *holder_b = list_entry(b, struct string_holder, elem);

  char *str1 = holder_a->chars;
  char *str2 = holder_b->chars;

  return my_strcmp(str1, str2);
}
