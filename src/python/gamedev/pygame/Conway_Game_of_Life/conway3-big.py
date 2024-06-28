import pygame
import numpy as np
from copy import deepcopy
import time

WIDTH = 200
HEIGHT = 200
SIZE = 4
SCREEN_WIDTH = WIDTH * SIZE
SCREEN_HEIGHT = HEIGHT * SIZE
FPS = 220

arr = np.full((HEIGHT, WIDTH), False)

win = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Game of Life")


def kill(x, y):
	arr[y, x] = False
	pygame.draw.rect(win, black, (x * SIZE, y * SIZE, SIZE, SIZE))


def revive(x, y):
	arr[y, x] = True
	pygame.draw.rect(win, white, (x * SIZE, y * SIZE, SIZE, SIZE))


def paint_white_if_nessesary(x, y, alive):
	if alive:
		pygame.draw.rect(win, white, (x * SIZE, y * SIZE, SIZE, SIZE))


def dead_or_alive(x, y):
	alive = False
	alive_squares_around = 0
	for i in (-1, 0, 1):
		for j in (-1, 0, 1):
			if i or j:
				if arr[(y + j) % HEIGHT, (x + i) % WIDTH]:
					alive_squares_around += 1
	if alive_squares_around == 3  or (arr[y, x] and alive_squares_around == 2):
		alive = True
	paint_white_if_nessesary(x, y, alive)
	return alive


def paint():
	x, y = pygame.mouse.get_pos()
	x, y = x // SIZE, y // SIZE
	if pygame.mouse.get_pressed()[0]:
		revive(x, y)
	elif pygame.mouse.get_pressed()[2]:
		kill(x, y)


def day_passes():
	win.fill(black)
	global arr
	new_arr = np.full((HEIGHT, WIDTH), False)
	for y in range(HEIGHT):
		for x in range(WIDTH):
			new_arr[y, x] = dead_or_alive(x, y)
	arr = new_arr.copy()

black = (0, 0, 0)
white = (255, 255, 255)
paused = True
run = True
clock = pygame.time.Clock()

while run:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			run = False

	keys = pygame.key.get_pressed()
	if keys[pygame.K_p]:
		paused = True
	if keys[pygame.K_s]:
		paused = False

	if paused:
		paint()
	else:
		day_passes()

	pygame.display.update()
	clock.tick(FPS)
