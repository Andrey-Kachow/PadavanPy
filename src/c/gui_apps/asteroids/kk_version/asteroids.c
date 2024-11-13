#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

struct List_elem {
    struct Asteroid * asteroid;
    struct List_elem * next;
};

struct List { 
    struct List_elem * head;
    int size;
};

struct List * List_create() {
    struct List * result = malloc(sizeof(struct List));
    if (result == NULL) {
        return NULL;
    } 
    result->head = NULL;
    result->size = NULL;
    return result;
}

struct List_elem * list_elem_create(struct Asteroid * asteroid) {
    struct List_elem * result = malloc(sizeof(struct List_elem));
    if (result == NULL) {
        return NULL;
    } 
    result->asteroid = asteroid;
    result->next = NULL;
    return result;
}

void List_append(struct List * list, struct Asteroid * asteroid) {
    struct List_elem * new_elem = list_elem_create(asteroid);
    new_elem->next = list->head;
    list->head = new_elem;
}

