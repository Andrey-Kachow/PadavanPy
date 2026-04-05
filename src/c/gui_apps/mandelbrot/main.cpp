// #include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include <time.h>

#include <iostream>

constexpr int SCREEN_WIDTH = 1500;
constexpr int SCREEN_HEIGHT = 900;

constexpr int MAX_ITERATIONS = 65;

class ComplexNumber {
public:
	double r;
	double i;

	ComplexNumber(double r, double i) : r(r), i(i) {
	}

	void operator+=(ComplexNumber& other) {
		r += other.r;
		i += other.i;
	}

	void operator*=(ComplexNumber& other) {
		const auto newReal = r * other.r - i * other.i;
		i = r * other.i + i * other.r;
		r = newReal;
	}
};

class MandelbrotImage {

	int width;
	int height;

	ComplexNumber topLeft = { -1.8, 0.9 };
	ComplexNumber bottomRight = { 0.45, -0.9 };

	int pixelCounter = 0;

public:
	int x = 0;
	int y = 0;

	MandelbrotImage(int width, int height) : width(width), height(height) {}

	void advancePixel() {
		pixelCounter++;
		x = pixelCounter % width;
		y = pixelCounter / width;
	}

	inline bool isDone() {
		return y >= height;
	}
	
	ComplexNumber getNextNumber() {
		double dx = x * getRealRange() / width;
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

/*
	x' - x^2 + c
*/
int mandelbrot(ComplexNumber& c) {
	ComplexNumber x = c;
	int iterationCounter = 0;
	while (x.r * x.r + x.i * x.i <= 4.0 && iterationCounter < MAX_ITERATIONS) {
		x *= x;
		x += c;
		iterationCounter++;
	}
	return iterationCounter;
}

SDL_Window* window;
SDL_Renderer* renderer;

void updateRenderedColour(int iterations) {
	int r, g, b;	
	if (iterations == MAX_ITERATIONS) {
    	r = g = b = 0;
	} else {
		// double smooth = iterations + 1 - log(log(abs(z))) / log(2.0);
		double t = iterations / (double)MAX_ITERATIONS;

		r = (Uint8)(9 * (1 - t) * t * t * t * 255);
		g = (Uint8)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (Uint8)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initilaize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}
	
	MandelbrotImage mandelbrotImage(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	int frameCount = 0;
	SDL_Event event;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		if (mandelbrotImage.isDone()) {
			SDL_Delay(50);
			continue;
		}
		
		ComplexNumber c = mandelbrotImage.getNextNumber();
		int iterations = mandelbrot(c);
		updateRenderedColour(iterations);
		SDL_RenderDrawPoint(renderer, mandelbrotImage.x, mandelbrotImage.y);
		mandelbrotImage.advancePixel();

		if (mandelbrotImage.isDone()) {
			std::cout << "Mandelbrot image is completed!";
			SDL_RenderPresent(renderer);
		}

		if (frameCount % 100000 == 0) {
			SDL_RenderPresent(renderer);
		}
		frameCount++;
	}
	
    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}