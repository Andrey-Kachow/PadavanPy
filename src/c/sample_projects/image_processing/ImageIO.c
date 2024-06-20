#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct pixel {
    int red;
    int green;
    int blue;
};

struct picture {
    int width;
    int height;
    struct pixel* pixels;
};

int decimal_string_to_int (char * decimal_string) {
    int index_current1 = 0;
    int result1 = 0;
    // printf("%s\n", decimal_string);
    while(decimal_string[index_current1] >= '0' && decimal_string[index_current1] <= '9') {
        result1 = result1 * 10 + decimal_string[index_current1] - '0';
        index_current1 += 1;
    }
    return result1;
}

struct picture* create_picture(int width, int height) {
    struct picture* image = malloc(sizeof(struct picture));
    if (image == NULL) {
        return NULL;
    }
    image->width = width;
    image->height = height;
    image->pixels = malloc(sizeof(struct pixel) * (width * height));
    if (image == NULL) {
        free(image);
        return NULL;
    }
    return image;
}

void destroy_picture(struct picture* picture) {
    free(picture->pixels);
    free(picture);
}

#define READ_BUFFER_ALLOCATION 64 * 1024
#define READ_BUFFER_SIZE (READ_BUFFER_ALLOCATION - 1)

int accept_int(char ** buffer_ptr) {

    while(**buffer_ptr == ' ' || **buffer_ptr == '\n') {
        *buffer_ptr += 1;
    }
    if (**buffer_ptr == '\0') {
        return -1; // -1 -- не дошли до цифер
    }

    int total = 0;
    int counter = 0;
    while(**buffer_ptr >= '0' && **buffer_ptr <= '9') {
        total = total * 10 + **buffer_ptr - '0';
        *buffer_ptr += 1;
        counter += 1;
    }
    if (**buffer_ptr == '\0' && counter < 3) {
        return total * 1000; // число подозревается
    }
    return total;

    // char letter;
    // fscanf(file_pointer, "%c", &letter);
    // while (letter == ' ' || letter == '\n') {
    //     // printf("~%c", letter);
    //     fscanf(file_pointer, "%c", &letter);
    // }
    // int total = 0;
    // // printf("\n\n\n\n----\nSKIPPED\n-----\n\n\n\n");
    // while (letter >= '0' && letter <= '9') {
    //     total = total * 10 + letter - '0';
    //     // printf("~%c", letter);
    //     fscanf(file_pointer, "%c", &letter);
    // }
    // return total;
    // /*
    // //     do {
    //         fscanf(file_pointer, "%c", &letter);
    //     } while (letter == ' ' || letter == '\n');
        
    // */
}

int complete_int(char ** buffer_ptr, int rgb) {
    while(**buffer_ptr >= '0' && **buffer_ptr <= '9') {
        rgb = rgb * 10 + **buffer_ptr - '0';
        *buffer_ptr += 1;
    }
    return rgb;
}

int read_rgb(char ** buffer_ptr, char * file_buffer, FILE * ptrFile) {
    int rgb;
    do {
        rgb = accept_int(buffer_ptr);
        if (rgb > 255) {
            rgb /= 1000;
            *buffer_ptr = fgets(file_buffer, READ_BUFFER_SIZE, ptrFile);
            rgb = complete_int(buffer_ptr, rgb);
        }
        if (rgb == -1) {
            *buffer_ptr = fgets(file_buffer, READ_BUFFER_SIZE, ptrFile);
            continue;
        }
        break;
    } while (true);
    return rgb;
}

/*
    PPM file structure :

    P3\n                           #  1) Header (always P3 for our purposes)
    1410 942\n                     #  2) Width and height as text decimals separated with a whitespace
    255\n                          #  3) Max RGB color channel value (always 255 for our purposes)
    153 175 209 153 175 209 ... \n #  4) Raw RGB values as text with spaces or newline characters acting as separators
    174 192 222 174 5 222 ...      #     line must not be very long and every pixel can start with a new line
    ...   \                        #
                                   #  5) Last line must be blank line
*/
struct picture * create_picture_from_ppm_file(char * filename) {
    /*
        Task 1. Используя функцию fgets(buffer, n, ptrFile), Прочитать заголовок файла
            1) Считать и проигнорировать символы, содержащие строку формата заголовка (P3)
            2) Считать текст ширины и высоты картинки и coxpaнить их в переменные (Пример: 1410 942)
            3) Считать и проигнорировать текст, означающий максимальное значение канала (255)

        Примечание: Может потребоваться посмотреть как пользоваться фунцкией fgets
                    https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
    */
    /////////////////////////// BEGIN TASK 1 CODE /////////////////////////
    int width;
    int height;


