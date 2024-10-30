#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define THRUST_POWER 0.01
#define ROTATION_POWER 0.1
#define TARGET_FPS 144.0
#define FRAME_DELAY (1000.0/TARGET_FPS)

struct Spaceship {
    float x;
    float y;
    float vel_x;     // скорость
    float vel_y;
    float angle;     // угол
    float angle_vel; // скорость угла
};
struct Spaceship spaceship;


bool quit = false;

void Spaceship_Init() {
    spaceship.x = 400;
    spaceship.y = 300;
    spaceship.vel_x = 0;
    spaceship.vel_y = 0;
    spaceship.angle = 0;
    spaceship.angle_vel = 0;
}

void Spaceship_process() {
    spaceship.x += spaceship.vel_x;
    spaceship.y += spaceship.vel_y;
    spaceship.angle += spaceship.angle_vel;
}

void Spaceship_rotate(float direction) {
    spaceship.angle_vel += direction * ROTATION_POWER;
}

void Spaceship_thrust() {
    spaceship.vel_x += cos(spaceship.angle * ((2 * M_PI) / 360)) * THRUST_POWER;
    spaceship.vel_y += sin(spaceship.angle * ((2 * M_PI) / 360)) * THRUST_POWER;
}

void Draw_spaceship(SDL_Texture * spaceship_texture, SDL_Renderer * renderer) {
    SDL_Rect destination = {  //destination.x = spaceship.x;
        spaceship.x - 32, 
        spaceship.y - 32,
        64,
        64 
    };
    SDL_RenderCopyEx(renderer, spaceship_texture, NULL, &destination, 90 + spaceship.angle, NULL, SDL_FLIP_NONE);
    
}

int main(int argc, int *argv[]) {
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

	// if (TTF_Init() != 0) {
	// 	printf("Could not initialize text! SDL_Error: %s\n", SDL_GetError());
	// 	return 1;
	// }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* spaceship_image = SDL_LoadBMP("spaceship.bmp");
    SDL_Texture* spaceship_texture = SDL_CreateTextureFromSurface(renderer, spaceship_image);
    
	SDL_Event event;
	srand(time(NULL));
    Spaceship_Init();

    // render cycle
    while (quit == false) {
        Uint32 frame_start = SDL_GetTicks();
		
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
				quit = true;
			}
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    Spaceship_thrust();
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    Spaceship_rotate(-1);
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                    Spaceship_rotate(1);
                }
            }
            
		}
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Обновляем игровые объекты
        Spaceship_process();
        
        // Рисуем
        Draw_spaceship(spaceship_texture, renderer);

        SDL_RenderPresent(renderer);

        // Регулировка FPS
        Uint32 frame_time = SDL_GetTicks() - frame_start; // каждую секунду новый астеройд
        if (frame_time < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frame_time); //дз сделать астеройд, чтобы он дрейфил в космосе случайно каждый раз
        }
	}

    SDL_DestroyTexture(spaceship_texture);
    SDL_FreeSurface(spaceship_image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}