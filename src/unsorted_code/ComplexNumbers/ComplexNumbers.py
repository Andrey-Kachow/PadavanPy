import math

PI = math.pi

class ComplexNumber():
	def __init__(self, real=0, imaginary=0):
		self.re = real
		self.im = imaginary

	@property
	def mod(self): # modulus
		return math.sqrt(self.re ** 2 + self.im ** 2)

	@property
	def arg(self): # argument
		angle = math.atan2(self.im, self.re)
		if angle < 0:
			angle += 2 * PI
		return angle

	@property
	def modarg_form(self):
		return "{}exp({}i)".format(self.mod, self.arg)
	
	@property
	def euler(self):
		form = str(self.mod)
		if self.arg:
			form += "[cos({0}) + isin({0})]".format(self.arg)
		return form

	def __repr__(self):
		return "({}, {}i)".format(self.re, self.im)

	def __str__(self):
		if self.im == 0:
			string = str(self.re)
		elif self.re == 0:
			string = str(self.im) + "i"
		else:
			if self.im > 0:
				string = "{}+{}i".format(self.re, self.im)
			else:
				string = "{}{}i".format(self.re, self.im)
		return string

	def __eq__(self, other):
		answer = False
		try:
			if self.re == other.re and self.im == other.im:
				answer = True
		except AttributeError:
			if self.re == other:
				answer = True
		return answer

	def __ne__(self, other):
		return not (self == other)

	def __abs__(self):
		return self.mod

	def __neg__(self):
		return ComplexNumber(-self.re, -self.im)

	def __add__(self, other):
		try:
			result = ComplexNumber(self.re + other.re, self.im + other.im)
		except AttributeError:
			result = ComplexNumber(self.re + other, self.im)
		return result

	def __radd__(self, other):
		return self + other

	def __sub__(self, other):
		return self + -other

	def __rsub__(self, other):
		return -self + other

	def __mul__(self, other):
		try:
			re = self.re * other.re - self.im * other.im
			im = self.re * other.im + self.im * other.re
		except AttributeError:
			re = self.re * other
			im = self.im * other
		return ComplexNumber(re, im)

	def __rmul__(self, other):
		return self * other

	def __truediv__(self, other):
		try:
			realised_denominator = other.re ** 2 + other.im ** 2
			re = (self.re * other.re + self.im * other.im) / realised_denominator
			im = (self.im * other.re - self.re * other.im) / realised_denominator
		except AttributeError:
			re = self.re / other
			im = self.im / other
		return ComplexNumber(re, im)

	def __rtruediv__(self, other):
		other = ComplexNumber(other, 0)
		return other / self

	def __nonzero__(self):
		if self.re or self.im:
			return True
		return False

	def conjugate(self):
		return ComplexNumber(self.re, - self.im)




# @property
# def arg(self): # argument in radians. if z = 0, then undefined
# 	if self.im == 0:
# 		if self.re == 0:
# 			angle = None
# 		elif self.re > 0:
# 			angle = 0
# 		else:
# 			angle = PI
# 	elif self.re == 0:
# 		if self.im > 0:
# 			angle = PI / 2
# 		else:
# 			angle = 3 * PI / 2
# 	else:
# 		if self.re > 0:
# 			if self.im > 0:
# 				quadrant = 0
# 			else:
# 				quadrant = 1
# 		else:
# 			if self.im > 0:
# 				quadrant = 3
# 			else:
# 				quadrant = 2
# 		if quadrant % 2:
# 			angle = quadrant * PI / 2 + math.atan(abs(self.re / self.im))
# 		else:
# 			angle = quadrant * PI / 2 + math.atan(abs(self.im / self.re))
# 	return angle