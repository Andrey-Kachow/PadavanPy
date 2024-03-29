// #include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

struct Point {
	int x;
	int y;
};

struct Cell {
	struct Point speed;
	struct Point position;
	double energy;
}

struct Cell * create_Cell(int x, int y, double energy) {
	struct Cell *cell = malloc(sizeof(struct Cell));
	if (cell == NULL) {
		return NULL;
	}
	cell->speed.x = 0;
	cell->speed.y = 0;
	cell->position.x = x;
	cell->position.y = y;
	cell->energy = energy;
	return cell;
}

int main(int argc, char *argv[]) {

	SDL_Window *window = NULL;

	SDL_Surface *screen_surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initilaize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Evolution Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	screen_surface = SDL_GetWindowSurface(window);

	SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 255, 255, 255));

	SDL_UpdateWindowSurface(window);

	SDL_Event event;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}