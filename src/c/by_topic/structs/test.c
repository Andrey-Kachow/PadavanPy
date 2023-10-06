#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct point {
    int x;
    int y;
};


struct animal {
    int type; // 0 - cat, 1 - dog, 2 - hampster, 3 - bird,
    char name[10];
    int age;
    int is_hungry;
};


struct cat {
    char name[10];
    int age;
    int is_hungry; // 1 - yes 0 - no
};

struct dog {
    char name[10];
    int age;
    int is_hungry;
    char breed[10];
};

struct pet_shop {
    char ardess[40];
    int number_of_cats_to_sale;
    struct cat cats[30];
    struct dog dogs[40];
};


int how_many_cats_are_hungry_in_the_city(struct pet_shop *shops[], int number_of_pet_shops) {

    int hungry_cats_count = 0;

    for (int pet_shop_count = 0; pet_shop_count < number_of_pet_shops; pet_shop_count++) {
        
        struct pet_shop *current = shops[pet_shop_count];
        
        for (int cat_count = 0; cat_count < current->number_of_cats_to_sale; cat_count++) {

            struct cat current_cat = current->cats[cat_count];
            
            if (current_cat.is_hungry) {
                hungry_cats_count++;
            }
        }
    }

    return hungry_cats_count;
}



struct batman {
    char title[10];
    char director_name[15];
    int movie_filmed_date[3];
};


struct batman *get_fitst_batman() {
    return NULL;
}

struct batman *get_next_batman(struct batman *batman) {
    return NULL;
}

int no_more_batmans(struct batman *batman) {
    return 1;
}



int main(void) {

    struct point p = { 10, 20 };

    p.x += 2;

    int Xs[4] = {1, 2, 3, 4};
    int Ys[4] = {4, 5, 6, 7};

    struct point points[4] = {
        {1, 4},
        {4, 0},
        {3, 6},
        {5, 9}
    };
    

    // numbers = {1, 2, 3, 4, .... 8}
    
    for (int number = 1; number < 8; number++) {

    }

    // {2, 4, 6}

    for (int even_number = 2; even_number < 7; even_number += 2) {

    }

        
    for (struct batman *current_batman_it = get_fitst_batman();
            !no_more_batmans(current_batman_it);
            current_batman_it = get_next_batman(current_batman_it)
    ) {
        // process batman
    }
    
}



