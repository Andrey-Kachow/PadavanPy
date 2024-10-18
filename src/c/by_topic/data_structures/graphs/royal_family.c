#include <stdio.h>
#include <stdbool.h>

/*
 * Romanov Dynasty - Male Descendants of Emperor Paul I (Grandchildren Included)
 *                   (Generated with Chat GPT)
 * 
 * Emperor Paul I (1754–1801) married Sophie Dorothea of Württemberg (Maria Feodorovna)
 * ├── 1. Alexander I (1777–1825), Emperor of Russia
 * │      - Married Louise of Baden (Elisabeth Alexeievna)
 * │      - No male issue
 * │
 * ├── 2. Konstantin Pavlovich (1779–1831), Grand Duke of Russia
 * │      - Married twice, no legitimate male issue
 * │
 * ├── 3. Nicholas I (1796–1855), Emperor of Russia
 * │      - Married Charlotte of Prussia (Alexandra Feodorovna)
 * │      - Male Issue:
 * │        ├── 1. Alexander II (1818–1881), Emperor of Russia
 * │        │      - Married Marie of Hesse (Maria Alexandrovna)
 * │        │      - Male Issue:
 * │        │        ├── Alexander III (1845–1894), Emperor of Russia
 * │        │        │      - Married Dagmar of Denmark (Maria Feodorovna)
 * │        │        │
 * │        │        └── Grand Duke Vladimir Alexandrovich (1847–1909)
 * │        │              - Married Duchess Marie of Mecklenburg-Schwerin
 * │        │
 * │        ├── Grand Duke Konstantin Nikolayevich (1827–1892)
 * │        │      - Married Alexandra of Saxe-Altenburg
 * │        │
 * │        ├── Grand Duke Nicholas Nikolaevich (1831–1891)
 * │        │      - Married Alexandra of Oldenburg
 * │        │
 * │        └── Grand Duke Michael Nikolaevich (1832–1909)
 * │              - Married Princess Cecilie of Baden
 * │
 * ├── 4. Michael Pavlovich (1798–1849), Grand Duke of Russia
 * │      - Married Charlotte of Württemberg (Elena Pavlovna)
 * │      - No male issue
 * │
 * └── 5. Grand Duke Konstantin Pavlovich (1827–1892)
 *        - Married Alexandra of Saxe-Altenburg
 *        - Male Issue:
 *        ├── Grand Duke Nicholas Konstantinovich (1850–1918)
 *        ├── Grand Duke Konstantin Konstantinovich (1858–1915)
 *        ├── Grand Duke Dmitry Konstantinovich (1860–1919)
 *        └── Grand Duke Vyacheslav Konstantinovich (1862–1879)
 */
struct stack {
    int data[6];
    int top;
};


struct person {
    char name[40];
    int year_of_birth;
    int year_of_death;
};

struct family_graph {
    struct person people[16];
    int relations[16][2];
};

struct stack * stack_create() {
    struct stack * result = malloc(sizeof(struct stack));
    if (result == NULL) {
        return NULL;
    }
    result->top = -1;
    return result;
}

int stack_peek(struct stack * stack) {
    if (stack->top == -1) {
        printf("Empty stack peek\n");
        return -1;
    }
    return stack->data[stack->top];
}

void stack_pop(struct stack * stack) {
    if (stack->top == -1) {
        printf("Empty stack pop\n");
        return ;
    }
    stack->top -= 1;
}

void stack_push(struct stack * stack, int new_number) {
    if (stack->top >= 6) {
        printf("Stack over flow\n");
        return ;
    }
    stack->top += 1;
    stack->data[stack->top] = new_number;
}

struct family_graph romanov_family = {
    { // people
        {"Emperor Paul I", 1754, 1801},
        {"Alexander I", 1777, 1825},
        {"Konstantin Pavlovich", 1779, 1831},
        {"Nicholas I", 1796, 1855},
        {"Alexander II", 1818, 1881},
        {"Alexander III", 1845, 1894},
        {"Grand Duke Vladimir Alexandrovich", 1847, 1909},
        {"Grand Duke Konstantin Nikolayevich", 1827, 1892},
        {"Grand Duke Nicholas Nikolaevich", 1831, 1891},
        {"Grand Duke Michael Nikolaevich", 1832, 1909},
        {"Michael Pavlovich", 1798, 1849},
        {"Grand Duke Konstantin Pavlovich", 1827, 1892},
        {"Grand Duke Nicholas Konstantinovich", 1850, 1918},
        {"Grand Duke Konstantin Konstantinovich", 1858, 1915},
        {"Grand Duke Dmitry Konstantinovich", 1860, 1919},
        {"Grand Duke Vyacheslav Konstantinovich", 1862, 1879},
    },
    { // relations
        {0, 1},
        {0, 2},
        {0, 3},
        //
            {3, 4},
                {4, 5},
                {4, 6},
            {3, 7},
            {3, 8},
            {3, 9},
        //
        {0, 10},
        {0, 11},
        // Konstantin Pavlovich
            {11, 12},
            {11, 13},
            {11, 14},
            {11, 15}
        //
    }
};

