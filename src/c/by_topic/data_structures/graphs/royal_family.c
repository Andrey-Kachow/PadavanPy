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

int * children(int parent) {
    int children_count = 0;
    int i = 0;
    while (i != 16) {
        if (romanov_family.relations[i][0] == parent) {
            children_count += 1;
            printf("%s\n", romanov_family.people[romanov_family.relations[i][1]].name); // 
        }
        i += 1;
    }
    int * children_array = malloc(sizeof(int) * children_count);
    int child_position = 0;
    for (int j=0; j!=16; j++) {
        if (romanov_family.relations[i][0] == parent) {
            children_array[child_position] = romanov_family.relations[i][1];
            // printf("%s\n", romanov_family.people[romanov_family.relations[i][1]].name);
            child_position += 1;
        }
    }
    return children_array;
}

int main() {
    struct stack * journal = stack_create();
    int start_person = 0;

    children(0);
    return 0;
}