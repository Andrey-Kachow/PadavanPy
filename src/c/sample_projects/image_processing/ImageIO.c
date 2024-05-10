#include <stdio.h>
#include <stdlib.h>

struct pixel {
    int red;
    int blue;
    int green;
};

struct picture {
    int width;
    int height;
    struct pixel* pixels;
};

struct picture* create_picture(int width, int height) {
    struct picture* image = malloc(sizeof(struct picture));
    //// to do warning ////
    image->width = width;
    image->height = height;
    image->pixels = malloc(sizeof(struct pixel) * (width * height));
    //// to do warning ////
    return image;
}

void destroy_picture(struct picture* picture) {
    free(picture->pixels);
    free(picture);
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
    
    FILE * ptrFile = fopen(filename, "r");
    if (ptrFile == NULL) {
        perror("Error opening file");
        return NULL;
    }

    /*
        Task 1. Используя функцию fgets(buffer, n, ptrFile), Прочитать заголовок файла
            1) Считать и проигнорировать символы, содержащие строку формата заголовка (P3)
            2) Считать текст ширины и высоты картинки и coxpaнить их в переменные (Пример: 1410 942)
            4) Считать и проигнорировать текст, означающий максимальное значение канала (255)

        Примечание: Может потребоваться посмотреть как пользоваться фунцкией fgets
                    https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
    */
    /////////////////////////// BEGIN TASK 1 CODE /////////////////////////
    
    char buffer[50];

    /////////////////////////// END TASK 1 CODE ///////////////////////////

    /*
        Task 2. Используя функцию create_picture создать картинку нужного размера и сохранить в переменную image
    */
    /////////////////////////// BEGIN TASK 2 CODE /////////////////////////
    
    struct picture *image;

    /////////////////////////// END TASK 2 CODE ///////////////////////////

    /*
        Task 3. Используя функцию fgets(buffer, n, ptrFile), Прочитать заголовок последовательность rgb значений
                и сохранить их в массив пикселей структуры картинки.
    */
    /////////////////////////// BEGIN TASK 3 CODE /////////////////////////
    

    /////////////////////////// END TASK 3 CODE ///////////////////////////

    fclose(ptrFile);
    return image;
}

void save_picture_as_ppm(struct picture * image, char * filepath) {

    FILE * ptrFile = fopen(filepath, "w");
    if (ptrFile == NULL) {
        perror("Error opening file");
        return NULL;
    }

    /*
        Task 4. Используя функции fprintf или putc, записать заголовок ppm файла ptrFile (каждый пункт с новой строки)
            1) Вписать обязательную часть: "P3\n"
            2) Вписать ширину и высоту картинки "<ширина> <высота>\n"
            4) Вписать максимальную глубину цвета '255\n'
    */
    /////////////////////////// BEGIN TASK 4 CODE /////////////////////////
    

    /////////////////////////// END TASK 4 CODE ///////////////////////////

    /*
        Task 5. Используя функции fprintf или putc, записать последовательность пикселей в файл

        Примечание: для простоты можно каждый пиксель выписывать в отдельной строке, т.е. "<r> <g> <b>\n"
        Например "212 1 135\n"
    */
    /////////////////////////// BEGIN TASK 4 CODE /////////////////////////
    

    /////////////////////////// END TASK 4 CODE ///////////////////////////

    fclose(ptrFile);
}

/*
    Task 6. Реализовать функцию, применяющую черно-белый фильтр (оттенки серого)
    
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

}

/*
    Task 7. Реализовать функцию, применяющую фильтр Сепия
    
    Algorithm to convert a colored image to sepia −
        Get the red green blue values of each pixel

        Get the average of these 3 colors.

        Define the depth and intensity values (ideally 20, and 30).

        Modify the values as −

        red = red + (depth*2).

        Green = green +depth.

        blue = blue-intensity.

        Make sure that the modified values are between 0 to 255.

        Create a new pixel value from the modified colors and set the new value to the pixel.

    источник: https://www.tutorialspoint.com/how-to-convert-a-colored-image-to-sepia-image-using-java-opencv-library
*/
#define DEFAULT_SEPIA_DEPTH 20
#define DEFAULT_SEPIA_INTENSITY 30
void sepia(struct picture * image, int depth, int intensity) {

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

}

/*
    Task 9. Реализовать функцию, применяющую фильтр размытия картинки
    
    Эффект размытия достигается путем замены RGB значений каждого пикселя
    на средне арифметическое значение RGB его самого и смежных соседей в квадрате 3x3.

    +----+----+----+
    | p0 | p1 | p2 | 
    +----+----+----+   Таким образом новые RGB значения пикселя p4 будут получены следующим образом:
    | p3 | p4 | p5 |        p4.r = (p0.r + p1.r + ... + p7.r + pg.r) / 9
    +----+----+----+        p4.g = (p0.g + p1.g + ... + p7.g + pg.g) / 9
    | p6 | p7 | p8 |        p4.r = (p0.b + p1.b + ... + p7.b + pg.b) / 9
    +----+----+----+

    Не забудьте учесть, что крайние и угловые пиксели имеют менее восьми соседей. 
    Для них нужно брать средне арифметическое из меньшего количества пикселей или игногировать.

    #  (Бонус)
    # Примечание:   Вместо целочисленного деления лучше использовать деление чисел с плавающей точкой
                    и округлить значение по стандартным правилам округления вместо отбрасывания целой части.

*/
void blur(struct picture * image) {

}

/*
    Task 10. Реализовать функцию, применяющую фильтр резкости
    
    Эффект резкости достигается путем замены RGB значений каждого пикселя
    на средне взвешенную сумму соответствующих значений RGB его самого 
    и смежных соседей в квадрате 3x3.

    возьмем пиксели     и     соответствующие веса W
    +----+----+----+            +----+----+----+
    | p0 | p1 | p2 |            | +0 | -1 | +0 |
    +----+----+----+            +---+----+----+
    | p3 | p4 | p5 |            | -1 | +5 | -1 |
    +----+----+----+            +----+----+----+
    | p6 | p7 | p8 |            | +0 | -1 | +0 |
    +----+----+----+            +----+----+----+
    
    Таким образом новые RGB значения пикселя p4 будут получены следующим образом:
        p4.r = W[0]*p0.r + W[1]*p1.r + ... + W[7]*p7.r + W[8]*p8.r
        p4.g = W[0]*p0.g + W[1]*p1.g + ... + W[7]*p7.g + W[8]*p8.g
        p4.b = W[0]*p0.b + W[1]*p1.b + ... + W[7]*p7.b + W[8]*p8.b

    Не забудьте учесть, что крайние и угловые пиксели имеют менее восьми соседей. 
    Их можно не трогать.
    Также нельзя, чтобы значение пикселя было больше 255, что может произойти в особых случаях.

    #  (Бонус)
    # Примечание:   Обратите внимание, что сумма весов равна 1. 
                    Попробуйте объяснить, почему это важно.
*/
void sharpen(struct picture * image) {

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
            blur(image);  // как например

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

    struct picture * image = create_picture_from_ppm_file("Some_Amazing_Image_Name.ppm");

    // Apply Transformations
    // blur(image);  // как например

    save_picture_as_ppm(image, "Result_Image.ppm");
    destroy_picture(image);

    return 0;
}