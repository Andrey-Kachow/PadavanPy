#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* 2-digit bitmap, where if the flag is set then the corresponding list,
   left or right is not empty */
enum emptiness_bitmap {
  BOTH_EMPTY = 0b00,
  ONLY_LEFT_EMPTY = 0b01,
  ONLY_RIGHT_EMPTY = 0b10,
  NEIGHER_EMPTY = 0b11
};

/* List element. */
struct list_elem {
  struct list_elem *prev;     /* Previous list element. */
  struct list_elem *next;     /* Next list element. */
};

/* List. */
struct list {
  struct list_elem head;      /* List head. */
  struct list_elem tail;      /* List tail. */
};

/* Converts pointer to list element LIST_ELEM into a pointer to
   the structure that LIST_ELEM is embedded inside.  Supply the
   name of the outer structure STRUCT and the member name MEMBER
   of the list element.  See the big comment at the top of the
   file for an example. */
#define list_entry(LIST_ELEM, STRUCT, MEMBER)           \
        ((STRUCT *) ((uint8_t *) &(LIST_ELEM)->next     \
                     - offsetof(STRUCT, MEMBER.next)))


typedef int list_comp_func (const struct list_elem *,
                            const struct list_elem *,
                            void *aux);

typedef void list_elem_destructor (struct list_elem *);

void list_init (struct list *);
struct list *list_create(void);
void list_destroy(struct list *, list_elem_destructor *);
void list_destroy_empty(struct list *);

/* List traversal. */
struct list_elem *list_begin (struct list *);
struct list_elem *list_next (struct list_elem *);
struct list_elem *list_end (struct list *);

struct list_elem *list_head (struct list *);
struct list_elem *list_tail (struct list *);

/* List insertion. */
void list_insert (struct list_elem *, struct list_elem *);
void list_push_front (struct list *, struct list_elem *);
void list_push_back (struct list *, struct list_elem *);

/* List removal. */
struct list_elem *list_remove (struct list_elem *);
struct list_elem *list_pop_front (struct list *);
struct list_elem *list_pop_back (struct list *);

/* List elements. */
struct list_elem *list_front (struct list *);
struct list_elem *list_back (struct list *);

/* List properties. */
size_t list_size (struct list *);
bool list_empty (struct list *);

/* Misc */
void list_swap (struct list_elem *, struct list_elem *);
struct list * list_concat (struct list *, struct list *);
bool list_is_sorted(struct list *list, list_comp_func *, void *aux);

#endif
