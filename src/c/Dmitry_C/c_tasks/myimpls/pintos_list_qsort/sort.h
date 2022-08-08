#ifndef SORTS_H
#define SORTS_H

#include "list.h"

struct string_holder {
  char *chars;
  struct list_elem elem;
};

struct string_holder *string_holder_create(void);
void string_holder_destroy(struct string_holder *holder);
void string_literal_holder_destroy(struct string_holder *holder);
void string_holder_elem_destroy(struct list_elem *elem);
void string_literal_holder_elem_destroy(struct list_elem *elem);

void bubble_sort_list(struct list * list, list_comp_func* comp, void* aux);
struct list * quick_sort_list(struct list * list, list_comp_func* comp, void* aux);

void list_of_string_holders_print(struct list *list);

int strcmp_list_elem(const struct list_elem*,const struct list_elem*, void* aux);

#endif