int * children(int parent, int * size_out) {
    int children_count = 0;
    for (int i=0; i!=15; i++) {
        if (romanov_family.relations[i][0] == parent) {
            children_count += 1;
            // printf("%s\n", romanov_family.people[romanov_family.relations[i][1]].name); // 
        }
    }
    *size_out = children_count;
    int * children_array = malloc(sizeof(int) * children_count);
    int child_position = 0;
    for (int j=0; j!=15; j++) {
        if (romanov_family.relations[j][0] == parent) {
            children_array[child_position] = romanov_family.relations[j][1];
            // printf("%s\n", romanov_family.people[romanov_family.relations[j][1]].name);
            child_position += 1;
        }
    }
    return children_array;
}

void dfs(struct stack * journal) {
    int child_count = -1;
    int current_romanov = stack_peek(journal);
    int * current_children = children(current_romanov, &child_count);

    printf("%s\n", romanov_family.people[current_romanov].name);
    for (int i=0; i != child_count; i++) {
        int next_child = current_children[i];
        stack_push(journal, next_child);
        dfs(journal);
        stack_pop(journal);
    }
}

void dfs_2(int current_romanov) {
    int child_count = -1;
    int * current_children = children(current_romanov, &child_count);

    printf("%s\n", romanov_family.people[current_romanov].name);
    for (int i=0; i != child_count; i++) {
        int next_child = current_children[i];
        dfs_2(next_child);
    }
}

struct queue {
    int start;
    int current_size;
    int * array;
    int size_array;
};

void queue_add(struct queue * this_queue, int new_element) {
    int end = this_queue->current_size + this_queue->start;
    end %= this_queue->size_array;
    this_queue->array[end] = new_element;
    this_queue->current_size += 1;
}

int queue_poll(struct queue * this_queue) {
    if (this_queue->current_size == 0) {
        printf("ERROR: empty queue poll\n");
        return -1;
    }
    int result = this_queue->array[this_queue->start];
    this_queue->start += 1;
    this_queue->start %= this_queue->size_array;
    this_queue->current_size -= 1;
    return result;
}


void queue_print(struct queue * this_queue) {
    printf("{ ");
    for (int i = 0; i < this_queue->current_size; i++) {
        int position = this_queue->start + i;
        position %= this_queue->size_array;
        printf("%d, ", this_queue->array[position]);
    }
    printf(" }\n");
}

bool queue_empty(struct queue * this_queue) {
    return this_queue->current_size == 0;
}

struct queue * queue_create(int size_array) {
    struct queue * result = malloc(sizeof(struct queue));
    if (result == NULL) {
        return NULL;
    }

    result->current_size = 0;
    result->start = -1;
    result->array = malloc(sizeof(int) * size_array);
    if (result->array == NULL) {
        free(result);
        return NULL;
    }
    result->size_array = size_array;
    return result;
}

void bfs() {
    int first = 0;
    struct queue * romanov_queue = queue_create(16);
    queue_add(romanov_queue, first);
    while (!queue_empty(romanov_queue)) {
        int current_romanov = queue_poll(romanov_queue);
        printf("%s\n", romanov_family.people[current_romanov].name);
        int children_size = 0;
        int * romanov_children = children(current_romanov, &children_size);
        for (int i=0; i != children_size; i++) {
            printf("%d\n", i);
            int child = romanov_children[i];
            queue_add(romanov_queue, child);
        }
    }
}

int main() {
    // struct stack * journal = stack_create();
    // int start_person = 0;
    // stack_push(journal, start_person);
    // // dfs(journal);

    // int size = -1;
    // int * paul_children = children(4, &size);
    // for (int i=0; i!=size; i++) {
    //     printf("%d\n", paul_children[i]);
    // }

    // free(journal);

    // dfs_2(0);

    bfs();
    struct queue * q = queue_create(3);
    queue_add(q, 1);
    queue_print(q);

    queue_add(q, 2);
    queue_print(q);

    queue_add(q, 3);
    queue_print(q);

    printf("%d\n", queue_poll(q));
    queue_print(q);

    queue_add(q, 4);
    queue_print(q);
    
    return 0;
}