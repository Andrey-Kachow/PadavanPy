from random import randint
import pygame

# Game of Pong, but ball always travels 45deg to the horisontal
pygame.init()
pygame.font.init() 


class GameDimensions:  # Markup
	def __init__(self, surface):
		self.surface = surface
		self.old_dimentions = 1280, 720

	@property
	def width(self):
		return self.surface.get_size()[0]
	
	@property
	def height(self):
		return self.surface.get_size()[1]

	@property
	def paddle_width(self):
		return self.surface.get_size()[0] // 40

	@property
	def paddle_height(self):
		return self.surface.get_size()[1] // 8

	@property
	def side_margin(self):
		return self.surface.get_size()[0] // 8

	@property
	def ball_width(self):
		return self.surface.get_size()[0] // 22

	@property
	def ball_height(self):
		return self.surface.get_size()[1] // 12

	@property
	def score_margin(self):
		return self.surface.get_size()[0] // 3

	@property
	def sep_line_rect(self):
		screen_width, screen_height = pygame.display.get_surface().get_size()
		return (screen_width // 2 - 3, 0, 6, screen_height)
		

class Ball:
	def __init__(self, surface, x, y, width, height, markup):
		self.markup = markup
		self.surface = surface
		self.x = x
		self.y = y
		self.width = width
		self.height = height

		self.x_vel = self.y_vel = 1
		self.up = bool(randint(0, 1))
		self.right = bool(randint(0, 1))
		
	@property
	def rect(self):
		return (round(self.x), round(self.y), round(self.width), round(self.height))

	@property
	def update_rect(self):
		return (
			round(self.x - 2 * self.x_vel), round(self.y - 2 * self.y_vel),
			round(self.width + 4 * self.x_vel), round(self.height + self.y_vel * 4)
		)

	def resize(self):
		x_scale_factor = self.markup.width / self.markup.old_dimentions[0]
		self.x = self.x * x_scale_factor
		self.x_vel = self.x_vel * x_scale_factor
		self.width = self.width * x_scale_factor

		y_scale_factor = self.markup.height / self.markup.old_dimentions[1]
		self.y = self.y * y_scale_factor
		self.y_vel = self.y_vel * y_scale_factor
		self.height = self.height * y_scale_factor


	def draw(self):
		pygame.draw.ellipse(self.surface, (255, 255, 255), self.rect)

	def displace(self):
		if self.up:
			self.y -= self.y_vel
		else:
			self.y += self.y_vel

		if self.right:
			self.x += self.x_vel
		else:
			self.x -= self.x_vel

	def collision_with_walls(self):
		if self.y <= 0 and self.up:
			self.up = False
		elif self.y + self.height >= self.markup.height:
			self.up = True 


class Paddle:

	vel = 4

	def __init__(self, surface, x, y, width, height, markup, cpu=False):
		self.markup = markup
		self.surface = surface
		self.x = x
		self.y = y
		self.width = width
		self.height = height
		self.cpu = cpu

	@property
	def rect(self):
		return (round(self.x), round(self.y), round(self.width), round(self.height))

	@property
	def column_rect(self):
		return (round(self.x), 0, round(self.width), self.markup.height)
	
	def resize(self):
		x_scale_factor = self.markup.width / self.markup.old_dimentions[0]
		self.x = self.x * x_scale_factor
		self.width = self.width * x_scale_factor

		y_scale_factor = self.markup.height / self.markup.old_dimentions[1]
		self.y = self.y * y_scale_factor
		Paddle.vel = Paddle.vel * y_scale_factor
		self.height = self.height * y_scale_factor

	def draw(self):
		pygame.draw.rect(self.surface, (255, 255, 255), self.rect)


class ScoreBoard:

	font = pygame.font.SysFont('Calibri', 60)
	Y = 5

	def __init__(self, surface, markup):
		self.surface = surface
		self.markup = markup
		self.margin = markup.score_margin
		self.left_score = self.right_score = 0
		self.update()

	@property
	def left_rect(self):
		width, height = self.left_text.get_size()
		return self.margin, self.Y, width, height

	@property
	def right_rect(self):
		width, height = self.right_text.get_size()
		return self.markup.width - width - self.margin, self.Y, width, height

	def __str__(self):
		return "Player1 {} : {} Player2".format(self.left_score, self.right_score)

	def resize(self):
		x_scale_factor = self.markup.width / self.markup.old_dimentions[0]
		self.margin = round(self.margin * x_scale_factor)

	def update(self):
		self.left_text = self.font.render(str(self.left_score), False, (255, 255, 255))
		self.right_text = self.font.render(str(self.right_score), False, (255, 255, 255))

	def draw(self):
		self.surface.blit(self.left_text, self.left_rect)
		self.surface.blit(self.right_text, self.right_rect)


def draw_field():
	pygame.draw.rect(win, (200, 200, 200), markup.sep_line_rect)
	ball.draw()
	left_paddle.draw()
	right_paddle.draw()
	score.draw()


def manage_paddle_motion():
	keys = pygame.key.get_pressed()
	if keys[pygame.K_w] and left_paddle.y > 0:
		left_paddle.y -= Paddle.vel
	if keys[pygame.K_s] and left_paddle.y + left_paddle.height < markup.height:
		left_paddle.y += Paddle.vel
	if keys[pygame.K_UP] and right_paddle.y > 0:
		right_paddle.y -= Paddle.vel
	if keys[pygame.K_DOWN] and right_paddle.y + right_paddle.height < markup.height:
		right_paddle.y += Paddle.vel


def collisions():
	if ball.right:
		if abs(ball.x + ball.width - right_paddle.x) <= ball.x_vel / 2:
			if ball.y + ball.height > right_paddle.y and ball.y < right_paddle.y + right_paddle.height:
				ball.right = False
	else:
		if abs(left_paddle.x + left_paddle.width - ball.x) <= ball.x_vel / 2:
			if ball.y + ball.height > left_paddle.y and ball.y < left_paddle.y + left_paddle.height:
				ball.right = True

	for paddle in [left_paddle, right_paddle]:
		if ball.x + ball.width > paddle.x and ball.x < paddle.x + paddle.width:
			if ball.up:
				if abs(paddle.y + paddle.height - ball.y) <= ball.y_vel * 2:
					ball.up = False
			else:
				if abs(ball.y + ball.height - paddle.y) <= ball.y_vel * 2:
					ball.up = True


def ball_outside_the_screen():	
	if ball.x + ball.width + ball.x_vel < 0:
		score.right_score += 1
		outside = True
	elif ball.x > markup.width + ball.x_vel:
		score.left_score += 1
		outside = True
	else:
		outside = False
	
	if outside:
		ball.x = (markup.width - ball.width) // 2
		ball.y = (markup.height - ball.height) // 2
		ball.up = bool(randint(0, 1))
		ball.right = bool(randint(0, 1))
		score.update()


MAX_FPS = 80

win = pygame.display.set_mode((1280, 720), pygame.RESIZABLE)
pygame.display.set_caption("Pong")


black = (0, 0, 0)
white = (255, 255, 255)
grey = (128, 128, 128)

clock = pygame.time.Clock()

markup = GameDimensions(win)
ball = Ball(
	win, (markup.width - markup.ball_width) // 2,
	(markup.height - markup.ball_height) // 2,
	markup.ball_width, markup.ball_height, markup
)
left_paddle = Paddle(
	win, markup.side_margin,
	300, markup.paddle_width, markup.paddle_height, markup
)
right_paddle = Paddle(
	win, markup.width - markup.side_margin - markup.paddle_width,
	300, markup.paddle_width, markup.paddle_height, markup
)
score = ScoreBoard(win, markup)


draw_field()
pygame.display.update()
run = True
while run:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			run = False
		elif event.type == pygame.VIDEORESIZE:
			markup.old_dimentions = pygame.display.get_surface().get_size()
			scrsize = event.size
			win = pygame.display.set_mode(scrsize, pygame.RESIZABLE)
			for item in [ball, left_paddle, right_paddle, score]:
				item.resize()
			draw_field()
			pygame.display.update()

	manage_paddle_motion()

	collisions()
	ball.collision_with_walls()
	ball.displace()

	ball_outside_the_screen()

	win.fill(black)
	draw_field()

	pygame.display.update([
		left_paddle.column_rect, right_paddle.column_rect, ball.update_rect,
		score.left_rect, score.right_rect
	])

	clock.tick(MAX_FPS)

pygame.quit()


	# @property
	# def width(self):
	# 	return pygame.display.get_surface().get_size()[0]
	
	# @property
	# def height(self):
	# 	return pygame.display.get_surface().get_size()[1]

	# @property
	# def paddle_width(self):
	# 	return pygame.display.get_surface().get_size()[0] // 20

	# @property
	# def paddle_height(self):
	# 	return pygame.display.get_surface().get_size()[1] // 8

	# @property
	# def side_margin(self):
	# 	return pygame.display.get_surface().get_size()[0] // 8

	# @property
	# def ball_width(self):
	# 	return pygame.display.get_surface().get_size()[0] // 20

	# @property
	# def ball_height(self):
	# 	return pygame.display.get_surface().get_size()[1] // 11

