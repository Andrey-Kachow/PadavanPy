struct List_elem {
    struct Asteroid * asteroid;
    struct List_elem * next;
};

struct List { 
    struct List_elem * head;
    int size;
};

struct List * List_create();

struct List_elem * list_elem_create(struct Asteroid * asteroid);

void List_append(struct List * list, struct Asteroid * asteroid);

