import math
import pygame
from random import randint


class Vector():
	def __init__(self, x=0, y=0, z=0):
		self.x = x
		self.y = y
		self.z = z

	@property
	def magnitude(self):
		return math.sqrt(self.x ** 2 + self.y ** 2 + self.z ** 2)

	@property
	def unit_vector(self):
		return self / self.magnitude
	
	def __repr__(self):
		return("({}, {}, {})".format(self.x, self.y, self.z))

	def __eq__(self, other):
		answer = False
		try:
			if self.x == other.x and self.y == other.y and self.z == other.z:
				answer = True
		except AttributeError:
			try:
				if len(other) == 3:
					if self.x == other[0] and self.y == other[1] and self.z == other[2]:
						answer = True
			except TypeError:
				pass
		return answer

	def __ne__(self, other):
		return not (self == other)

	def __abs__(self):
		return self.magnitude

	def __neg__(self):
		return Vector(-self.x, -self.y, -self.z)

	def __add__(self, other):
		try:
			result = Vector(self.x + other.x, self.y + other.y, self.z + other.z)
		except AttributeError:
			if len(other) == 3:
				result = Vector(self.x + other[0], self.y + other[1], self.z + other[2])
		return result

	def __radd__(self, other):
		return self + other

	def __sub__(self, other):
		try:
			return self + -other
		except TypeError:
			if len(other) == 3:
				for index in range(3):
					other[index] = -other[index]
				return self + other
			else:
				raise TypeError

	def __rsub__(self, other):
		return -self + other

	def __mul__(self, other):  # scalar product
		try:
			answer = self.x * other.x + self.y * other.y + self.z * other.z
		except AttributeError:
			try:
				if len(other) == 3:
					answer = self.x * other[0] + self.y * other[1] + self.z * other[2]
			except TypeError:
				answer = Vector(self.x * other, self.y * other, self.z * other)
		return answer

	def __rmul__(self, other):
		return self * other

	def __pow__(self, other):  # cross product
		try:
			x = self.y * other.z - self.z * other.y
			y = self.z * other.x - self.x * other.z
			z = self.x * other.y - self.y * other.x
		except AttributeError:
			if len(other) == 3:
				x = self.y * other[2] - self.z * other[1]
				y = self.z * other[0] - self.x * other[2]
				z = self.x * other[1] - self.y * other[0]
		return Vector(x, y, z)

	def __truediv__(self, other):
		return Vector(self.x / other, self.y / other, self.z / other)

	def __nonzero__(self):
		if self.x or self.y or self.z:
			return True
		return False

	def dot(self, other):
		return self * other

	def cross(self, other):
		return self ** other

	def cos_of_angle_with(self, vect):
		return (self * vect) / (self.magnitude * vect.magnitude)

	def angle_with(self, vect):
		cos_alpha = cos_of_angle_with(vect)
		return math.acos() 

	def parallel_to(self, vect_or_line):
		try:
			if abs(self * vect_or_line.dir) == self.magnitude * vect_or_line.dir.magnitude:
				return True
		except AttributeError:
			if abs(self * vect_or_line) == self.magnitude * vect_or_line.magnitude:
				return True
		return False

	@staticmethod
	def vectorise(arr):
		return Vector(arr[0], arr[1], arr[2])


class Shadow():
	def __init__(self, position, color):
		self.pos = position
		self.color = color


class Particle():
	G = 1
	RADIUS = 10
	MASS = 1
	CRIT_D = 2 * RADIUS
	MAX_SPEED = 10

	def __init__(self, position, color):
		self.pos = position
		self.color = color
		self.net_force = Vector(0, 0, 0)
		self.velocity = Vector(0, 0, 0)
		self.shadow = Shadow(Vector(self.pos.x - Particle.RADIUS, self.pos.y, 0), grey)

	def __repr__(self):
		return "<{}-({},{},{})>".format(self.color, self.pos.x, self.pos.y, self.pos.z)

	def force_exerted_by(self, other):
		dx = other.x - self.x
		dy = other.y - self.y
		dz = other.z - self.z

		d = math.sqrt(dx ** 2 + dy ** 2 + dz ** 2)

		f = 0.001 * force_funcs[(other.color, self.color)](d)
		fx = f * dx / d 
		fy = f * dy / d 
		fz = f * dz / d

		return Vector(fx, fy, fz)


