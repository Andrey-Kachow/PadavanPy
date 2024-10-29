// #include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Pixel length of one length unit (meter)
#define UNIT_SIZE 20 

#define CAMERA_X (SCREEN_WIDTH/2)
#define CAMERA_Y (SCREEN_HEIGHT/2)
#define HORIZONTAL_DIR_FACTOR 1
#define VERTICAL_DIR_FACTOR -1

static inline int drawable_x(float x) {
    return (HORIZONTAL_DIR_FACTOR * x * UNIT_SIZE) + CAMERA_X;
}

static inline int drawable_y(float y) {
    return (VERTICAL_DIR_FACTOR * y * UNIT_SIZE) + CAMERA_Y;
}

static inline int drawable_scale(float size) {
    return (UNIT_SIZE * size);
}

void Debug_print_rect(SDL_Rect *rect) {
    printf("{ %d, %d, %d, %d }\n", rect->x, rect->y, rect->w, rect->h);
}

void Game_draw_axis(SDL_Renderer *renderer) {
    float ax_half_thickness = 0.1;
    float ax_half_length = 10;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect hor_ax = {
        drawable_x(-ax_half_length),
        drawable_y(ax_half_thickness),
        drawable_scale(2 * ax_half_length),
        drawable_scale(2 * ax_half_thickness)
    };
    SDL_Rect ver_ax = {
        drawable_x(-ax_half_thickness),
        drawable_y(ax_half_length),
        drawable_scale(2 * ax_half_thickness),
        drawable_scale(2 * ax_half_length)
    };
    SDL_RenderFillRect(renderer, &hor_ax);
    SDL_RenderFillRect(renderer, &ver_ax);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect origin_rect = {
        drawable_x(-ax_half_thickness),
        drawable_y(ax_half_thickness),
        drawable_scale(2 * ax_half_thickness),
        drawable_scale(2 * ax_half_thickness)
    };
    SDL_RenderFillRect(renderer, &origin_rect);
    Debug_print_rect(&origin_rect);
}

struct Point {
    float x;
    float y;
};

struct SpaceShip {
    struct Point pos;
    float length;
    float width;
};

void SpaceShip_render(struct SpaceShip *spaceship, SDL_Renderer *renderer) {
    SDL_Vertex vert[3];
    vert[0].position.x = spaceship->pos.x;
    vert[0].position.y = spaceship->pos.y + spaceship->length;
}

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

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

	SDL_UpdateWindowSurface(window);

	SDL_Event event;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        Game_draw_axis(renderer);

        SDL_RenderPresent(renderer);
	}

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}