    char buffer[READ_BUFFER_SIZE];
    FILE * ptrFile = fopen(filename, "r");
    int long_size = 0;
    if (ptrFile == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }
    fgets(buffer, READ_BUFFER_SIZE, ptrFile);
    fgets(buffer, READ_BUFFER_SIZE, ptrFile);
    // printf("%s", buffer);

    char * width_pointer;
    char * letter_pointer = buffer;
    char * height_pointer = NULL;
    width_pointer = letter_pointer;
    while (height_pointer == NULL) {
        if (*letter_pointer == ' ') {
            height_pointer = letter_pointer + 1;
        }
        letter_pointer += 1;
    }

    width = decimal_string_to_int(width_pointer);
    height = decimal_string_to_int(height_pointer);
    fgets(buffer, READ_BUFFER_SIZE, ptrFile);
    // printf("%d\n", width);
    // printf("%d", height);

    /////////////////////////// END TASK 1 CODE ///////////////////////////
    /*
        Task 2. Используя функцию create_picture создать картинку нужного размера и сохранить в переменную image
    */
    /////////////////////////// BEGIN TASK 2 CODE /////////////////////////

    struct picture *image;
    image = create_picture(width, height);

    /////////////////////////// END TASK 2 CODE ///////////////////////////
    /*
        Task 3. Используя функцию fgets(buffer, n, ptrFile), Прочитать заголовок последовательность rgb значений
                и сохранить их в массив пикселей структуры картинки.
    */
    /////////////////////////// BEGIN TASK 3 CODE /////////////////////////
    
        // int colors = 0; // каждое значение rgb, она будет увеличиваться
        // if (next1 == 2) {
        //     if (*letter_pointer1 == ' ') {
        //         colors += 1;
        //         if (colors == 1) {
        //             blue = *letter_pointer1;
        //         }
        //         if (colors == 2) {
        //             green = *letter_pointer1;
        //         }
                
        //         red = *letter_pointer1;
        //     }    
        // }
    char * file_buffer = malloc(sizeof(char) * READ_BUFFER_ALLOCATION);
    
    int red;
    int blue;
    int green;

    int next1 = 0;
    int pixel_counter = 0;
    while (pixel_counter < width * height && fgets(file_buffer, READ_BUFFER_SIZE, ptrFile)) {
        char * buffer_ptr = file_buffer;
        while (pixel_counter < width * height && *buffer_ptr != '\0') {
            red = read_rgb(&buffer_ptr, file_buffer, ptrFile);
            green = read_rgb(&buffer_ptr, file_buffer, ptrFile);
            blue = read_rgb(&buffer_ptr, file_buffer, ptrFile);
            // green = accept_int(&buffer_ptr);
            printf("%d ---> rgb(%d, %d, %d)\n", pixel_counter, red, green, blue);
            // printf("%s\n", buffer_ptr);

            image->pixels[pixel_counter].red = red;
            image->pixels[pixel_counter].green = green;
            image->pixels[pixel_counter].blue = blue;
            pixel_counter += 1;
        }
        // image->pixels[pixel_counter].red = red
    }
    
    free(file_buffer);
    /////////////////////////// END TASK 3 CODE ///////////////////////////

    fclose(ptrFile);
    return image;
}

void save_picture_as_ppm(struct picture * image, char * filepath) {

    FILE * ptrFile = fopen(filepath, "w");
    if (ptrFile == NULL) {
        perror("Error opening file");
        return;
    }

    /*
        Task 4. Используя функции fprintf или putc, записать заголовок ppm файла ptrFile (каждый пункт с новой строки)
            1) Вписать обязательную часть: "P3\n"
            2) Вписать ширину и высоту картинки "<ширина> <высота>\n"
            4) Вписать максимальную глубину цвета '255\n'
    */
    /////////////////////////// BEGIN TASK 4 CODE /////////////////////////

    fprintf(ptrFile, "P3\n");
    fprintf(ptrFile, "%d %d\n", image->width, image->height);
    fprintf(ptrFile, "255\n");    

    /////////////////////////// END TASK 4 CODE ///////////////////////////

    /*
        Task 5. Используя функции fprintf или putc, записать последовательность пикселей в файл

        Примечание: для простоты можно каждый пиксель выписывать в отдельной строке, т.е. "<r> <g> <b>\n"
        Например "212 1 135\n"
    */
    /////////////////////////// BEGIN TASK 4 CODE /////////////////////////
    
    
    int pixel_counter = 0;
    while (pixel_counter != image->width * image->height) {
        struct pixel px= image->pixels[pixel_counter];

        int red = px.red;
        int green = px.green;
        int blue = px.blue;

        fprintf(ptrFile, "%d %d %d\n", red, green, blue);
        pixel_counter += 1;  
    }

    /////////////////////////// END TASK 4 CODE ///////////////////////////
    fclose(ptrFile);
}

