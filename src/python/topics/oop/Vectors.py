import math

PI = math.pi


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


class Line():
	def __init__(self, position_vector, direction_vector):
		self.pos = position_vector
		self.dir = direction_vector

	def __repr__(self):
		return "r = {} + t{}".format(self.pos, self.dir)

	def contains(self, point):
		pos_to_point = point - self.pos
		if abs(pos_to_point * self.dir) == pos_to_point.magnitude * self.dir.magnitude:
			return True
		return False

	def parallel_to_line(self, line):
		if abs(self.dir * line.dir) == self.dir.magnitude * line.dir.magnitude:
			return True
		return False

	def parallel_to_plane(self, plane):
		if plane.n * self.dir == 0:
			return True
		return False

	def lies_in_plane(self, plane):
		return plane.contains_line(self)

	def parallel_to(self, obj):
		if type(obj) is Line:
			return parallel_to_line(obj)
		elif type(obj) is Plane:
			return parallel_to_plane(obj)
		else:
			raise TypeError

	def identical_to(self, line):
		if type(line) is Line and self.parallel_to(line) and self.contains(line.pos):
			return True
		return False

	def intersects(self, line):
		if self.identical_to(line):
			return True
		det = line.dir.x * self.dir.y - line.dir.y * self.dir.x
		self_t = line.dir.x * (line.pos.y - self.pos.y) - line.dir.y * (line.pos.x - self.pos.x)
		line_t = self.dir.x * (line.pos.y - self.pos.y) - self.dir.y * (line.pos.x - self.pos.x)
		self_t = self_t / det
		line_t = line_t / det
		if self.pos.z + self_t * self.dir.z == line.pos.z + line_t * line.dir.z:
			self.pos = self.pos + self_t * self.dir
			return True
		return False

	def point_of_intersection_with(self, line):
		if self.intersects(line):
			return self.pos
		return None

	def skew(self, line):
		if not self.parallel_to(line) and not self.intersects(line):
			return True
		return False

	def distance_to_point(self, point):
		if self.contains(point):
			d = 0
		else:
			pos_to_point = point - self.pos
			cos_alpha = self.dir.cos_of_angle_with(pos_to_point)
			sin_alpha = math.sqrt(1 - cos_alpha ** 2)
			d = pos_to_point.magnitude * sin_alpha
		return d

	def distance_to_line(self, line):
		if self.intersects(line):
			d = 0
		else:
			pass
		return d

	def cos_angle_with_line(self, line):
		if self.intersects(line):
			pass


class Plane():
	def __init__(self, position, direction1, direction2):
		self.n = direction1 ** direction2
		self.const = self.n * position
		self.pos = position
		self.dir1 = direction1
		self.dir2 = direction2

	@property
	def cartesian(self):
		y = str(self.n.y)
		if self.n.y >= 0:
			y = "+" + y
		z = str(self.n.z)
		if self.n.z > 0:
			z = "+" + z
		return "{}x{}y{}z={}".format(self.n.x, y, z, self.cont)

	@property
	def parametric(self):
		return "r = {} + t{} +m{}".format(self.pos, self.dir1, self.dir2)

	@property
	def n(self):
		return Vector(self.x, self.y, self.z)

	def __repr__(self):
		return self.cartesian

	def contains_point(self, point):
		if point * self.n == self.const:
			return True
		return False

	def contains_line(self, line):
		if line.pos * self.n == self.const and line.dir * self.n == 0:
			return True
		return False

	def contains(self, obj):
		if type(obj) is Vector:
			return self.contains_point(obj)
		elif type(obj) is Line:
			return self.contains_line(obj)
		elif type(obj) is Plane:
			return self.identical_to(obj)
		else:
			raise TypeError

	def parallel_to_line(self, line):
		if self.n * line.dir == 0:
			return True
		return False

	def parallel_to_plane(self, plane):
		if abs(self.n * plane.n) == self.n.magnitude * plane.n.magnitude:
			return True
		return False

	def identical_to(self, plane):
		plane_line_1 = Line(plane.pos, plane.dir1)
		plane_line_2 = Line(plane.pos, plane.dir2)
		if self.contains_line(plane_line_1) and self.contains_line(plane_line_2):
			return True
		return False

	def intersects_with_line(self, line):
		if self.parallel_to_line(line):
			return False
		return True

	def intersects_with_plane(self, plane):
		if self.parallel_to_plane(plane):
			return False
		return True

	def point_of_intersection_with(self, line):
		if self.intersects_with_line(line):
			t = (self.const - self.n * line.pos) / (self.n * line.dir)
			return line.pos + t * line.dir
		return None

	# def common_line_with(slef, plane)
	# 	if self.intersects_with_plane(plane):
	# 		pass

	def cos_angle_with_line(self, line):
		return


O = Vector(0, 0, 0)

i = Vector(1, 0, 0)
j = Vector(0, 1, 0)
k = Vector(0, 0, 1)

l1 = Line(O, i)
l2 = Line(O, j)

p1 = Plane(O, i, j)
l3 = Line(O, k)
l4 = Line(k + i, k)
l5 = Line(k, i)

print(p1.point_of_intersection_with(l3))
print(p1.point_of_intersection_with(l4))
print(p1.point_of_intersection_with(l5))

# t = []
# 		try:
# 			if self.dir.x:
# 				t.append((point.x - self.pos.x) / self.dir.x)
# 			if self.dir.y:
# 				t.append((point.y - self.pos.y) / self.dir.y)
# 			if self.dir.z:
# 				t.append((point.z - self.pos.z) / self.dir.z)
# 		except AttributeError:
# 			if self.dir.x:
# 				t.append((point[0] - self.pos.x) / self.dir.x)
# 			if self.dir.y:
# 				t.append((point[1] - self.pos.y) / self.dir.y)
# 			if self.dir.z:
# 				t.append((point[2] - self.pos.z) / self.dir.z)
# 		for index in range(len(t)):
# 			if t[0] != t[index]:
# 				return False
# 		return True

# O = Vector(0, 0, 0)
# a = Vector(1, 1, 1)
# b = Vector(1, 0, 0)
# c = Vector(3, 5, 0)
# d = Vector(4, 4, 4)

# l1 = Line(O, b)

# print(l1.distance_to_point(c))

# def intersects(self, line):
# 		numerator1 = self.dir.x * (self.pos.y - line.pos.y)
# 		numerator2 = self.dir.y * (line.pos.x - self.pos.x)
# 		denominator = self.dir.x * line.dir.y - line.dir.x * self.dir.y
# 		line_t = (numerator1 + numerator2) / denominator
# 		self_t = (line.pos.x - self.pos.x + line_t * line.dir.x) / self.dir.x
# 		print(self.pos.z + self_t * self.dir.z, line.pos.z + line_t * self.dir.z)
# 		if self.pos.z + self_t * self.dir.z == line.pos.z + line_t * self.dir.z:
# 			self.pos = self.pos + self_t * self.dir
# 			return True
# 		return False