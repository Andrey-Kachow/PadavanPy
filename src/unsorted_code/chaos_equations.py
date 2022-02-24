import math
import pygame

WIDTH = 1000
HEIGHT = 1000
ORIGIN = (500, 500)

win = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Chaos Equations")

black = (0, 0, 0)
white = (255, 255, 255)
red = (255, 0, 0)
green = (0, 255, 0)
blue = (0, 0, 255)

colors = (white, red, green, blue)

win.set_at(ORIGIN, red)

clock = pygame.time.Clock()
run = True

t = -3
while run:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			run = False

	x = y = t
	
	for color in colors:	
		x_ = y * t + x - t
		y_ = x - y - t

		x, y = x_, y_

		x_index = ORIGIN[0] + int(10 * round(x, 1))
		y_index = ORIGIN[1] - int(10 * round(y, 1))

		if abs(x_index) < 1000 and abs(y_index) < 1000:
			win.set_at((x_index, y_index), color)

	t += 0.0001
	if t == 3.0001:
		t = -3


	pygame.display.update()
	# clock.tick(20)