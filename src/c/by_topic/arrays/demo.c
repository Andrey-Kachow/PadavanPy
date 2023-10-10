#include <stdio.h>

int find_food_for_hungriest_dog_2(int dog1, int dog2) {
   return 0;
}


int find_food_for_hungriest_dog_3(int dog1, int dog2, int dog3) {
   return 0;
}


int find_food_for_hungriest_dog_4(int dog1, int dog2, int dog3, int dog4) {
   return 0;
}


int find_food_for_hungriest_dog_5(int dog1, int dog2, int dog3, int dog4, int dog5) {
   return 0;
}


int find_food_for_hungriest_dog(int *dogs, int dogs_size) {

    int max_dog = dogs[0];
    for (int dog_count = 1; dog_count < dogs_size; dog_count++) {

       if (dogs[dog_count] > max_dog) {
            max_dog = dogs[dog_count];    
       } 
    }

    return max_dog;
}


int find_food_for_hungriest_dog_(int *dogs, int dogs_size) {

    int max_dog_index = 0;
    for (int dog_count = 1; dog_count < dogs_size; dog_count++) {

       if (dogs[dog_count] > dogs[max_dog_index]) {
            max_dog_index = dog_count;    
       } 
    }

    return dogs[max_dog_index];
}


void bad_thing() {

    int x = 0;    
    int numbers[5] = {1, 2, 3, 4, 5};

    numbers[-1] = 10;

    printf("numbers[5] is now %d, x has value %d\n", numbers[5], x);
    

}


int main() {

    
    int dogs[3];

    int max1 = dogs[0];
    if (dogs[1] > max1) {
        max1 = dogs[1];
    }
    if (dogs[2] > max1) {
        max1 = dogs[2];
    }



    // scanf...

    int sharik = 10;
    int pushok = 12;
    int gai = 15;

    // Найти значение корма самой голодной собаки;

    int max2 = sharik;
    if (pushok > max2) {
        max2 = pushok;
    }
    if (gai > max2) {
        max2 = gai;
    }

    //// result

    

    // bad thing will happen;

    bad_thing();


    printf("Bad thing did not happen\n");
    
    return 0;

}
