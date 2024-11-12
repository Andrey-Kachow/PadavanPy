#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define THRUST_POWER 1000
#define THRUST_POWER_ASTEROID 0.025
#define THRUST_POWER_BULLET 0.10
#define ROTATION_POWER 1000
#define TARGET_FPS 144.0
#define FRAME_DELAY (1000.0/TARGET_FPS)
#define COUNT_ASTEROIDS 7
#define DAMPING 0.999

struct Spaceship {
    float x;
    float y;
    float vel_x;     // скорость
    float vel_y;
    float angle;     // угол
    float angle_vel; // скорость угла
};

struct Bullet {
    float x;
    float y;
    float vel_x;
    float vel_y;
    float angle;
    float angle_vel;  
};

struct Asteroid {
    float x;
    float y;
    float vel_x;
    float vel_y;
    float angle;
    float angle_vel; 
    int size;
};

float radius[3] = {32, 64, 128}; // size
struct Spaceship spaceship;
struct Asteroid asteroid;
struct Bullet bullet;
bool quit = false;

////////////////////////////////////////////////////////
void Spaceship_Init() {
    spaceship.x = 400;
    spaceship.y = 300;
    spaceship.vel_x = 0;
    spaceship.vel_y = 0;
    spaceship.angle = 0;
    spaceship.angle_vel = 0;
}

float random_float(float min, float max) {
    float width = max-min;
    return (float)rand() / ((float)(RAND_MAX / width)) + min;
}

void Asteroid_Init(struct Asteroid * asteroid) {
    asteroid->x = rand() % (SCREEN_WIDTH - 1 + 1) + 1;
    asteroid->y = rand() % (SCREEN_HEIGHT - 1 + 1) + 1;
    asteroid->vel_x = random_float(-50, 50);
    asteroid->vel_y = random_float(-50, 50);
    asteroid->angle = random_float(-M_PI, M_PI);
    asteroid->angle_vel = random_float(-M_PI, M_PI);
    asteroid->size = rand() % 3;
}

void Bullet_Init() {
    bullet.x = spaceship.x;
    bullet.y = spaceship.y;
    bullet.vel_x = 50;   
    bullet.vel_y = 50;   
    bullet.angle = spaceship.angle;
    bullet.angle_vel = spaceship.angle_vel;
}

////////////////////////////////////////////////////////
void Spaceship_process(float delta_time) {
    spaceship.x += spaceship.vel_x * delta_time;
    spaceship.vel_x *= DAMPING;
    spaceship.y += spaceship.vel_y * delta_time;
    spaceship.vel_y *= DAMPING;
    spaceship.angle += spaceship.angle_vel * delta_time;
    spaceship.angle_vel *= DAMPING;
}

void Asteroid_process(struct Asteroid * asteroid, float delta_time) {
    asteroid->x += asteroid->vel_x * delta_time;
    asteroid->y += asteroid->vel_y * delta_time;
    asteroid->angle += asteroid->angle_vel * delta_time;
}

void Bullet_process(float delta_time) {
    bullet.x += bullet.vel_x * delta_time;
    bullet.y += bullet.vel_y * delta_time;
    bullet.angle += bullet.angle_vel * delta_time;
}

////////////////////////////////////////////////////////
void Spaceship_rotate(float direction, float delta_time) {
    spaceship.angle_vel += direction * ROTATION_POWER * delta_time;
}

void Spaceship_thrust(float delta_time) {
    spaceship.vel_x += cos(spaceship.angle * ((2 * M_PI) / 360)) * THRUST_POWER * delta_time;
    spaceship.vel_y += sin(spaceship.angle * ((2 * M_PI) / 360)) * THRUST_POWER * delta_time;
}
////////////////////////////////////////////////////////
void Draw_spaceship(SDL_Texture * spaceship_texture, SDL_Renderer * renderer) {
    SDL_Rect destination = {  //destination.x = spaceship.x;
        spaceship.x - 32, 
        spaceship.y - 32,
        64,
        64 
    };
    SDL_RenderCopyEx(renderer, spaceship_texture, NULL, &destination, 90 + spaceship.angle, NULL, SDL_FLIP_NONE);
}

void Draw_asteroid(struct Asteroid * asteroid, SDL_Renderer * renderer, SDL_Texture * asteroid_texture) {
    SDL_Rect destination = {  //destination.x = spaceship.x;
        asteroid->x - radius[asteroid->size], 
        asteroid->y - radius[asteroid->size],
        radius[asteroid->size] * 2,
        radius[asteroid->size] * 2
    };
    SDL_RenderCopyEx(renderer, asteroid_texture, NULL, &destination, 90 + asteroid->angle, NULL, SDL_FLIP_NONE);
}

