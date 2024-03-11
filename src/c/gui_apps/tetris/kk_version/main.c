// cl.exe /Zi /I "D:\c_dev_libraries\SDL2-2.28.5\include" main.c /link "D:\c_dev_libraries\SDL2-2.28.5\lib\x86\SDL2main.lib" "D:\c_dev_libraries\SDL2-2.28.5\lib\x86\SDL2.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x86\shell32.lib" /SUBSYSTEM:WINDOWS

// #include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include <time.h>

#include <SDL_TTF.h>

// Base Units
#define SQUARE 6
#define PADDING 40
#define GAME_WIDTH 22
#define GAME_HEIGHT 30
#define BORDER_WIDTH 2
#define EMPTY_CELL_COLOR_INDEX 7
#define MOTION_RATE 3
#define PANEL_WIDTH 400
#define DANGER_ZONE_Y 3
#define SCORE_BOX 120

// UI elements dimensions
#define FIELD_HEIGHT_PX (GAME_HEIGHT*(SQUARE+BORDER_WIDTH)+BORDER_WIDTH) 
#define FIELD_WIDTH_PX (GAME_WIDTH*(SQUARE+BORDER_WIDTH)+BORDER_WIDTH)

#define SCREEN_WIDTH (FIELD_WIDTH_PX+3*PADDING+PANEL_WIDTH) 
#define SCREEN_HEIGHT (FIELD_HEIGHT_PX+2*PADDING)

// UI elements positions
#define PANEL_X (SCREEN_WIDTH - PADDING - PANEL_WIDTH)
#define PANEL_Y PADDING
#define BOX_X (PANEL_X + PADDING)
#define BOX_Y (PANEL_Y + PADDING)


SDL_Surface *screen_surface = NULL;

struct point {
	int x;
	int y;
};

struct point shapes[7][4][4] = {
	{
		{{0, 0}, {0, -1}, {0, 1}, {1, 1}}, // L_shape_Right 45 
		{{0, 0}, {1, 0}, {-1, 0}, {-1, 1}}, // L_shape_Right 90 
		{{0, 0}, {0,-1}, {0, 1}, {-1, -1}}, // L_shape_Right 135 
		{{0, 0}, {-1, 0}, {1, 0}, {1, -1}}, // L_shape_Right 180 
	},
	{
		{{0, 0}, {0,-1}, {-1,-1}, {-1,0}}, // square_shape 45 
		{{0, 0}, {0, 1}, {1,1}, {1,0}}, // square_shape 90 
		{{0, 0}, {0,-1}, {-1,-1}, {-1,0}}, // square_shape 135 
		{{0, 0}, {1, 0}, {1, 1}, {0, 1}}, // square_shape 180 
	},
	{	
		{{0, 0}, {0, 1}, {0, 2}, {0, -1}}, // I_shape 45 
		{{0, 0}, {-1, 0}, {1, 0}, {2, 0}}, // I_shape 90 
		{{0, 0}, {0, -1}, {0, -2}, {0, 1}}, // I_shape 135 
		{{0, 0}, {-2, 0}, {-1, 0}, {1, 0}}, // I_shape 180 
	},
	{
		{{0, 0}, {0,1}, {0, -1}, {-1, 1}}, // L_shape_LEFT 45 
		{{0, 0}, {-1, 0}, {1, 0}, {-1, -1}}, // L_shape_LEFT 90 
		{{0, 0}, {0, 1}, {0, -1}, {1, -1}}, // L_shape_LEFT 135 
		{{0, 0}, {1, 0}, {-1, 0}, {1, 1}}, // L_shape_LEFT 180 
	},
	{
		{{0, 0}, {1, 0}, {0, -1}, {1, 1}}, // S_shape 45
		{{0, 0}, {1, 0}, {0, 1}, {-1, 1}}, // S_shape 180
		{{0, 0}, {1, 0}, {0, -1}, {1, 1}}, // S_shape 45
		{{0, 0}, {1, 0}, {0, 1}, {-1, 1}}, // S_shape 180
	},
	{
		{{0, 0}, {1, 0}, {1, -1}, {0, 1}}, // Z_shape 45
		{{0, 0}, {1, 0}, {0, -1}, {-1, -1}}, // Z_shape 135
		{{0, 0}, {1, 0}, {1, -1}, {0, 1}}, // Z_shape 45
		{{0, 0}, {1, 0}, {0, -1}, {-1, -1}}, // Z_shape 135
	},
	{
		{{0, 0}, {-1, 0}, {-1, -1}, {-1, 1}}, //T_shape 45
		{{0, 0}, {1, 0}, {1, 1}, {1, -1}}, //T_shape 90
		{{0, 0}, {-1, -1}, {0, -1}, {1, -1}}, //T_shape 135
		{{0, 0}, {1, 1}, {0, 1}, {-1, 1}} //T_shape 180
	}
};

