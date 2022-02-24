import ComplexNumbers as cn
import numpy as np
import pygame

WIDTH = 1000
HEIGHT = 1000
ORIGIN = (700, 500)

arr = np.zeros((HEIGHT, WIDTH), dtype=int)

win = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Mandelbrot")

black = (0, 0, 0)
white = (255, 255, 255)
red = (255, 0, 0)
green = (0, 255, 0)

win.set_at(ORIGIN, red)

clock = pygame.time.Clock()
run = True
skeched = False
while run:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			run = False

	if not skeched:
		for col in range(WIDTH):
			for row in range(HEIGHT):
				c = cn.ComplexNumber(0.002*(col - ORIGIN[0]), 0.002*(row - ORIGIN[1]))
				z = 0
				for i in range(20):
					z = z * z + c
				if abs(z.re) + abs(z.im) > 100000:
					win.set_at((col, row), white)
				if z == z * z + c:
					win.set_at((col, row), green)
			pygame.display.update()
		skeched = True

	pygame.display.update()
	clock.tick(20)