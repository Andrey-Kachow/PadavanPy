// #include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>

#define CONTAINER_WIDTH 10
#define CONTAINER_HEIGHT 30

#define GRID_CELL_SIZE 5
#define CONTAINER_BOUNDS 5

#define GAME_SIDE_BOARD_WIDTH 200
#define UI_ELEMENTS_SEPARATION 20
#define UI_PADDING 25

#define CONTAINER_UI_WIDTH (CONTAINER_WIDTH*GRID_CELL_SIZE+2*CONTAINER_BOUNDS)
#define CONTAINER_UI_HEIGHT (CONTAINER_HEIGHT*GRID_CELL_SIZE+CONTAINER_BOUNDS)

#define SCREEN_WIDTH (2*UI_PADDING+UI_ELEMENTS_SEPARATION+CONTAINER_UI_WIDTH)
#define SCREEN_HEIGHT (2*UI_PADDING+CONTAINER_HEIGHT)

int main(int argc, char *argv[]) {

	SDL_Window *window = NULL;

	SDL_Surface *screen_surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initilaize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("SDL App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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