#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "asteroids.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SPACESHIP_SIZE 64
#define THRUST_POWER 1000
#define THRUST_POWER_ASTEROID 0.025
#define THRUST_POWER_BULLET 0.10
#define ROTATION_POWER 1000
#define TARGET_FPS 144.0
#define FRAME_DELAY (1000.0/TARGET_FPS)
#define COUNT_ASTEROIDS 7
#define DAMPING 0.999
#define BULLET_RADIUS 16
#define COLLISION_DEPTH 20

struct Spaceship {
    float x;
    float y;
    float vel_x;     // скорость
    float vel_y;
    float angle;     // угол
    float angle_vel; // скорость угла
    int life;
    enum SpaceshipState status;
    Uint32 destroy_time;
};

struct Bullet {
    float x;
    float y;
    float vel_x;
    float vel_y;
    float angle;
    float angle_vel;  
};

bool bullet_life = false;

struct Asteroid {
    float x;
    float y;
    float vel_x;
    float vel_y;
    float angle;
    float angle_vel; 
    int size;
};

enum SpaceshipState {Good, Recovery};
struct List *asteroids_list;
float radius[3] = {32, 64, 128}; // size
struct Spaceship spaceship;
struct Bullet bullet;
bool quit = false;

float cos_deg(float angle) {
    return cos(angle * ((2 * M_PI) / 360));
}

float sin_deg(float angle) {
    return sin(angle * ((2 * M_PI) / 360));
}

////////////////////////////////////////////////////////
void Spaceship_Init() {
    spaceship.x = 400;
    spaceship.y = 300;
    spaceship.vel_x = 0;
    spaceship.vel_y = 0;
    spaceship.angle = 0;
    spaceship.angle_vel = 0;
    spaceship.status = Good;
    spaceship.life = 3;
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
    bullet.vel_x = 450 * cos_deg(spaceship.angle);
    bullet.vel_y = 450 * sin_deg(spaceship.angle);
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
    if (spaceship.x > SCREEN_WIDTH + SPACESHIP_SIZE / 2) {
        spaceship.x = 0 - SPACESHIP_SIZE / 2;
    }
    if (spaceship.x < 0 - SPACESHIP_SIZE / 2) {
        spaceship.x = SCREEN_WIDTH + SPACESHIP_SIZE / 2;
    }
    if (spaceship.y > SCREEN_HEIGHT + SPACESHIP_SIZE / 2) {
        spaceship.y = 0 - SPACESHIP_SIZE / 2;
    }
    if (spaceship.y < 0 - SPACESHIP_SIZE / 2) {
        spaceship.y = SCREEN_HEIGHT + SPACESHIP_SIZE / 2;
    }
}

void Asteroid_process(struct Asteroid * asteroid, float delta_time) {
    asteroid->x += asteroid->vel_x * delta_time;
    asteroid->y += asteroid->vel_y * delta_time;
    asteroid->angle += asteroid->angle_vel * delta_time;
    if (asteroid->x > SCREEN_WIDTH + radius[asteroid->size]) {
        asteroid->x = 0 - radius[asteroid->size];
    }
    if (asteroid->x < 0 - radius[asteroid->size]) {
        asteroid->x = SCREEN_WIDTH + radius[asteroid->size];
    }
    if (asteroid->y > SCREEN_HEIGHT + radius[asteroid->size]) {
        asteroid->y = 0 - radius[asteroid->size];
    }
    if (asteroid->y < 0 - radius[asteroid->size]) {
        asteroid->y = SCREEN_HEIGHT + radius[asteroid->size];
    }
}

void Bullet_process(float delta_time) {
    bullet.x += bullet.vel_x * delta_time;
    bullet.y += bullet.vel_y * delta_time;
    bullet.angle += bullet.angle_vel * delta_time;
    if (bullet.x > SCREEN_WIDTH || bullet.x < 0 || bullet.y > SCREEN_HEIGHT || bullet.y < 0) {
        bullet_life = false;
    }
}