/*
		{{0, 0}, {1, 0}, {0, -1}, {1, 1}}, // Z_shape 45

*/

int score = 0;
Uint32 primary_color;
Uint32 secondary_color;
Uint32 panel_color;
Uint32 cell_colors[8];
Uint32 empty_cell_color;
Uint32 Field[GAME_HEIGHT][GAME_WIDTH];
bool quit = false;
Uint32 top_color;

void string_to_int(char * word, int value) {
	if (value == 0) {
        word[0] = '0';
        word[1] = '\0';
        return;
    }
	word[32] = '\0';
	int current_position = 31;
	while (value != 0) {
		word[current_position] = value;
	}
	current_position -= 1;
	value /= 2;
}

void internal_place_shape(int shape_id, int x, int y, int rotating, int px_offset_x, int px_offset_y) {
	int destination_x;
	int destination_y;
	SDL_Rect drawable;
	drawable.h = SQUARE;
	drawable.w = SQUARE;
	for (int count = 0; count < 4; count++) {
		struct point cell = shapes[shape_id][rotating][count];
		destination_y = y + cell.y;
		destination_x = x + cell.x;
		int draw_x = game_coordinate_to_graphics_coordinate(destination_x);
		int draw_y = game_coordinate_to_graphics_coordinate(destination_y);
		drawable.x = draw_x + px_offset_x;
		drawable.y = draw_y + px_offset_y;
		
		SDL_FillRect(screen_surface, &drawable, cell_colors[shape_id]); //............................................
	}
}

void Place_Shape(int shape_id, int x, int y, int rotating) {
	internal_place_shape(shape_id, x, y, rotating, 0, 0);
}

void Draw_next_shape(int shape_id, int rotating) {
	int x = 0;
	int y = 0;
	int px_offset_x = BOX_X - PADDING + SCORE_BOX/2 - (SQUARE + BORDER_WIDTH)/2;
	int px_offset_y = BOX_Y - PADDING + SCORE_BOX/2 - (SQUARE + BORDER_WIDTH)/2;

	internal_place_shape(shape_id, x, y, rotating, px_offset_x, px_offset_y);
}

/*
	Mark Field Array Elements that correspond to cells in a shape as Active.
*/
void Place_freeze_Shape(int shape_id, int x, int y, int rotating) {
	int destination_x;
	int destination_y;
	for (int count = 0; count < 4; count++) {
		struct point cell = shapes[shape_id][rotating][count];
		destination_y = y + cell.y;
		destination_x = x + cell.x;
		Field[destination_y][destination_x] = cell_colors[shape_id];
	}
}

int game_coordinate_to_graphics_coordinate(int x_or_y) {
	return PADDING + BORDER_WIDTH + x_or_y * (SQUARE+BORDER_WIDTH);
}


int active_shape_id = -1;
int active_x = 0;
int active_y = 0;
int active_orentation = 0;
int next_shape_id = -1;
int next_orentation = 0;
int game_time = 0;
int next_move = MOTION_RATE;



bool collides(int delta_x, int delta_y, int delta_rotation) {
	int shape_element_x;
	int shape_element_y;
	int actual_orentation = active_orentation + delta_rotation;
	actual_orentation %= 4;
	for (int count = 0; count < 4; count++) {
		struct point cell = shapes[active_shape_id][actual_orentation][count];
		shape_element_y = active_y + cell.y + delta_y;
		shape_element_x = active_x + cell.x + delta_x;
		if (shape_element_y >= GAME_HEIGHT) {
			return true;
		}
		if (shape_element_x >= GAME_WIDTH || shape_element_x < 0) {
			return true;
		}
		if (Field[shape_element_y][shape_element_x] != cell_colors[EMPTY_CELL_COLOR_INDEX]) {
			return true;
		}
	}
	return false;
}

