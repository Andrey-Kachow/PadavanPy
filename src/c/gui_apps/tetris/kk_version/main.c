// #include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include <time.h>

#define CELL_SIZE 10
#define GAME_SIZE 100
#define SCREEN_WIDTH CELL_SIZE * GAME_SIZE
#define SCREEN_HEIGHT CELL_SIZE * GAME_SIZE

int Current_Buffer = 0;
SDL_Surface *screen_surface = NULL;
bool Game_Buffer[2][GAME_SIZE * GAME_SIZE];

void Init_Game_Buffer() {
	srand(time(NULL));
	int number_time = 0;
	while (number_time < GAME_SIZE * GAME_SIZE) {
		Game_Buffer[Current_Buffer][number_time] = rand()&1;
		number_time += 1;
	}
}

void Draw_Game() {
	SDL_Rect Regtangle;
	Regtangle.w = CELL_SIZE;
	Regtangle.h = CELL_SIZE;
	int number_time = 0;
	while (number_time < GAME_SIZE * GAME_SIZE) {
		Regtangle.x = number_time % GAME_SIZE * CELL_SIZE;
		Regtangle.y = number_time / GAME_SIZE * CELL_SIZE;
		if (Game_Buffer[Current_Buffer][number_time]) {
			SDL_FillRect(screen_surface, &Regtangle, SDL_MapRGB(screen_surface->format, 255, 255, 255));
		} else {
			SDL_FillRect(screen_surface, &Regtangle, SDL_MapRGB(screen_surface->format, 0, 0, 0));
		}
		number_time += 1;
	}
}

void Update_Game() {
	bool* Input_Buffer = Game_Buffer[Current_Buffer];
	Current_Buffer = (Current_Buffer + 1) % 2;
	bool* Output_Buffer = Game_Buffer[Current_Buffer]; 
	// Current_Buffer = (Current_Buffer - 1) % 2;
	//Homework do the next step in output buffer

	int Current_Element = 0;
	while (Current_Element < (GAME_SIZE * GAME_SIZE)) {
		int Neighbour_Count = 0;

		// ??? 
		Neighbour_Count += Input_Buffer[(Current_Element - GAME_SIZE + 1) % (GAME_SIZE * GAME_SIZE)];
		Neighbour_Count += Input_Buffer[(Current_Element - GAME_SIZE) % (GAME_SIZE * GAME_SIZE)];
		Neighbour_Count += Input_Buffer[(Current_Element - GAME_SIZE - 1) % (GAME_SIZE * GAME_SIZE)];
		Neighbour_Count += Input_Buffer[(Current_Element - 1) % (GAME_SIZE * GAME_SIZE)];
		Neighbour_Count += Input_Buffer[(Current_Element + 1) % (GAME_SIZE * GAME_SIZE)];
		Neighbour_Count += Input_Buffer[(Current_Element + GAME_SIZE - 1) % (GAME_SIZE * GAME_SIZE)];
		Neighbour_Count += Input_Buffer[(Current_Element + GAME_SIZE) % (GAME_SIZE * GAME_SIZE)];
		Neighbour_Count += Input_Buffer[(Current_Element + GAME_SIZE + 1) % (GAME_SIZE * GAME_SIZE)];
		
		

		if (Input_Buffer[Current_Element] == 1) {
			if (Neighbour_Count == 2 || Neighbour_Count == 3) {
				Output_Buffer[Current_Element] = 1;
			} else {
				Output_Buffer[Current_Element] = 0;
			}
		} else {
			if (Neighbour_Count == 3) {
				Output_Buffer[Current_Element] = 1;
			} else {
				Output_Buffer[Current_Element] = 0;
			}
		}
		Current_Element += 1;
	}
}

int main(int argc, char *argv[]) {

	SDL_Window *window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initilaize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Conway", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	screen_surface = SDL_GetWindowSurface(window);

	SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 255, 255, 255));

	Init_Game_Buffer();

	SDL_UpdateWindowSurface(window);

	SDL_Event event;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		Draw_Game();
		Update_Game();
		SDL_UpdateWindowSurface(window);
		SDL_Delay(100);
	}

    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}