////////////////////////////////////////////////////////
void Asteroid_List_process(float delta_time) {
    for (struct List_elem * elem = asteroids_list->head; elem != NULL; elem = elem->next) {
        Asteroid_process(elem->asteroid, delta_time);
    }
}

////////////////////////////////////////////////////////
void Spaceship_rotate(float direction, float delta_time) {
    spaceship.angle_vel += direction * ROTATION_POWER * delta_time;\
    bullet.angle_vel = spaceship.angle_vel;
}

void Spaceship_thrust(float delta_time) {
    spaceship.vel_x += cos(spaceship.angle * ((2 * M_PI) / 360)) * THRUST_POWER * delta_time;
    spaceship.vel_y += sin(spaceship.angle * ((2 * M_PI) / 360)) * THRUST_POWER * delta_time;
}
////////////////////////////////////////////////////////
void Draw_spaceship(SDL_Texture * spaceship_texture, SDL_Renderer * renderer) {
    SDL_Rect destination = {  //destination.x = spaceship.x;
        spaceship.x - SPACESHIP_SIZE / 2, 
        spaceship.y - SPACESHIP_SIZE / 2,
        SPACESHIP_SIZE,
        SPACESHIP_SIZE 
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

void Draw_List_asteroids(SDL_Renderer * renderer, SDL_Texture * asteroid_texture) {
    for (struct List_elem * elem = asteroids_list->head; elem != NULL; elem = elem->next) {
        Draw_asteroid(elem->asteroid, renderer, asteroid_texture);
    }
}

void Draw_bullet(SDL_Texture * bullet_texture, SDL_Renderer * renderer) {
    SDL_Rect destination = {  //destination.x = spaceship.x;
        bullet.x - BULLET_RADIUS, 
        bullet.y - BULLET_RADIUS,
        2 * BULLET_RADIUS,
        2 * BULLET_RADIUS 
    };
    SDL_RenderCopyEx(renderer, bullet_texture, NULL, &destination, 90 + bullet.angle, NULL, SDL_FLIP_NONE);
}

void Draw_background(SDL_Texture * background_texture, SDL_Renderer * renderer) {
    SDL_Rect destination = {  
        0,
        0,
        SCREEN_WIDTH,
        SCREEN_HEIGHT 
    };
    SDL_RenderCopyEx(renderer, background_texture, NULL, &destination, 0, NULL, SDL_FLIP_NONE);
}

struct Asteroid * Spawn_asteroid(struct List_elem * prev) {
    struct Asteroid * asteroid = malloc(sizeof(struct Asteroid));
    Asteroid_Init(asteroid);
    if (prev == NULL) {
        List_append(asteroids_list, asteroid);
    } else {
        List_insert_after(asteroids_list, prev, asteroid);
    }
    return asteroid;
}

void Asteroid_split(struct List_elem * parent) {
    struct Asteroid * parent_asteroid = parent->asteroid;
    if (parent_asteroid->size == 0) {
        return;
    }
    printf("first");
    struct Asteroid * child1 = Spawn_asteroid(parent);
    printf("second");
    struct Asteroid * child2 = Spawn_asteroid(parent);
    printf("second created");
    child1->x = parent_asteroid->x;
    child1->y = parent_asteroid->y;
    // child1->vel_x = random_float(-150, 150);
    // child1->vel_y = random_float(-150, 150);
    
    float speed = random_float(100, 300);
    float rand_angle = random_float(-180, 180);
    child1->vel_x = cos_deg(rand_angle) * speed;
    child1->vel_y = sin_deg(rand_angle) * speed;

    child2->x = parent_asteroid->x;
    child2->y = parent_asteroid->y;
    child2->vel_x = -child1->vel_x;
    child2->vel_y = -child1->vel_y;

    child1->size = parent_asteroid->size - 1;
    child2->size = parent_asteroid->size - 1;
}

void Asteroid_collision() {
    struct List_elem * prev = NULL;
    for (struct List_elem * elem = asteroids_list->head; elem != NULL; elem = elem->next) {
        bool asteroid_destroy = false;
        if (bullet_life) {
            float dx = elem->asteroid->x - bullet.x;
            float dy = elem->asteroid->y - bullet.y;
            int summa = radius[elem->asteroid->size] + BULLET_RADIUS - COLLISION_DEPTH;
            if (summa * summa >= dx * dx + dy * dy) {
                printf("\n\n\n\nCOlision\n\n\n\n");
                bullet_life = false;
                asteroid_destroy = true;
            }    
        }
        if (spaceship.status == Good && spaceship.life > 0) {
            float dx = elem->asteroid->x - spaceship.x;
            float dy = elem->asteroid->y - spaceship.y;
            int summa = radius[elem->asteroid->size] + 32 - COLLISION_DEPTH;
            if (summa * summa >= dx * dx + dy * dy) {
                spaceship.destroy_time = SDL_GetTicks();
                spaceship.status = Recovery;
                asteroid_destroy = true;
                spaceship.life -= 1;
            }
        }
        if (asteroid_destroy == true) {
            Asteroid_split(elem);
            // удаление элемента списка
            if (elem == asteroids_list->head) {
                asteroids_list->head = elem->next;
                free(elem->asteroid);
                free(elem);
            } else {
                prev->next = elem->next;
                free(elem->asteroid);
                free(elem);
            }
        }
        prev = elem;
    }
}

////////////////////////////////////////////////////////

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
    SDL_Surface* background = SDL_LoadBMP("background.bmp");
    SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, background);
    SDL_Surface* spaceship_invis_image = SDL_LoadBMP("spaceship_transparent.bmp");
    SDL_Texture* spaceship_invis_texture = SDL_CreateTextureFromSurface(renderer, spaceship_invis_image);
    SDL_Surface* spaceship_image = SDL_LoadBMP("spaceship.bmp");
    SDL_Texture* spaceship_texture = SDL_CreateTextureFromSurface(renderer, spaceship_image);
    SDL_Surface* asteroid_image = SDL_LoadBMP("asteroid.bmp");
    SDL_Texture* asteroid_texture = SDL_CreateTextureFromSurface(renderer, asteroid_image);
    SDL_Surface* bullet_image = SDL_LoadBMP("bullet.bmp");
    SDL_Texture* bullet_texture = SDL_CreateTextureFromSurface(renderer, bullet_image);

    struct Asteroid asteroids[COUNT_ASTEROIDS];
    // for (int i=0; i!=COUNT_ASTEROIDS; i++) {
    //     Asteroid_Init(&asteroids[i]);
    // }
	SDL_Event event;
    Spaceship_Init();


    Uint32 frame_last_time = SDL_GetTicks();
    // render cycle

    Uint8 *keyState = SDL_GetKeyboardState(NULL);
    asteroids_list = List_create();
    Spawn_asteroid(NULL);


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
                    Bullet_Init();
                    bullet_life = true;
                    printf("SPACE");
                }
            }
		}
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Обновляем игровые объекты
        Spaceship_process(delta_time);
        if (spaceship.status == Recovery) {
            int recovery_elapse = frame_start - spaceship.destroy_time; 
            if (recovery_elapse > 3000) {
                spaceship.status = Good;
            }
        }
        Bullet_process(delta_time);
        Asteroid_List_process(delta_time);
        Asteroid_collision();
        
        // Рисуем
        Draw_background(background_texture, renderer);
        if (bullet_life == true) {
            Draw_bullet(bullet_texture, renderer);
        }
        if (spaceship.life > 0) {
            if (spaceship.status == Recovery) {
                Draw_spaceship(spaceship_invis_texture, renderer);
            } else {
                Draw_spaceship(spaceship_texture, renderer);
            }
        }
        Draw_List_asteroids(renderer, asteroid_texture);
        SDL_RenderPresent(renderer);

        // Регулировка FPS
        Uint32 frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frame_time); 
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
    SDL_Quit();

    return 0; // дз Сделать индикатор здоровья коробля, без использования текста (картинками), поверх всех элементов(последними)
    // по желанию после проигрыша делатьо черное сердце, bmp, в ряд. 
}