/*
    Task 6. Реализовать функцию, применяющую чернобелый фильтр (оттенки серого)
    
    Эффект достигается путем замены RGB значений каждого пикселя 
    на средне-арифметическое значений для каждого канала --> (R + G + B) / 3.

    #  (Бонус)
    # Примечание:   В реальности синий канал RGB слабее влияет на яркость пикселя.
                    Насыщенный синий цвет темнее чем сопоставимый красный или зеленый.
                    Поэтому для более качественного результата может иметь смысл брать
                    взвещенную сумму, где вес каждого канала соответствует влиянию на яркость.

                    Например Grayscale = 0.299*R + 0.587*G + 0.114*B

                    Попробуйте разные варианты и сравните результаты
*/
void grayscale(struct picture * image) {

    int pixel_counter = 0;
    while (pixel_counter != image->width * image->height) {
        struct pixel px= image->pixels[pixel_counter];
        int red = px.red;
        int green = px.green;
        int blue = px.blue;

        int red_gray = (red + green + blue) / 3;
        int green_gray = (red + green + blue) / 3;
        int blue_gray = (red + green + blue) / 3;
        
        image->pixels[pixel_counter].red = red_gray;
        image->pixels[pixel_counter].green = green_gray;
        image->pixels[pixel_counter].blue = blue_gray;

        // fprintf(ptrFile, "%d %d %d\n", red_gray, green_gray, blue_gray);
        pixel_counter += 1;  
    }
}

/*
    Task 7. Реализовать функцию, применяющую фильтр Сепия
    
    Algorithm to convert a colored image to sepia −
        1.Get the red green blue values of each pixel
        2.Get the average of these 3 colors.
        3.Define the depth and intensity values (ideally 20, and 30).
        4.Modify the values as −
        5.red = red + (depth*2).
        6.Green = green + depth.
        7.blue = blue - intensity.
        8.Make sure that the modified values are between 0 to 255.
        9.Create a new pixel value from the modified colors and set the new value to the pixel.

    источник: https://www.tutorialspoint.com/how-to-convert-a-colored-image-to-sepia-image-using-java-opencv-library
*/
#define DEFAULT_SEPIA_DEPTH 20
#define DEFAULT_SEPIA_INTENSITY 30
void sepia(struct picture * image, int depth, int intensity) {

    int pixel_counter = 0;
    while (pixel_counter != image->width * image->height) {
        struct pixel px= image->pixels[pixel_counter];

        // colors
        int red = px.red;
        int green = px.green;
        int blue = px.blue;

        // average of colors
        int red_average = red + 0 *(red + green + blue) / 3;
        int green_average = green + 0 *(red + green + blue) / 3;
        int blue_average = blue + 0 *(red + green + blue) / 3;

        // sepia_filter
        int red_sepia = red_average + (depth*2);
        if (red_sepia > 255) {
            red_sepia = 255;
        }

        int green_sepia = green_average + depth;
        if (green_sepia > 255) {
            green_sepia = 255;
        }

        int blue_sepia = blue_average - intensity;
        if (blue_sepia > 255) {
            blue_sepia = 255;
        }
        if (blue_sepia < 0) {
            blue_sepia = 0;
        }

        image->pixels[pixel_counter].red = red_sepia;
        image->pixels[pixel_counter].green = green_sepia;
        image->pixels[pixel_counter].blue = blue_sepia;

        // fprintf(ptrFile, "%d %d %d\n", red, green, blue);
        pixel_counter += 1;
    }

}

