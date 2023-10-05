#include <stdio.h>
#include <stdbool.h>

struct point {
    int x;
    int y;
};


struct animal {
    int type; // 0 - cat, 1 - dog, 2 - hampster, 3 - bird,
    char name[10];
    int age;
    int is_hungry;
}


struct cat {
    char name[10];
    int age;
    int is_hungry; // 1 - yes 0 - no
};

struct pet_shop {
    char ardess[40];
    int number_of_cats_to_sale;
    struct cat cats[30];
    struct dog dogs[40];
};


int how_many_cats_are_hungry_in_the_city(struct pet_shop shops[], int number_of_pet_shops) {

    int hungry_cats_count = 0;

    for (int pet_shop_count = 0; pet_shop_count < number_of_pet_shops; pet_shop_count++) {
        
        struct pet_shop current = shops[pet_shop_count];
        
        for (int cat_count = 0; cat_count < current.number_of_cats_to_sale; cat_count++) {

            struct cat current_cat = current.cats[cat_count];
            
            if (cat.is_hungry) {
                hungry_cats_count++;
            }
        }
    }

    return hungry_cats_count;
}



int main(void) {

    int expected = 5;
    int actual_cats = how_many_cats_are_hungry_in_the_city(...);

    if (expected != actual_cats) {
        fail();
    }
    


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

    for (int even_number = 2; even_number < 7; number += 2) {

    }

        
    for (struct batman current_batman_it = get_fitst_batman();
            !no_more_batmans(current_batman_it);
            current_batman_it = get_next_batman(current_batman_it)
    ) {
        // process batman
    }
    
}



