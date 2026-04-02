// #include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include <time.h>

constexpr int SCREEN_WIDTH = 1000;
constexpr int SCREEN_HEIGHT = 800;

constexpr int MAX_ITERATIONS = 0;

class ComplexNumber {
public:
	double r;
	double i;

	ComplexNumber(double r, double i) : r(r), i(i) {
	}

	operator+=(ComplexNumber& other) {
		_r += other.r;
		_i += other.i;
	}

	operator*=(ComplexNumber& other) {
		const auto newReal = r * other.r - i * other.i;
		_i = r * other.i + i * other.r;
		_r = newReal;
	}
};

class MandelbrotImage {

	int width;
	int height;

	ComplexNumber topLeft(-2.0, 2.0);
	ComplexNumber bottomRight(2.0, -2.0);

	int pixelCounter = 0;
	int x = 0;
	int y = 0;

public:
	MandelbrotImage(int width, int height) : width(width), height(height) {}

	advancePixel() {
		pixelCounter++;
		x = pixelCounter % width;
		y = pixelCounter / width;
	}

	inline bool isDone() {
		return y >= height;
	}
	
	ComplexNumber getNextNumber() {
		double dx = -x * getRealRange() / width;
		double dy = -y * getImaginaryRange() / height;
		ComplexNumber nextNumber(dx, dy);
		nextNumber += topLeft;
		return nextNumber;
	}

private:
	inline double getRealRange() {
		return bottomRight.r - topLeft.r;
	}

	inline double getImaginaryRange() {
		return topLeft.i - bottomRight.i;
	}
};


int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initilaize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	
	init_initial_game();

	screen_surface = SDL_GetWindowSurface(window);

	alive_color = SDL_MapRGB(screen_surface->format, 255, 255, 255);
	dead_color = SDL_MapRGB(screen_surface->format, 0, 0, 0);

	SDL_FillRect(screen_surface, NULL, dead_color);

	SDL_UpdateWindowSurface(window);

	MandelbrotImage mandelbrotImage(SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Event event;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		ComplexNumber c = mandelbrotImage.getNextNumber();
		int iterations = mandelbrot(c);
		if (iterations < MAX_ITERATIONS) {
			
		}

		SDL_UpdateWindowSurface(window);
		SDL_Delay(50);
	}
	
    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}