void Drop_shapes(int y) {
	int count = 0;
	for (int i=y;i>0;i--) {
		for (int j=0;j<GAME_WIDTH;j++) {
			int temp = Field[i][j];
			Field[i][j] = Field[i-1][j];
			Field[i-1][j] = temp;
		}
	}
}

double factorial(int n) {
	int count = 1;
	double product = 1;
	while (count <= n) {
		product *= count;
		count += 1;
	}
	// printf("%d! = %f\n", n, product);
	return product;
}

void Destroy_complete_rows() {
	int count = 0;
	for (int i=0;i<GAME_HEIGHT;i++) {
		int empty_counter = 0;
		for (int j=0;j<GAME_WIDTH;j++) {
			if (Field[i][j] == cell_colors[EMPTY_CELL_COLOR_INDEX]) {
				empty_counter += 1;		
			} 
		}
		if (empty_counter < 1) {
			for (int j=0;j<GAME_WIDTH;j++) {
				Field[i][j] = cell_colors[EMPTY_CELL_COLOR_INDEX];
			}
			count += 1;
			Drop_shapes(i);
		}
	}
	int score_bonus = 0;



	/*
		count  |  score_bonus
		-------+------------- 
			1  |   200           200 * count
			2  |   400           200 * count * (count - 1)
			3  |   1200			 200 * count * (count - 1) * (count - 2)
			4  |   4800          200 * count * (count - 1) * (count - 2) * (count - 3)

			n  |   200 * n!

			n! = n * (n - 1) * (n - 2) ... * 2 * 1
			1! = 1
	*/

	if (1 <= count) {
		score_bonus = 200 * factorial(count);
	}
	
	score += score_bonus;
	printf("%d ", score);
}


void Draw_active_shape() {
	if (game_time >= next_move) {
		if (collides(0, 1, 0)) {
			Place_freeze_Shape(active_shape_id, active_x, active_y, active_orentation);
			Destroy_complete_rows();
			active_shape_id = -1;
		} else {
			active_y += 1;
			next_move += MOTION_RATE;
		}
	}
	if (active_shape_id == -1) {
		active_shape_id = rand()%7;
		active_orentation = rand()%4;
		active_x = GAME_WIDTH/2;
		active_y = 2;
		next_shape_id = rand()%7;
		next_orentation = rand()%4;
	}
	if (Field[active_y][active_x] != cell_colors[EMPTY_CELL_COLOR_INDEX]) {
		quit = true;
	}	
	Place_Shape(active_shape_id, active_x, active_y, active_orentation);
	Draw_next_shape(next_shape_id, next_orentation);
}

/**
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
*/

void Clear_field() {
	for (int i=0;i<GAME_HEIGHT;i++) {
		for (int j=0;j<GAME_WIDTH;j++) {
			Field[i][j] = cell_colors[EMPTY_CELL_COLOR_INDEX];
		}
	}
}

// void test() {
// 	Clear_field();
// 	for (int j=1;j<GAME_WIDTH;j++) {
// 		Field[GAME_HEIGHT-1][j] = cell_colors[0];
// 	}
// }

void test() {
	Clear_field();
	for (int j=1;j<GAME_WIDTH;j++) {
		Field[GAME_HEIGHT-6][j] = cell_colors[0];
		Field[GAME_HEIGHT-5][j] = cell_colors[0];
		Field[GAME_HEIGHT-4][j] = cell_colors[0];
		Field[GAME_HEIGHT-3][j] = cell_colors[0];
		Field[GAME_HEIGHT-2][j] = cell_colors[0];
		Field[GAME_HEIGHT-1][j] = cell_colors[0];
	}
}

// void test() {
// 	for (int shape_id = 0; shape_id < 7; shape_id++) {
// 		for (int orentation = 0; orentation < 4; orentation++) {
// 			int x = 5 * orentation + 5;
// 			int y = 5 * shape_id + 5;
// 			Place_Shape(shape_id, x, y, orentation);
// 		}
// 	}
	
// }

