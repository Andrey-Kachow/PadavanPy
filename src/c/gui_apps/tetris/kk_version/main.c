// cl.exe /Zi /I "D:\c_dev_libraries\SDL2-2.28.5\include" main.c /link "D:\c_dev_libraries\SDL2-2.28.5\lib\x86\SDL2main.lib" "D:\c_dev_libraries\SDL2-2.28.5\lib\x86\SDL2.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x86\shell32.lib" /SUBSYSTEM:WINDOWS

// #include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include <time.h>

#define SQUARE 20
#define PADDING 40
#define GAME_WIDTH 15
#define GAME_HEIGHT 40
#define BORDER_WIDTH 5
#define ACTIVE_CELL 'A'
#define EMPTY_CELL 'E'

#define FIELD_HEIGHT_PX (GAME_HEIGHT*(SQUARE+BORDER_WIDTH)+BORDER_WIDTH) 
#define FIELD_WIDTH_PX (GAME_WIDTH*(SQUARE+BORDER_WIDTH)+BORDER_WIDTH)

#define SCREEN_WIDTH (FIELD_WIDTH_PX+2*PADDING) 
#define SCREEN_HEIGHT (FIELD_HEIGHT_PX+2*PADDING)

SDL_Surface *screen_surface = NULL;

struct point {
	int x;
	int y;
};

struct point shapes[7][4] = {
	{{0, 0}, {-1, 0}, {-1, -1}, {1, 0}}, // L_shape_Right
	{{0, 0}, {0,-1}, {-1,-1}, {-1,0}}, // square_shape
	{{0, 0}, {0, -1}, {0, -2}, {0, 1}}, // I_shape
	{{0, 0}, {-1,0}, {1,0}, {-1, -1}}, // L_shape_Left
	{{0, 0}, {1, 0}, {1, -1}, {0, 1}}, // S_shape
	{{0, 0}, {1, 0}, {0, -1}, {1, 1}}, // Z_shape
	{{0, 0}, {-1, 0}, {-1, -1}, {-1, 1}} //T_shape
};


Uint32 primary_color;
Uint32 secondary_color;
Uint32 cell_color;
Uint32 empty_cell_color;
char Field[GAME_HEIGHT][GAME_WIDTH];

/*
	Mark Field Array Elements that correspond to cells in a shape as Active.
*/
void Place_Shape(int shape_id, int x, int y) {
	int destination_x;
	int destination_y;
	for (int count = 0; count < 4; count++) {
		struct point cell = shapes[shape_id][count];
		destination_y = y + cell.y;
		destination_x = x + cell.x;
		Field[destination_y][destination_x] = ACTIVE_CELL;
	}
}

void Clear_field() {
	for (int i=0;i<GAME_HEIGHT;i++) {
		for (int j=0;j<GAME_WIDTH;j++) {
			Field[i][j] = EMPTY_CELL;
		}
	}
}

void test() {
	for (int shape_id = 0; shape_id < 7; shape_id++) {
		int offset = 5 * shape_id;

		Place_Shape(shape_id, GAME_WIDTH / 2, offset + 4);

	}
}



void Init_colors() {
	primary_color = SDL_MapRGB(screen_surface->format, 0, 0, 0);
	secondary_color = SDL_MapRGB(screen_surface->format, 179, 111, 0);
	cell_color = SDL_MapRGB(screen_surface-> format, 224, 142, 7);
	empty_cell_color = SDL_MapRGB(screen_surface-> format, 87, 78, 65);
}

void Draw_Game() {
	SDL_FillRect(screen_surface, NULL, secondary_color);
	// SDL_Rect Square;
	// SDL_Rect Kletka;
	// Square.x = PADDING;
	// Square.y = PADDING;
	// Kletka.w = SQUARE;
	// Kletka.h = SQUARE;
	// Square.w = SQUARE * GAME_WIDTH;
	// Square.h = SQUARE * GAME_HEIGHT;
	// SDL_FillRect(screen_surface, &Square, primary_color);
	// SDL_FillRect(screen_surface, &Kletka, secondary_color);

	// 2. Oбъявляем квадрат внутренний (темный -- цвет границ клетокб сетка)
	SDL_Rect inner;
	inner.w = FIELD_WIDTH_PX;
	inner.h = FIELD_HEIGHT_PX;
	inner.x = PADDING;
	inner.y = PADDING;
	SDL_FillRect(screen_surface, &inner, primary_color);

	// 3. Рисуем игровые клетки (розоватым цветом)
	SDL_Rect cell;
	cell.w = SQUARE;
	cell.h = SQUARE;
	// SDL_FillRect(screen_surface, &cell, cell_color);

	// cell.x cell.y будут меняться.
	int x0 = inner.x + BORDER_WIDTH;
	int y0 = inner.y + BORDER_WIDTH;
	for (int i = 0;i < GAME_HEIGHT; i++) {
		cell.y = (SQUARE+BORDER_WIDTH)*i+y0;
		for (int j = 0;j < GAME_WIDTH; j++) {
			cell.x = (SQUARE + BORDER_WIDTH)*j+x0;
			if (Field[i][j] == ACTIVE_CELL) {
				SDL_FillRect(screen_surface, &cell, cell_color);
			} else {
				SDL_FillRect(screen_surface, &cell, empty_cell_color);
			}
		}
	}
	// while??
}


int main(int argc, char *argv[]) {

	SDL_Window *window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initilaize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	screen_surface = SDL_GetWindowSurface(window);

	SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 255, 255, 255));

	SDL_UpdateWindowSurface(window);
	Init_colors();

	SDL_Event event;
	bool quit = false;
	Clear_field();
	test();
	while (quit == false) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		Draw_Game();
		SDL_UpdateWindowSurface(window);
		SDL_Delay(100);
	}

    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}