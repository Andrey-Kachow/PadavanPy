import pygame
import numpy as np
from copy import deepcopy

WIDTH = 128
HEIGHT = 128
FPS = 220

arr = np.full((HEIGHT, WIDTH), False)

win = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Game of Life")


def kill(x, y):
	arr[y, x] = False
	win.set_at((x, y), black)


def revive(x, y):
	arr[y, x] = True
	win.set_at((x, y), white)


def change_color_if_nessesary(x, y, alive):
	if alive != arr[y, x]:
		if alive:
			win.set_at((x, y), white)
		else:
			win.set_at((x, y), black)


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
	change_color_if_nessesary(x, y, alive)
	return alive


def paint():
	x, y = pygame.mouse.get_pos()
	if pygame.mouse.get_pressed()[0]:
		revive(x, y)
	elif pygame.mouse.get_pressed()[2]:
		kill(x, y)


def day_passes():
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
