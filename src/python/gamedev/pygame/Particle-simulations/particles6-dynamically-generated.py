import math
import pygame
from random import randint


class Vector():
	def __init__(self, x=0, y=0):
		self.x = x
		self.y = y

	@property
	def magnitude(self):
		return math.sqrt(self.x ** 2 + self.y ** 2)

	@property
	def unit_vector(self):
		return self / self.magnitude
	
	def __repr__(self):
		return("({}, {})".format(self.x, self.y))

	def __eq__(self, other):
		answer = False
		try:
			if self.x == other.x and self.y == other.y:
				answer = True
		except AttributeError:
			try:
				if len(other) == 2:
					if self.x == other[0] and self.y == other[1]:
						answer = True
			except TypeError:
				pass
		return answer

	def __ne__(self, other):
		return not (self == other)

	def __abs__(self):
		return self.magnitude

	def __neg__(self):
		return Vector(-self.x, -self.y)

	def __add__(self, other):
		try:
			result = Vector(self.x + other.x, self.y + other.y)
		except AttributeError:
			if len(other) == 2:
				result = Vector(self.x + other[0], self.y + other[1])
		return result

	def __radd__(self, other):
		return self + other

	def __sub__(self, other):
		try:
			return self + -other
		except TypeError:
			if len(other) == 2:
				for index in range(2):
					other[index] = -other[index]
				return self + other
			else:
				raise TypeError

	def __rsub__(self, other):
		return -self + other

	def __mul__(self, other):  # scalar product
		try:
			answer = self.x * other.x + self.y * other.y
		except AttributeError:
			try:
				if len(other) == 2:
					answer = self.x * other[0] + self.y * other[1]
			except TypeError:
				answer = Vector(self.x * other, self.y * other)
		return answer

	def __rmul__(self, other):
		return self * other

	def __truediv__(self, other):
		return Vector(self.x / other, self.y / other)

	def __nonzero__(self):
		if self.x or self.y:
			print("accepted", self.x, self.y)
			return True
		return False

	def dot(self, other):
		return self * other

	def cos_of_angle_with(self, vect):
		return (self * vect) / (self.magnitude * vect.magnitude)

	def angle_with(self, vect):
		cos_alpha = cos_of_angle_with(vect)
		return math.acos() 

	def parallel_to(self, vect):
		if abs(self * vect_or_line) == self.magnitude * vect_or_line.magnitude:
			return True
		return False

	@staticmethod
	def vectorise(arr):
		return Vector(arr[0], arr[1])


class Particle():
	G = 1
	RADIUS = 10
	MASS = 1
	CRIT_D = 2 * RADIUS
	MAX_SPEED = 10

	def __init__(self, x, y, color):
		self.x = x
		self.y = y
		self.color = color
		self.net_force = Vector(0, 0)
		self.velocity = Vector(0, 0)

	def __repr__(self):
		return "<{}-({},{})>".format(self.color, self.x, self.y)

	def force_exerted_by(self, other):
		dx = other.x - self.x
		dy = other.y - self.y

		d = math.sqrt(dx ** 2 + dy ** 2)

		f = 0.001 * force_funcs[(other.color, self.color)](d)
		fx = f * dx / d 
		fy = f * dy / d 

		return Vector(fx, fy)


class Space():
	RESISTIVITY = 0.001

	def __init__(self, particles):
		self.particles = particles

	def resolve_forces(self):
		length = len(self.particles)
		for j in range(length):
			p = self.particles[j]
			p.net_force = Vector(0,0)
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
			p.x = p.x + p.velocity.x
			p.y = p.y + p.velocity.y

	def draw_all_particles(self, surface):
		for p in self.particles:
			position = int(round(p.x)), int(round(p.y))
			pygame.draw.circle(surface, p.color, position, Particle.RADIUS)

	def walls(self):
		for p in self.particles:
			if p.x - Particle.RADIUS < 0:
				p.velocity.x = abs(p.velocity.x)
			if p.x + Particle.RADIUS > WIDTH:
				p.velocity.x = -abs(p.velocity.x)
			if p.y - Particle.RADIUS < 0:
				p.velocity.y = abs(p.velocity.y)
			if p.y + Particle.RADIUS > HEIGHT:
				p.velocity.y = -abs(p.velocity.y)


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


WIDTH = 1000
HEIGHT = 600
NUMBER_OF_COLORS = 7
NUMBER_OF_PARTICLES = 24

win = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Particle Game of Life")

black = (0, 0, 0)

colors = []
while len(colors) < NUMBER_OF_COLORS:
	new_color = (randint(0, 255), randint(0, 255), randint(0, 255))
	if not new_color in colors:
		colors.append(new_color)

force_funcs = {}

for i in range(NUMBER_OF_COLORS):
	for j in range(NUMBER_OF_COLORS):
		pair = colors[i], colors[i - j]
		force_funcs[pair] = generate_force_function()

space = Space([])
for i in range(NUMBER_OF_PARTICLES):
	par = Particle(randint(15, WIDTH - 15), randint(12, HEIGHT - 15), colors[randint(0, NUMBER_OF_COLORS - 1)])
	space.particles.append(par)

clock = pygame.time.Clock()
run = True
while run:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			run = False

	space.resolve_forces()
	space.resolve_velocity()
	space.displace_particles()
	space.walls()

	win.fill(black)
	space.draw_all_particles(win)
	pygame.display.update()

	# clock.tick(20)