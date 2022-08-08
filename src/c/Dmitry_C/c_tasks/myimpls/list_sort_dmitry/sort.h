#ifndef SORTS_H
#define SORTS_H

#include "listimpl.h"

void bubble_sort_list(list_t*, list_comparator*, void*);
list_t * quick_sort_list(list_t*, list_comparator*, void*, list_destructor_mode_t);
int strcmp_entry(const struct ListEntry*, const struct ListEntry*, void*);

#endif
