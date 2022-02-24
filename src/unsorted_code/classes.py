import math

# Use "class" keyword to define your own data sructure

# class MyClass:
# 	pass


# a = MyClass
# b = MyClass()

# print(a)
# print(b)





# # variables which belong to a class are called attributes
# class JustFive:
# 	num = 5


# b = JustFive()

# print(b)
# print(b.num)
# print(JustFive)
# print(JustFive.num)





# # functions which belong to a class are called methods
# class Number:
# 	num = 7

# 	def square(self):  # First parameter of the class method is the object itself
# 		return self.num * self.num  # convention suggests using the word "self". It is not a language keyword


# c = Number() 	
# print(c.square())





# # __init__() method allows to create an instance of a class
# class Person:

# 	species = "Homo Sapiens"

# 	def __init__(self, name, age):
# 		self.name = name
# 		self.age = age

# 	def birthday(self):
# 		self.age += 1

		
# andrey = Person("Andrey Popov", 20)
# print(andrey.name, andrey.age, andrey.species)
# print(Person.species)
# andrey.birthday()
# print(andrey.name, andrey.age, andrey.species)

# nora = Person("Nora Adiyan", 20)
# print(nora.name, nora.age, nora.species)
# print(Person.species)
# nora.age = 15
# print(nora.name, nora.age, nora.species)
# print("Andrey goes to jail")





# # Inheritance. Create subclasses, which have everything the parent class have
# class Student(Person):
# 	pass

# andrey = Student("Andrey Popov", 20)
# print(andrey.name, andrey.age, andrey.species)
# print(Student.species)
# andrey.birthday()
# print(andrey.name, andrey.age, andrey.species)





# # Attributes and methods with the same name can be redefined override the parent values
# class Animal(object):  # By default all classes inherit from class called "object".

# 	fat = False

# 	def __init__(self, name, age):
# 		self.name = name
# 		self.age = age


# class Seal(Animal):

# 	fat = True

# 	def __init__(self, name, age, loved_by=None):

# 		Animal.__init__(self, name, age)

# 		self.loved_by = ["Nora"]

# 		if loved_by != None:
# 			self.loved_by.append(loved_by)


# bruce = Animal("Bruce", 13)
# print("Animals are fat?", bruce.fat)

# seal = Seal("Kroshik", 25, )
# print("Seals are fat?", seal.fat)





# # use super() function to make multilevel inheritance possible and easier
# class Dog(Animal):

# 	sound = "Ruff!"

# 	def __init__(self, name, age, owner):
# 		super().__init__(name, age)
# 		self.owner = owner

# 	def bark(self, message):
# 		print(self.sound, message, self.sound, self.sound)


# class Corgi(Dog):

# 	sound = "Bark!"

# 	def __init__(self, name, age, owner):
		
# 		super().__init__(name, age, owner)
# 		self.loved_by = "Nora"


# spot = Dog("Spot", 7, "Brodyaga")
# holly = Corgi("Holly", 13, "Queen Elizabeth II")

# spot.bark("I love you, Holly!")
# holly.bark("I love you too, Spot!")






# # Magic methods __str__(), __repr__()
# class Hedgehog(Animal):
# 	def __init__(self, name, age, number_of_quills):
# 		super().__init__(name, age)
# 		self.quills = number_of_quills

# 	def __repr__(self):
# 		return "Hedgehog('{}', {}, {})".format(self.name, self.age, self.quills)

# 	def __str__(self):
# 		return "{} is a hedgehog. it is {} years old and it has {} quills".format(self.name, self.age, self.quills)


# lj = Hedgehog("Eljey", 3, 5000)
# ejidze = Hedgehog("Ejidze", 10, 20)
# sonic = Hedgehog("Sonic", 15, 10) 

# hedgehog_list = [lj, ejidze, sonic]

# print(lj, ejidze, sonic, sep="\n")

# print(hedgehog_list)

# print(Hedgehog)





# # Decorator @propery
# class Vector():
# 	def __init__(self, x=0, y=0, z=0):
# 		self.x = x
# 		self.y = y
# 		self.z = z

# 	@property
# 	def magnitude(self):
# 		return math.sqrt(self.x ** 2 + self.y ** 2 + self.z ** 2)


# b = Vector(1, 2, 3)