/*
    Task 8. Реализовать функцию, применяющую фильтр негатив
    
    Эффект достигается путем замены RGB значений каждого пикселя на обратное значение.
    Яркое становится темным, а темное ярким.
        r = 255 - r
        g = 255 - g
        b = 255 - b
*/
void negative(struct picture * image) {

    int pixel_counter = 0;
    while (pixel_counter != image->width * image->height) {
        struct pixel px= image->pixels[pixel_counter];

        int red = px.red;
        int green = px.green;
        int blue = px.blue;

        int red_negative = 255 - red;
        int green_negative = 255 - green;
        int blue_negative = 255 - blue;

        image->pixels[pixel_counter].red = red_negative;
        image->pixels[pixel_counter].green = green_negative;
        image->pixels[pixel_counter].blue = blue_negative;

        // fprintf(ptrFile, "%d %d %d\n", red, green, blue);
        pixel_counter += 1;  
    }

}

/*
    Task 9. Реализовать функцию, применяющую фильтр размытия картинки

    Эффект размытия достигается путем замены RGB значений каждого пикселя
    на средне арифметическое значение RGB его самого и смежных соседей в квадрате 3x3.

    +----+----+----+
    | p0 | p1 | p2 | 
    +----+----+----+   Таким образом новые RGB значения пикселя p4 будут получены следующим образом (Псевдокод):
    | p3 | p4 | p5 |        p4.r = (p0.r + p1.r + ... + p7.r + p8.r) / 9
    +----+----+----+        p4.g = (p0.g + p1.g + ... + p7.g + p8.g) / 9
    | p6 | p7 | p8 |        p4.b = (p0.b + p1.b + ... + p7.b + p8.b) / 9
    +----+----+----+

    Не забудьте учесть, что крайние и угловые пиксели имеют менее восьми соседей. 
    Для них нужно брать средне арифметическое из меньшего количества пикселей или игногировать.

    (!!) Обратите внимание, что новые пиксели нужно сохранять в output_image

    #  (Бонус)
    # Примечание:   Вместо целочисленного деления лучше использовать деление чисел с плавающей точкой
                    и округлить значение по стандартным правилам округления вместо отбрасывания целой части.

*/
void blur(struct picture * input_image, struct picture * output_image) {

    int pixel_counter = 0;
    while (pixel_counter != input_image->width * input_image->height) {
        int pix_n = 0;
        int total_r = 0;
        int total_g = 0;
        int total_b = 0;

        int middle_i = pixel_counter / input_image->width;
        int middle_j = pixel_counter % input_image->width;

        for (int y=-1; y<2; y++) {
            for (int x=-1; x<2; x++) {
                
                int neighbourhood_pixel_i = middle_i + y;
                int neighbourhood_pixel_j = middle_j + x;

                // проверка краев и углов.
                if (neighbourhood_pixel_j >= 0 && neighbourhood_pixel_j < input_image->width) {
                    if (neighbourhood_pixel_i >= 0 && neighbourhood_pixel_i < input_image->height) {
                        
                        int neighbourhood_pixel_index = neighbourhood_pixel_i * input_image->width + neighbourhood_pixel_j;
                        struct pixel px= input_image->pixels[neighbourhood_pixel_index]; 

                        int red = px.red;
                        int green = px.green;
                        int blue = px.blue;
                        
                        total_r += red;
                        total_g += green;
                        total_b += blue;
                        pix_n += 1;
                    }
                }
            }     
        }
        total_r /= pix_n;
        total_g /= pix_n;
        total_b /= pix_n;
        
        output_image->pixels[pixel_counter].red = total_r;
        output_image->pixels[pixel_counter].green = total_g;
        output_image->pixels[pixel_counter].blue = total_b;

        // fprintf(ptrFile, "%d %d %d\n", red_gray, green_gray, blue_gray);
        pixel_counter += 1;  
    }
}

