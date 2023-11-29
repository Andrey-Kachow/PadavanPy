#include <stdio.h>
#include <stdlib.h>

//
// Associative arrays
char names[4][10]      = {"Ivan",   "Sergey", "Petr",       "Alexey"};
char surnames[4][10]   = {"Ivanov", "Petrov", "Nikolayev", "Drozdov"};
char total_grades[4][10] = {4, 5, 3, 5};

//
// Structs
struct Student {
    char name[10];
    char surname[10];
    int total_grade;
};
struct Student ivan_ivanov = {"Ivan", "Ivanov", 4};

void struct_demo_func() {
    //
    // local variable declaration
    struct Student student;
    strcpy(student.name, "Alexander");
    strcpy(student.surname, "Ivanov");
    student.total_grade = 5;
    printf("student is %s %s has grade %d\n", student.name, student.surname, student.total_grade);
}

//////////////////////////////////////////////////////////////
///////////// typedefs and dynamic memory ////////////////////
//////////////////////////////////////////////////////////////

typedef struct {
    char * name;
    char * surname;
    char * alter_ego;
} superhero_t;

//
// Constructor function
superhero_t * superhero_create(char *name, char *surname, char *alter_ego) {

    superhero_t *new_superhero = malloc(sizeof(superhero_t));

    if (new_superhero == NULL) {
        return NULL;
    }

    new_superhero->name = name;
    new_superhero->surname = surname;
    new_superhero->alter_ego = alter_ego;

    return new_superhero;
}

typedef struct {
    float width;
    float height;
    float x;
    float y;
} rectangle_t;

float rectangle_area(rectangle_t *rect) {
    return rect->width * rect->height;
}

int main() {
    
    printf("%s %s\n", names[0], surnames[0]);
    printf("%s %s\n", ivan_ivanov.name, ivan_ivanov.surname);

    struct_demo_func();

    //
    // Allocating a struct in a dynamic memory (in a heap)
    superhero_t * spiderman = superhero_create("Peter", "Parker", "Spiderman");

    //
    // Usage of struct pointer
    printf("%s is actually %s %s\n", spiderman->alter_ego, spiderman->name, spiderman->surname);

    //
    // Memory cleanup
    free(spiderman);


    rectangle_t rect = {200, 100, 0, 0};
    printf("Rectangle has %.1f width, %.1f height, %.1f area.\n", rect.width, rect.height, rectangle_area(&rect));
    return 0;
}