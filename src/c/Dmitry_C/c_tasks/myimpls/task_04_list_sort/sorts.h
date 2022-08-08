#ifndef SORTS_H
#define SORTS_H

#include "listimpl.h"

int my_strcmp(const char *,const char *);

int alphabetical_comparator(
  const struct ListEntry *,
  const struct ListEntry *,
  void *
);

void bubble_sort(list_t *);

void quick_sort(list_t *);

void quick_sort_swap(list_t *);

#endif