/*
    Task 10. Реализовать функцию, применяющую фильтр резкости
    
    Эффект резкости достигается путем замены RGB значений каждого пикселя
    на средне взвешенную сумму соответствующих значений RGB его самого 
    и смежных соседей в квадрате 3x3.

    возьмем пиксели p    и    соответствующие веса W
    +----+----+----+            +----+----+----+
    | p0 | p1 | p2 |            | +0 | -1 | +0 |
    +----+----+----+            +---+----+----+
    | p3 | p4 | p5 |            | -1 | +5 | -1 |
    +----+----+----+            +----+----+----+
    | p6 | p7 | p8 |            | +0 | -1 | +0 |
    +----+----+----+            +----+----+----+
    
    Таким образом новые RGB значения пикселя p4 будут получены следующим образом (Псевдокод):
        p4.r = W[0]*p0.r + W[1]*p1.r + ... + W[7]*p7.r + W[8]*p8.r
        p4.g = W[0]*p0.g + W[1]*p1.g + ... + W[7]*p7.g + W[8]*p8.g
        p4.b = W[0]*p0.b + W[1]*p1.b + ... + W[7]*p7.b + W[8]*p8.b

    Не забудьте учесть, что крайние и угловые пиксели имеют менее восьми соседей. 
    Их можно не трогать.
    Также нельзя, чтобы значение пикселя было больше 255, что может произойти в особых случаях.

    (!!) Обратите внимание, что новые пиксели нужно сохранять в output_image

    #  (Бонус)
    # Примечание:   Обратите внимание, что сумма весов равна 1. 
                    Попробуйте объяснить, почему это важно.
*/
void sharpen(struct picture * input_image, struct picture * output_image) {

}

/*
    Как проверять результат.

    PPM - наиболее упрощенный формат хранения картинок,
    максимально хорошо походящий для начального уровня 
    сложности изучения и тренировки программирования.

    Формат не добавляет никаких уровней сложности в виде форматов
    сжатия или бинарных кодировок.

    К сожалению, формат не поддерживается Windows по умолчанию,
    поэтому для просмотра изображений нужны дополнительные программы.

    Для самопроверки будем использовать программу ImageMagick 
    и действовать по следующей пошаговой инструкции:

        Шаг 0 
        Вбить в Powershell команду:
        >  winget install ImageMagick
        
        Шаг 1
        Перезапустить Powershell

        Шаг 2
        Найти любую понравившуюся картинку в формате стандартных PNG или JPEG.
        Можно скачать в интернете.

        Шаг 3
        Сохранить картинку в папку с программой.

        Шаг 4
        Перевод в формат PPM. Запустить команду в Powershell:
        > magick <название исходной картинки> -compress Some_Amazing_Image_Name.ppm

        Шаг 5
        Запустить данную С программу, выполняющую код:

            struct picture * image = create_picture_from_ppm_file("Some_Amazing_Image_Name.ppm");

            // Применить трансформацию
            grayscale(image);  // как например

            save_picture_as_ppm(image, "Result_Image.ppm")
            destroy_picture(picture);

        Можно не применять трансформации, чтобы проверить правильность обычного считывания и сохранения.

        Шаг 6
        Перевод PPM в формат PNG для просмотра результата. Запустить Powershell команду:
        > magick Result_Image.ppm Result_Image.png

        Шаг 7
        Просмотреть получившееся изображение Result_Image.png (или другое, если сохраняли по другому имени)

        Шаг 8
        Перейти к шагу 2. Можно менять названия картинок и аргументов программы magick

*/
int main() {

    int depth = DEFAULT_SEPIA_DEPTH;
    int intensity = DEFAULT_SEPIA_INTENSITY;

    struct picture * image = create_picture_from_ppm_file("Photo1.ppm");


    int selection = 0;
    while (selection != 6) {
        printf("Enter number of filter (1 - grayscale, 2 - sepia, 3 - negative, 4 - blur, 5 - sharpen, 6 - exit):\n");
        scanf("%d", &selection);
        if (selection == 1) {
            grayscale(image);
            save_picture_as_ppm(image, "Grayscale_Image.ppm");
            break;
        }
        if (selection == 2) {
            sepia(image, depth, intensity);
            save_picture_as_ppm(image, "Sepia_Image.ppm");
        }
        if (selection == 3) {
            negative(image);
            save_picture_as_ppm(image, "Negative_Image.ppm");
        }
        if (selection == 4) {
            struct picture * output_image = create_picture(image->width, image->height);
            save_picture_as_ppm(output_image, "Blur_Image.ppm");
            destroy_picture(output_image);
        }
        if (selection == 6) {
            break;
        }
        if (selection > 6) {
            printf("Selection error! No such option: %d\n", selection);
        }
    }

    // Apply Transformations

    // Примечание: Для успешного применения функций blur и sharpen, нужно создать дополнительную картинку,
    // у которой размеры будут такие же, как и у исходной. 
    // (Ну или w - 2, h - 2, если вырезать рамку пикселей с неполным соседством 3x3 - стенки и углы)
    destroy_picture(image);

    return 0;
}