class Space():
	RESISTIVITY = 0.001

	def __init__(self, particles):
		self.particles = particles

	def resolve_forces(self):
		length = len(self.particles)
		for j in range(length):
			p = self.particles[j]
			p.net_force = Vector(0, 0, 0)
			for i in range(1, length):
				p.net_force = p.net_force + p.force_exerted_by(self.particles[j-i])
			
			if p.velocity.magnitude:
				air_resistance = -p.velocity * Space.RESISTIVITY
				p.net_force = p.net_force + air_resistance

	def resolve_velocity(self):
		for p in self.particles:
			p.velocity += p.net_force
			if p.velocity.magnitude > Particle.MAX_SPEED:
				p.velocity = p.velocity.unit_vector * Particle.MAX_SPEED

	def displace_particles(self):
		for p in self.particles:
			p.pos = p.pos + p.velocity
			p.shadow.pos = p.shadow.pos + Vector(p.velocity.x, p.velocity.y, 0)

	def draw_back_faces(self, surface):
		va = ORIGIN
		vb = ORIGIN[0] + WIDTH, ORIGIN[1]
		vc = ORIGIN[0] + 2 * WIDTH, ORIGIN[1] + HEIGHT
		vd = ORIGIN[0] + WIDTH, ORIGIN[1] + HEIGHT
		pygame.draw.polygon(surface, light_grey, (va, vb, vc, vd))

		vc = MARGIN + WIDTH, MARGIN
		vd = MARGIN, MARGIN
		pygame.draw.polygon(surface, white, (va, vb, vc, vd))

		va = ORIGIN[0] + 2 * WIDTH, ORIGIN[1] + HEIGHT
		vd = ORIGIN[0] + 2 * WIDTH, ORIGIN[1]
		pygame.draw.polygon(surface, medium_grey, (va, vb, vc, vd))

	def screen_coords(self, pos):
		return ORIGIN[0] + int(round(pos.x)) + int(round(pos.y)), ORIGIN[1] + int(round(pos.y)) - int(round(pos.z))

	def draw_shadows(self, surface):
		for p in self.particles:
			position = self.screen_coords(p.shadow.pos)
			rectangular = (position[0], position[1], 2 * Particle.RADIUS, Particle.RADIUS)
			pygame.draw.ellipse(surface, p.shadow.color, rectangular)

	def draw_all_particles(self, surface):
		for p in self.particles:
			position = self.screen_coords(p.pos)
			pygame.draw.circle(surface, p.color, position, Particle.RADIUS)

	def walls(self):
		for p in self.particles:
			if p.pos.x - Particle.RADIUS < 0:
				p.velocity.x = abs(p.velocity.x)
			if p.pos.x + Particle.RADIUS > WIDTH:
				p.velocity.x = -abs(p.velocity.x)

			if p.pos.y - Particle.RADIUS < 0:
				p.velocity.y = abs(p.velocity.y)
			if p.pos.y + Particle.RADIUS > LENGTH:
				p.velocity.y = -abs(p.velocity.y)

			if p.pos.z - Particle.RADIUS < 0:
				p.velocity.z = abs(p.velocity.z)
			if p.pos.z + Particle.RADIUS > HEIGHT:
				p.velocity.z = -abs(p.velocity.z)


def generate_force_function():

	def force_function(d):
		if d < Particle.CRIT_D:
			return 10 * math.sin(d * 2 * math.pi / (Particle.CRIT_D * 4)) - 10
		else:
			if d < Particle.CRIT_D + 8 * Particle.RADIUS:
				ran = randint(1, 19)
				mul = 0.0002 * randint(-99, 60)
				return mul * (d - Particle.CRIT_D) * (d - Particle.CRIT_D - ran * Particle.RADIUS)
			else:
				return 0

	return force_function


WIDTH = 300
LENGTH = 300 # * math.sqrt(2)
HEIGHT = 300
MARGIN = 30

SCREEN_WIDTH = 2 * (WIDTH + MARGIN)
SCREEN_HEIGHT = 2 * (HEIGHT + MARGIN)
ORIGIN = MARGIN, MARGIN + HEIGHT

NUMBER_OF_COLORS = 3
NUMBER_OF_PARTICLES = 30

win = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Particle Game of Life")

black = (0, 0, 0)
light_grey = (200, 200, 200)
medium_grey = (150, 150, 150)
white = (255, 255, 255)
grey = (128, 128, 128)

# colors = []
# while len(colors) < NUMBER_OF_COLORS:
# 	new_color = (randint(0, 255), randint(0, 255), randint(0, 255))
# 	if not new_color in colors:
# 		colors.append(new_color)

# force_funcs = {}

# for i in range(NUMBER_OF_COLORS):
# 	for j in range(NUMBER_OF_COLORS):
# 		pair = colors[i], colors[i - j]
# 		force_funcs[pair] = generate_force_function()
a = Particle(Vector(20, 20, 20), (255, 0, 0))
space = Space([a])
# for i in range(NUMBER_OF_PARTICLES):
# 	par = Particle(randint(15, WIDTH - 15), randint(12, HEIGHT - 15), colors[randint(0, NUMBER_OF_COLORS - 1)])
# 	space.particles.append(par)

clock = pygame.time.Clock()
run = True
while run:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			run = False

	keys = pygame.key.get_pressed()
	if keys[pygame.K_w]:
		a.velocity.y -= 0.001
	if keys[pygame.K_s]:
		a.velocity.y += 0.001
	if keys[pygame.K_a]:
		a.velocity.x -= 0.001
	if keys[pygame.K_d]:
		a.velocity.x += 0.001
	if keys[pygame.K_SPACE]:
		a.velocity.z += 0.001
	if keys[pygame.K_LSHIFT]:
		a.velocity.z -= 0.001



	space.resolve_forces()
	space.resolve_velocity()
	space.displace_particles()
	space.walls()

	win.fill(black)
	space.draw_back_faces(win)
	space.draw_shadows(win)
	space.draw_all_particles(win)
	pygame.display.update()

	# clock.tick(20)