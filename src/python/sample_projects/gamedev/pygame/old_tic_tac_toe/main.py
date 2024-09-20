import pygame, time, random
pygame.init()

win = pygame.display.set_mode((600, 640))
pygame.display.set_caption('Tic Tac Toe')
icon = pygame.image.load('icon.png')
pygame.display.set_icon(icon)


class Button:
	def __init__(self, x, y, w, h, image, display, func):
		self.x = x
		self.y = y
		self.w = w
		self.h = h
		self.image = image
		self.display = display
		self.func = func

	def appear(self):
		self.display.blit(self.image, (self.x, self.y))

	def mouse_interaction(self):
		mouse = pygame.mouse.get_pos()
		if self.x < mouse[0] < self.x + self.w and self.y < mouse[1] < self.y + self.h:
			if pygame.mouse.get_pressed()[0]:
				self.func()


def draw_field():
	win.fill((255, 255, 255))
	pygame.draw.rect(win, (0, 0, 0), (180, 0, 30, 600))
	pygame.draw.rect(win, (0, 0, 0), (390, 0, 30, 600))
	pygame.draw.rect(win, (0, 0, 0), (0, 180, 600, 30))
	pygame.draw.rect(win, (0, 0, 0), (0, 390, 600, 30))

	for coords, value in field.items():
		if value == 'X':
			win.blit(cross, coords)
		elif value == 'O':
			win.blit(zero, coords)

	pygame.draw.rect(win, (100, 100, 100), (0, 600, 600, 40))
	resetButton.appear()
	vsCPUButton.appear()
	vsUSERButton.appear()


def mouse_manage():
	global playerXturn
	if not game_over:
		mouse = pygame.mouse.get_pos()
		for coords in field.keys():
			if coords[0] < mouse[0] < coords[0] + 180 and coords[1] < mouse[1] < coords[1] + 180:
				if pygame.mouse.get_pressed()[0] and not(field[coords]):
					if playerXturn:
						field[coords] = 'X'
						playerXturn = False
					else:
						field[coords] = 'O'
						playerXturn = True

	resetButton.mouse_interaction()
	vsCPUButton.mouse_interaction()
	vsUSERButton.mouse_interaction()


def game_is_over():
	fl = []
	for value in field.values():
		fl.append(value)
	if   (fl[0] == fl[1] == fl[2] and fl[0] and fl[1] and fl[2]):
		pygame.draw.line(win, (0, 0, 255), (90, 90), (510, 90), 11)
		return True
	elif (fl[3] == fl[4] == fl[5] and fl[3] and fl[4] and fl[5]):
		pygame.draw.line(win, (0, 0, 255), (90, 300), (510, 300), 11)
		return True
	elif (fl[6] == fl[7] == fl[8] and fl[6] and fl[7] and fl[8]):
		pygame.draw.line(win, (0, 0, 255), (90, 510), (510, 510), 11)
		return True
	elif (fl[0] == fl[3] == fl[6] and fl[0] and fl[3] and fl[6]):
		pygame.draw.line(win, (0, 0, 255), (90, 90), (90, 510), 11)
		return True
	elif (fl[1] == fl[4] == fl[7] and fl[1] and fl[4] and fl[7]):
		pygame.draw.line(win, (0, 0, 255), (300, 90), (300, 510), 11)
		return True
	elif (fl[2] == fl[5] == fl[8] and fl[2] and fl[5] and fl[8]):
		pygame.draw.line(win, (0, 0, 255), (510, 90), (510, 510), 11)
		return True
	elif (fl[0] == fl[4] == fl[8] and fl[0] and fl[4] and fl[8]):
		pygame.draw.line(win, (0, 0, 255), (90, 90), (510, 510), 11)
		return True
	elif (fl[2] == fl[4] == fl[6] and fl[2] and fl[4] and fl[6]):
		pygame.draw.line(win, (0, 0, 255), (90, 510), (510, 90), 11)
		return True
	return False


def field_is_full():
	for value in field.values():
		if not value:
			return False
	return True


def reset():
	global playerXturn
	global game_over
	global field
	playerXturn = True
	game_over = False
	field = FIELD.copy()


def vsCPU():
	reset()
	global CPUmode
	CPUmode = True

def vsUSER():
	reset()
	global CPUmode
	CPUmode = False


def cpu_make_move():
	global playerXturn
	playerXturn = True
	moved = False
	while not moved:
		for key, value in field.items():
			if not value:
				if not random.randint(0, 100):
					field[key] = 'O'
					moved = True
					break


cross = pygame.image.load('Cross.png')
zero = pygame.image.load('Zero.png')
resetButton = Button(0, 600, 180, 40, pygame.image.load('reset.png'), win, reset)
vsCPUButton = Button(210, 600, 180, 40, pygame.image.load('vsCPU.png'), win, vsCPU)
vsUSERButton = Button(420, 600, 120, 40, pygame.image.load('vsUSER.png'), win, vsUSER)


FIELD = {
	(0, 0): None,
	(210, 0): None,
	(420, 0): None,
	(0, 210): None,
	(210, 210): None,
	(420, 210): None,
	(0, 420): None,
	(210, 420): None,
	(420, 420): None,
}
field = FIELD.copy()

playerXturn = True
game_over = False
CPUmode = False



run = True
while run:
	pygame.time.delay(100)

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			run = False

	mouse_manage()
	draw_field()

	if game_is_over() or field_is_full():
		game_over = True
		
	pygame.display.update()

	if not game_over and not playerXturn and CPUmode:
		cpu_make_move()

pygame.quit()