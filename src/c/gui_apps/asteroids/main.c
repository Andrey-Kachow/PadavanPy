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

#define TIME_DELTA 0.001

static inline int drawable_x(float x) {
    return (HORIZONTAL_DIR_FACTOR * x * UNIT_SIZE) + CAMERA_X;
}

static inline int drawable_y(float y) {
    return (VERTICAL_DIR_FACTOR * y * UNIT_SIZE) + CAMERA_Y;
}

static inline int drawable_scale(float size) {
    return (UNIT_SIZE * size);
}

float random_float(float min, float max) {
    float range_width = max - min;
    float random_value = ((float)rand()/(float)(RAND_MAX)) * range_width;
    return min + random_value;
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
}

struct Point {
    float x;
    float y;
    float speed_x;
    float speed_y;
};

struct SpaceShip {
    struct Point pos;
    float length;
    float width;
};

struct Asteroid {
    struct Point pos;
    float radius;
    float angle;
    float rot_speed;
};

void SpaceShip_render(struct SpaceShip *spaceship, SDL_Renderer *renderer) {
}

void Asteroid_render(SDL_Renderer *renderer, SDL_Texture *asteroid_texure, struct Asteroid *asteroid) {
    SDL_Rect dst;
    dst.x = drawable_x(asteroid->pos.x - asteroid->radius);
    dst.y = drawable_y(asteroid->pos.y - asteroid->radius);
    dst.w = drawable_scale(asteroid->radius * 2);
    dst.h = dst.w;
    Debug_print_rect(&dst);
    printf("%f\n", asteroid->radius);
    SDL_RenderCopyEx(renderer, asteroid_texure, NULL, &dst, asteroid->angle, NULL, SDL_FLIP_NONE);
}

void Asteroid_process(struct Asteroid * asteroid) {
    asteroid->pos.x += asteroid->pos.speed_x * TIME_DELTA;
    asteroid->pos.y += asteroid->pos.speed_y * TIME_DELTA;
    asteroid->angle += asteroid->rot_speed * TIME_DELTA;
}

// void Asteroids_draw(SDL_Renderer *renderer, SDL_Texture *asteroid_texure, struct Asteroid *asteroids, int num_asteroids) {
//     for (int i = 0; i < num_asteroids; i++) {
//         Asteroid_render(renderer, asteroid_texure, asteroids + i);
//     }
// }

int main(int argc, char *argv[]) {
    srand(time());

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


    SDL_Surface* asteroid_image = SDL_LoadBMP("asteroid.bmp");
    SDL_Texture* asteroid_texure = SDL_CreateTextureFromSurface(renderer, asteroid_image);

    // Random Asteroids
    //
    struct Asteroid roid = {
        { 
            random_float(-10, 10),
            random_float(-10, 10),
            random_float(-2, 2),
            random_float(-2, 2)
        },
        random_float(1, 5),
        random_float(0, 359),
        random_float(-10, 10)
    };   

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
        Asteroid_render(renderer, asteroid_texure, &roid);
        Asteroid_process(&roid);

        SDL_RenderPresent(renderer);
	}

    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(asteroid_texure);
    SDL_FreeSurface(asteroid_image);
    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}