# print(b.magnitude)

# b.x = 10

# print(b.magnitude)





# # Class Methods can only manipulate the class variables
# class Particle:
	
# 	G = 6.67 * 10 ** (-11)
# 	g = 9.81

# 	def __init__(self, mass):
# 		self.mass = mass
# 		self.speed = 0

# 	@classmethod
# 	def change_gravitation_field_strength(cls, new_value):
# 		cls.g = new_value

# 	@classmethod
# 	def not_working_method(cls):
# 		cls.mass = 69


# a = Particle(1)
# b = Particle(2)

# print(Particle.g)
# print(a.g)

# Particle.change_gravitation_field_strength(10)
# print(Particle.g)
# print(a.g)

# a.change_gravitation_field_strength(7)
# print(Particle.g)
# print(a.g)
# print()

# # print(a.mass)
# # print(b.mass)
# # Particle.not_working_method()
# # print(a.mass)
# # print(b.mass)
 




# # Static methods do something but they do not have access to the class variables and instance variables
# class Math:

# 	@staticmethod
# 	def add_five(value):
# 		return value + 5

# 	@staticmethod
# 	def display():
# 		print("I love Mathematics")

# var = Math.add_five(5)
# print(var)

# Math.display()





# # More magic methods?
# class Vector():

# 	def __init__(self, x=0, y=0):
# 		self.x = x
# 		self.y = y

# 	@property
# 	def magnitude(self):
# 		return math.sqrt(self.x ** 2 + self.y ** 2)

# 	@property
# 	def unit_vector(self):
# 		return self / self.magnitude
	
# 	def __repr__(self):
# 		return("({}, {})".format(self.x, self.y))

# 	def __eq__(self, other):
# 		answer = False
# 		try:
# 			if self.x == other.x and self.y == other.y:
# 				answer = True
# 		except AttributeError:
# 			try:
# 				if len(other) == 2:
# 					if self.x == other[0] and self.y == other[1]:
# 						answer = True
# 			except TypeError:
# 				pass
# 		return answer

# 	def __ne__(self, other):
# 		return not (self == other)

# 	def __abs__(self):
# 		return self.magnitude

# 	def __neg__(self):
# 		return Vector(-self.x, -self.y)

# 	def __add__(self, other):
# 		try:
# 			result = Vector(self.x + other.x, self.y + other.y)
# 		except AttributeError:
# 			if len(other) == 2:
# 				result = Vector(self.x + other[0], self.y + other[1])
# 		return result

# 	def __radd__(self, other):
# 		return self + other

# 	def __sub__(self, other):
# 		try:
# 			return self + -other
# 		except TypeError:
# 			if len(other) == 2:
# 				for index in range(2):
# 					other[index] = -other[index]
# 				return self + other
# 			else:
# 				raise TypeError

# 	def __rsub__(self, other):
# 		return -self + other

# 	def __mul__(self, other):  # scalar product or vector by number
# 		try:
# 			answer = self.x * other.x + self.y * other.y
# 		except AttributeError:
# 			try:
# 				if len(other) == 2:
# 					answer = self.x * other[0] + self.y * other[1]
# 			except TypeError:
# 				answer = Vector(self.x * other, self.y * other)
# 		return answer

# 	def __rmul__(self, other):
# 		return self * other

# 	def __truediv__(self, other):
# 		return Vector(self.x / other, self.y / other)

# 	def __nonzero__(self):
# 		if self.x or self.y:
# 			return True
# 		return False

# 	def dot(self, other):
# 		return self * other

# 	def cos_of_angle_with(self, vect):
# 		return (self * vect) / (self.magnitude * vect.magnitude)

# 	def angle_with(self, vect):
# 		cos_alpha = cos_of_angle_with(vect)
# 		return math.acos() 

# 	def parallel_to(self, vect):
# 		if abs(self * vect) == self.magnitude * vect.magnitude:
# 			return True
# 		return False

# 	@staticmethod
# 	def vectorise(arr):
# 		return Vector(arr[0], arr[1])


# a = Vector(2, 5)

# print(a.unit_vector)

# print(a, -a)
# print(a * 2)
# print(a + Vector(3, 2))
# print(a == Vector(2, 5))
# print(abs(a), a.magnitude)
# print(bool(a))






