void Draw_bullet(SDL_Texture * bullet_texture, SDL_Renderer * renderer) {
    SDL_Rect destination = {  //destination.x = spaceship.x;
        bullet.x - 16, 
        bullet.y - 16,
        32,
        32 
    };
    SDL_RenderCopyEx(renderer, bullet_texture, NULL, &destination, 90 + bullet.angle, NULL, SDL_FLIP_NONE);
}
////////////////////////////////////////////////////////

bool bullet_life = false;

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

	srand(time(NULL));
    SDL_Surface* spaceship_image = SDL_LoadBMP("spaceship.bmp");
    SDL_Texture* spaceship_texture = SDL_CreateTextureFromSurface(renderer, spaceship_image);
    SDL_Surface* asteroid_image = SDL_LoadBMP("asteroid.bmp");
    SDL_Texture* asteroid_texture = SDL_CreateTextureFromSurface(renderer, asteroid_image);
    SDL_Surface* bullet_image = SDL_LoadBMP("bullet.bmp");
    SDL_Texture* bullet_texture = SDL_CreateTextureFromSurface(renderer, bullet_image);

    struct Asteroid asteroids[COUNT_ASTEROIDS];
    for (int i=0; i!=COUNT_ASTEROIDS; i++) {
        Asteroid_Init(&asteroids[i]);
    }
	SDL_Event event;
    Spaceship_Init();
    // Bullet_Init();   //    ########### Не нужно. Пуля появляется только, когда игрок стреляет

    Uint32 frame_last_time = SDL_GetTicks();
    // render cycle

    Uint8 *keyState = SDL_GetKeyboardState(NULL);

    while (quit == false) {
        Uint32 frame_start = SDL_GetTicks();
        float delta_time = (frame_start - frame_last_time) / 1000.0;
        frame_last_time = frame_start;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
				quit = true;
			}
            // if (event.type == SDL_KEYDOWN) {
            //     if (event.key.keysym.sym == SDLK_UP) {
            //         Spaceship_thrust(delta_time);
            //         printf("FORWARD");
            //     }
            //     if (event.key.keysym.sym == SDLK_LEFT) {
            //         Spaceship_rotate(-1, delta_time);
            //         printf("LEFT");
            //     }
            //     if (event.key.keysym.sym == SDLK_RIGHT) {
            //         Spaceship_rotate(1, delta_time);
            //         printf("RIGHT");
            //     }
            // }
            if (keyState[SDL_SCANCODE_UP]) {
                Spaceship_thrust(delta_time);
                printf("FORWARD");
            }
            if (keyState[SDL_SCANCODE_LEFT]) {
                Spaceship_rotate(-1, delta_time);
                printf("LEFT");
            }
            if (keyState[SDL_SCANCODE_RIGHT]) {
                Spaceship_rotate(1, delta_time);
                printf("RIGHT");
            }
            if (keyState[SDL_SCANCODE_SPACE]) {
                if (bullet_life == false) {
                    Bullet_Init();                // ##### Инициализания пули в момент выстрела
                    // Draw_bullet(bullet_texture, renderer);   ##### Рисование пули происходит на каждом кадре. Нет необходимости рисовать еще раз в момент нажатия
                    bullet_life = true;
                    printf("SPACE");
                }
            }
		}
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Обновляем игровые объекты
        Spaceship_process(delta_time);
        Bullet_process(delta_time);
        for (int i=0; i!=COUNT_ASTEROIDS; i++) {
            Asteroid_process(&asteroids[i], delta_time);
        }
        
        // Рисуем
        if (bullet_life) { // ##### Рисование пули происходит при условии, что пуля существует
            Draw_bullet(bullet_texture, renderer);
        }
        Draw_spaceship(spaceship_texture, renderer);
        for (int i=0; i!=COUNT_ASTEROIDS; i++) {
            Draw_asteroid(&asteroids[i], renderer, asteroid_texture);
        }
        SDL_RenderPresent(renderer);

        // Регулировка FPS
        Uint32 frame_time = SDL_GetTicks() - frame_start; // каждую секунду новый астеройд
        if (frame_time < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frame_time); //дз сделать астеройд, чтобы он дрейфил в космосе случайно каждый раз
        }
	}

    SDL_DestroyTexture(spaceship_texture);
    SDL_DestroyTexture(asteroid_texture);
    SDL_DestroyTexture(bullet_texture);
    SDL_FreeSurface(spaceship_image);
    SDL_FreeSurface(asteroid_image);
    SDL_FreeSurface(bullet_image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // дз сделать пули(пулю) можно выстреливать, летит с постояннойц скоросте с направлением выстрела
    // не можем выпускать пулю пока не исчезнет старая

    return 0;
}