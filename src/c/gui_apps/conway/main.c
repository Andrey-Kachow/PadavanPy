// #include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include <time.h>

// #pragma comment(lib,"Shell32.lib")

#define CELL_SIZE 2
#define GAME_SIZE 400

#define SCREEN_WIDTH (CELL_SIZE*GAME_SIZE)
#define SCREEN_HEIGHT (CELL_SIZE*GAME_SIZE)

bool first_game_buffer[GAME_SIZE * GAME_SIZE];
bool second_game_buffer[GAME_SIZE * GAME_SIZE];
bool *source_array = first_game_buffer;
bool *destination_array = second_game_buffer;

Uint32 alive_color;
Uint32 dead_color;

SDL_Window *window;
SDL_Surface *screen_surface;

bool use_first_game_buffer = true;

void init_initial_game(void) {
	srand(time(NULL));
	for (int i = 0; i < GAME_SIZE; i++) {
		for (int j = 0; j < GAME_SIZE; j++) {
			first_game_buffer[i * GAME_SIZE + j] = rand() & 1;
		}
	}
}

void flip_game_buffers() {
	if (use_first_game_buffer) {
		source_array = first_game_buffer;
		destination_array = second_game_buffer;
	} else {
		source_array = second_game_buffer;
		destination_array = first_game_buffer;
	}
	use_first_game_buffer = !use_first_game_buffer;
}

void update_field(void) {
	for (int i = 0; i < GAME_SIZE; i++) {
		for (int j = 0; j < GAME_SIZE; j++) {
			int neighbour_count = 0;
			for (int y = -1; y <= 1; y++) {
				for (int x = -1; x <= 1; x++) {
					if (x != 0 || y != 0) {
						int u = (i + y + GAME_SIZE) % GAME_SIZE;
						int v = (j + x + GAME_SIZE) % GAME_SIZE;
						if (source_array[u * GAME_SIZE + v]) {
							neighbour_count++;
						}
					}
				}
			}
			// double check rules
			if (source_array[i * GAME_SIZE + j]) {
				if (neighbour_count == 2 || neighbour_count == 3) {
					destination_array[i * GAME_SIZE + j] = true;
				} else {
					destination_array[i * GAME_SIZE + j] = false;
				}
			} else {
				if (neighbour_count == 3) {
					destination_array[i * GAME_SIZE + j] = true;
				} else {
					destination_array[i * GAME_SIZE + j] = false;
				}
			}
		}
	}
}

void draw_game(void) {
	SDL_Rect rectangle;
	rectangle.w = CELL_SIZE;
	rectangle.h = CELL_SIZE;
	for (int i = 0; i < GAME_SIZE; i++) {
		rectangle.y = i * CELL_SIZE;
		for (int j = 0; j < GAME_SIZE; j++) {
			rectangle.x = j * CELL_SIZE;
			if (source_array[i * GAME_SIZE + j]) {
				SDL_FillRect(screen_surface, &rectangle, alive_color);
			} else {
				SDL_FillRect(screen_surface, &rectangle, dead_color);
			}
		}
	}
}

int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initilaize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	
	init_initial_game();

	screen_surface = SDL_GetWindowSurface(window);

	alive_color = SDL_MapRGB(screen_surface->format, 255, 255, 255);
	dead_color = SDL_MapRGB(screen_surface->format, 0, 0, 0);

	SDL_FillRect(screen_surface, NULL, dead_color);

	SDL_UpdateWindowSurface(window);

	SDL_Event event;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		flip_game_buffers();
		draw_game();
		update_field();
		SDL_UpdateWindowSurface(window);
		SDL_Delay(50);
	}
	
    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}