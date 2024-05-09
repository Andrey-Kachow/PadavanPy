#include <stdio.h>
#include <stdlib.h>

struct pixel {
    int red;
    int blue;
    int green;
}

struct picture {
    int width;
    int height;
    struct pixel* pixels;
}

struct picture* create_picture(int width, int height) {
    struct picture* image = malloc(sizeof(struct picture));
    //// to do warning ////
    image->width = width;
    image->height = height;
    image->pixels = malloc(sizeof(struct pixel) * (width * height));
    //// to do warning ////
    return image;
}

void destroy_picture(struct* picture) {
    free(pixels);
    free(picture);
}

int main() {

    int* x = malloc(100 * sizeof(int));

    // int massiv[100];
    for (int i=0; i<100; i++) {
        printf("%d ", x[i]);
    }
    // printf("%s", x)

    free(x);
    return 0;
}