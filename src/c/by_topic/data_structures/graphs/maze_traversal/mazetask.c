#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define READ_BUFFER_SIZE 50
struct path_position {
    int y;
    int x;
    struct path_position *previous_position;
};

struct path_queue {
    int start;
    int current_size;
    int size_array;
    struct path_position **array;
};

struct path_queue * queue_create(int size_array) {
    struct path_queue * result = malloc(sizeof(struct path_queue));
    if (result == NULL) {
        return NULL;
    }
    result->start = -1;
    result->current_size = 0;
    result->array = malloc(sizeof(struct path_position*) * size_array);
    if (result->array == NULL) {
        free(result);
        return NULL;
    }
    result->size_array = size_array;
    return result;
}

void queue_add(struct path_queue * this_queue, struct path_position * new_element) {
    int end = this_queue->current_size + this_queue->start;
    end %= this_queue->size_array;
    this_queue->array[end] = new_element;
    this_queue->current_size += 1;
}

struct path_position * queue_poll(struct path_queue * this_queue) {
    if (this_queue->current_size == 0) {
        printf("ERROR: empty queue poll\n");
        return -1;
    }
    struct path_position * result = this_queue->array[this_queue->start];
    this_queue->start += 1;
    this_queue->start %= this_queue->size_array;
    this_queue->current_size -= 1;
    return result;
}

bool queue_empty(struct path_queue * this_queue) {
    return this_queue->current_size == 0;
}

// int accept_int(FILE * file_pointer) { /// возможно пригодится
//     char letter;
//     fscanf(file_pointer, "%c", &letter);
//     while (letter == ' ' || letter == '\n') {
//         fscanf(file_pointer, "%c", &letter);
//     }
//     int total = 0;
//     while (letter >= '0' && letter <= '9') {
//         total = total * 10 + letter - '0';
//         fscanf(file_pointer, "%c", &letter);
//     }
//     return total;
// } ///////////////////////////////////////////////////////////

void calculate_maze_size(char * file_path, int * line_width, int * line_count) {
    char buffer[READ_BUFFER_SIZE];
    FILE * ptrFile = fopen(file_path, "r");
    if (ptrFile == NULL) {
        printf("Error opening file.\n");
    }
    *line_width = -1;
    int count_lines = 0;
    while (fgets(buffer, READ_BUFFER_SIZE, ptrFile) != NULL) {
        if (*line_width == -1) {
            *line_width = strlen(buffer) - 1;
        }
        count_lines += 1;
    }
    *line_count = count_lines;
    fclose(ptrFile);
}

void maze_load(char * file_path, char * maze, int line_width, int line_count) {
    char buffer[READ_BUFFER_SIZE];
    FILE * ptrFile = fopen(file_path, "r");
    if (ptrFile == NULL) {
        printf("Error opening file.\n");
    }
    for (int i=0; i!=line_count; i++) {
        fgets(buffer, READ_BUFFER_SIZE, ptrFile);
        memcpy(maze + i * line_width, buffer, line_width);
    } 
    fclose(ptrFile);
}

bool path_contains(struct current_position * position, int x, int y) {
    return false;
}

char maze_get(char * maze, struct path_position * position, int maze_width) {
    return maze[position->y * maze_width + position->x];
}

void print_maze(char * maze, int maze_width, int maze_height) {
    for (int i=0; i<maze_height; i++) {
        for (int j=0; j<maze_width; j++) {
            printf("%c", maze[i * maze_width + j]);
        }
        printf("\n");
    }
}

int main() {
    // char * maze_buffer;
    // int maze_width;
    // int maze_height;
    // struct path_queue * journal = queue_create();

    // char buffer[READ_BUFFER_SIZE];
    // FILE * ptrFile = fopen("maze.txt", "r");
    // if (ptrFile == NULL) {
    //     printf("Error opening file.\n");
    //     return 1;
    // }
    // fgets(buffer, READ_BUFFER_SIZE, ptrFile);
    // fclose(ptrFile);

    // 1. получить высоту и ширину лабиринта.
    int line_width;
    int line_count;
    calculate_maze_size("maze.txt", &line_width, &line_count);
    printf("%d, %d\n", line_width, line_count);

    // 2. выделить память для лабиринта и сохранить лабиринт.
    char * maze = malloc(sizeof(char) * line_width * line_count);
    maze_load("maze.txt", maze, line_width, line_count);
    print_maze(maze, line_width, line_count);

    // 3. Создать очередь и положить в нее стартовый элемент.
    struct path_queue * journal = queue_create(line_width * line_count);
    struct path_position * start_position = malloc(sizeof(struct path_position));
    start_position->x = 0;
    start_position->y = 1;
    start_position->previous_position = NULL;
    queue_add(journal, start_position);
    while (!queue_empty(journal)) {
        struct path_position * current_position = queue_poll(journal);
        if (maze_get(maze, current_position, line_width) == 'B') {
            printf("END");
            break;
        }
        int dx = 1;
        int dy = 0;
        char neighbour = maze[(current_position->y + dy) * line_width + (current_position->x + dx)];
        if (neighbour == ' ' && !path_contains(current_position, current_position->x + dx, current_position->y + dy)) {
            struct path_position * neighbour_position = malloc(sizeof(struct path_position));
            neighbour_position->x = current_position->x + dx;
            neighbour_position->y = current_position->y + dy;
            neighbour_position->previous_position = current_position;
            queue_add(journal, neighbour_position);
        }
    }

    return 0;
}