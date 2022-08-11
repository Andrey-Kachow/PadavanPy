#include <stdlib.h>
#include "list.h"

/* Returns true if ELEM is a head, false otherwise. */
static inline bool is_head (struct list_elem *elem) {
  return elem != NULL && elem->prev == NULL && elem->next != NULL;
}

/* Returns true if ELEM is an interior element,
   false otherwise. */
static inline bool is_interior (struct list_elem *elem) {
  return elem != NULL && elem->prev != NULL && elem->next != NULL;
}

/* Returns true if ELEM is a tail, false otherwise. */
static inline bool is_tail (struct list_elem *elem) {
  return elem != NULL && elem->prev != NULL && elem->next == NULL;
}

/* Initializes LIST as an empty list. */
void
list_init (struct list *list) {
  list->head.prev = NULL;
  list->head.next = &list->tail;
  list->tail.prev = &list->head;
  list->tail.next = NULL;
}

struct list *list_create(void) {
  struct list *new_list = malloc(sizeof(*new_list));
  if (new_list == NULL) {
    return NULL;
  }
  list_init(new_list);
  return new_list;
}

void list_destroy(struct list *list, list_elem_destructor *destructor) {
  while (!list_empty(list) && destructor != NULL) {
    destructor(list_pop_front(list));
  }
  free(list);
}

/* Returns the beginning of LIST.  */
struct list_elem * list_begin (struct list *list) {
  return list->head.next;
}

/* Returns the element after ELEM in its list.  If ELEM is the
   last element in its list, returns the list tail.  Results are
   undefined if ELEM is itself a list tail. */
struct list_elem * list_next (struct list_elem *elem) {
  return elem->next;
}

/* Returns LIST's tail.

   list_end() is often used in iterating through a list from
   front to back.  See the big comment at the top of list.h for
   an example. */
struct list_elem * list_end (struct list *list) {
  return &list->tail;
}

/* Return's LIST's head. */
struct list_elem * list_head (struct list *list) {
  return &list->head;
}

/* Return's LIST's tail. */
struct list_elem * list_tail (struct list *list) {
  return &list->tail;
}

/* Inserts ELEM just before BEFORE, which may be either an
   interior element or a tail.  The latter case is equivalent to
   list_push_back(). Undefined behavior if ELEM is already in the list. */
void list_insert (struct list_elem *before, struct list_elem *elem) {
  elem->prev = before->prev;
  elem->next = before;
  before->prev->next = elem;
  before->prev = elem;
}

/* Inserts ELEM at the beginning of LIST, so that it becomes the
   front in LIST. */
void list_push_front (struct list *list, struct list_elem *elem) {
  list_insert (list_begin (list), elem);
}

/* Inserts ELEM at the end of LIST, so that it becomes the
   back in LIST. */
void list_push_back (struct list *list, struct list_elem *elem) {
  list_insert (list_end (list), elem);
}

struct list_elem * list_remove (struct list_elem *elem) {
  elem->prev->next = elem->next;
  elem->next->prev = elem->prev;
  return elem->next;
}

/* Removes the front element from LIST and returns it.
   Undefined behavior if LIST is empty before removal. */
struct list_elem * list_pop_front (struct list *list) {
  struct list_elem *front = list_front (list);
  list_remove (front);
  return front;
}

/* Removes the back element from LIST and returns it.
   Undefined behavior if LIST is empty before removal. */
struct list_elem * list_pop_back (struct list *list) {
  struct list_elem *back = list_back (list);
  list_remove (back);
  return back;
}

/* Returns the front element in LIST.
   Undefined behavior if LIST is empty. */
struct list_elem * list_front (struct list *list) {
  return list->head.next;
}

/* Returns the back element in LIST.
   Undefined behavior if LIST is empty. */
struct list_elem * list_back (struct list *list) {
  return list->tail.prev;
}

/* Returns the number of elements in LIST.
   Runs in O(n) in the number of elements. */
size_t list_size (struct list *list) {
  size_t count = 0;
  struct list_elem *e = list_begin(list);
  while (e != list_end(list)) {
    e = list_next(e);
    count++;
  }
  return count;
}

/* Returns true if LIST is empty, false otherwise. */
bool list_empty (struct list *list) {
  return list_begin (list) == list_end (list);
}

/* Swaps the `struct list_elem *'s that A and B point to. */
void list_swap (struct list_elem *left, struct list_elem *right) {
  list_remove(left);
  list_insert(right->next, left);
}

struct list * list_concat(struct list * first, struct list * second) {
  printf("");
  list_of_string_holders_print(first);
  printf(" + ");
  list_of_string_holders_print(second);
  printf(" = ");
  enum emptiness_bitmap e_bm = ((!list_empty(first)) << 1) + !list_empty(second);
  switch (e_bm) {
    case BOTH_EMPTY:
    case ONLY_RIGHT_EMPTY:
      list_destroy(second, NULL);
      list_of_string_holders_print(first);
      printf("\n");
      return first;
    case ONLY_LEFT_EMPTY:
      list_destroy(first, NULL);
      list_of_string_holders_print(second);
      printf("\n");
      return second;
    case NEIGHER_EMPTY:
      list_back(first)->next = list_front(second);
      list_front(second)->prev = list_back(first);
      first->tail.prev = second->tail.prev;
      list_init(second);
      list_destroy(second, NULL);
  }
  list_of_string_holders_print(first);
  printf("\n");
  return first;
}

bool list_is_sorted(struct list *list, list_comp_func *comp, void *aux) {
  if (list_empty(list)) {
    return true;
  }
  struct list_elem* current = list_begin(list);
  struct list_elem* next = list_next(current);
  for (; next != list_end(list); current = next, next = list_next(next)) {
    if (comp(current, next, aux) > 0) {
      return false;
    }
  }
  return true;
}