void Init_colors() {
	primary_color = SDL_MapRGB(screen_surface->format, 0, 0, 0);
	secondary_color = SDL_MapRGB(screen_surface->format, 82, 42, 2);
	panel_color = SDL_MapRGB(screen_surface-> format, 230, 121, 11);
	cell_colors[0] = SDL_MapRGB(screen_surface-> format, 224, 142, 7);
	cell_colors[1] = SDL_MapRGB(screen_surface-> format, 222, 12, 12);
	cell_colors[2] = SDL_MapRGB(screen_surface-> format, 204, 38, 230);
	cell_colors[3] = SDL_MapRGB(screen_surface-> format, 32, 84, 168);
	cell_colors[4] = SDL_MapRGB(screen_surface-> format, 35, 209, 104);
	cell_colors[5] = SDL_MapRGB(screen_surface-> format, 179, 84, 118);
	cell_colors[6] = SDL_MapRGB(screen_surface-> format, 52, 84, 118);
	cell_colors[7] = SDL_MapRGB(screen_surface-> format, 87, 78, 65);
	top_color = SDL_MapRGB(screen_surface-> format, 133, 47, 25);
}

void Draw_ScoreText() {
	TTF_Font* font = TTF_OpenFont("DejaVuSansMono.ttf", 12);
	
	SDL_Color foregroundColor = { 0, 0, 0 };
	SDL_Color backgroundColor = { 255, 255, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "hello", foregroundColor, backgroundColor);
	SDL_Rect textLocation = { PANEL_X + 100, PANEL_Y + 100, 100, 100 };
	SDL_BlitSurface(textSurface, NULL, screen_surface, &textLocation);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
}

void Draw_Panel() {
	SDL_Rect inner;
	inner.w = PANEL_WIDTH;
	inner.h = FIELD_HEIGHT_PX;
	inner.x = PANEL_X;
	inner.y = PANEL_Y;

	SDL_Rect next_shape_box = { inner.x + PADDING, inner.y + PADDING, SCORE_BOX, SCORE_BOX };

	SDL_FillRect(screen_surface, &inner, panel_color);
	SDL_FillRect(screen_surface, &next_shape_box, top_color);

	Draw_ScoreText();

}

void Draw_Game() {
	SDL_FillRect(screen_surface, NULL, secondary_color);
	Draw_Panel();

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
			SDL_FillRect(screen_surface, &cell, Field[i][j]);
			if (i < DANGER_ZONE_Y && cell_colors[EMPTY_CELL_COLOR_INDEX] == Field[i][j]) {
				SDL_FillRect(screen_surface, &cell, top_color);
			}
		}
	}
	// while??
}


bool right_press = false;
bool left_press = false;
bool rotate_press = false;
bool down_press = false;

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

	if (TTF_Init() != 0) {
		printf("Could not initialize text! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	screen_surface = SDL_GetWindowSurface(window);

	SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 255, 255, 255));

	SDL_UpdateWindowSurface(window);
	Init_colors();

	SDL_Event event;
	srand(time(NULL));
	// Clear_field();
	test();
	while (quit == false) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_LEFT && !left_press) {
					if (!collides(-1, 0, 0)) {
						active_x -= 1;
						left_press = true;
					}
				} else if (event.key.keysym.sym == SDLK_RIGHT && !right_press) {
					if (!collides(1, 0, 0)) {
						active_x += 1;
						right_press = true;
					}
				} else if (event.key.keysym.sym == SDLK_SPACE && !rotate_press) {
					if (!collides(0, 0, 1)) {
						active_orentation += 1;
						active_orentation %= 4;
						rotate_press = true; 
					}
				} else if (event.key.keysym.sym == SDLK_DOWN && !down_press) {
					if (!collides(0, 1, 0)) {
						active_y += 1;
						down_press = true; 
					}
				}
			}
			if (event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_LEFT) {
					left_press = false;
				} else if (event.key.keysym.sym == SDLK_RIGHT) {
					right_press = false;
				} else if (event.key.keysym.sym == SDLK_SPACE) {
					rotate_press = false;
				} else if (event.key.keysym.sym == SDLK_DOWN) {
					down_press = false;
				}
			}
		}
		Draw_Game();
		Draw_active_shape();
		SDL_UpdateWindowSurface(window);
		// printf("%d", score);
		SDL_Delay(100);
		game_time += 1;
	}

    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}