import math
import random

'''
	Добро пожаловать в модуль, посвященный генераторам!
	Здесь мы научимся писать различные генераторы, от
	самых простых, до более сложных.

	Задание 1. Напините простой генератор gen_2_8_9_1,
	который ничего не делает, кроме того что он
	всегда генерирует 4 числа в следующем порядке:
		
		2, 8, 9, 1

	...после чего итерация завершается.
'''
def gen_2_8_9_1():
	yield 2
	yield 8
	yield 9
	yield 1


'''
	Задание 2. Реализуйте генератор нечетных чисел,
	таких как 1, 3, 5, 7 и т.д. Итерации не должны останавливаться,
	то есть функцию next() от этого генератора можно вызывать
	сколько угодно раз
'''
def gen_odds():
	current = 1
	while True:
		yield current
		current += 2


'''
	Задание 3. Аналогично предыдущему заданию, реализуйте генератор
	четных чисел.
'''
def gen_evens():
	current = 0
	while True:
		yield current
		current += 2


'''
	Задание 4. Используя генераторы четных и нечетных чисел, 
	написанные ранее, напишите генератор любых чисел gen_numbers.

	Каких именно чисел, зависит от аргумента even_or_odd.
	Если значение аргумента является строкой "even", то gen_numbers
	должен вести себя как gen_evens, если "odd", то как gen_odds.

	Если аргумент принял значение по умолчанию, то бишь None,
	тогда он должен генерировать числа от 0 до бесконечности,
	вызывая генерацию четных и нечетных чисел по очереди.

	Если же значение аргумента иное, тогда должна быть 
	вызвана ошибка ValueError.

	Подсказка: Заведите список используемых генераторов, в которых
	будут лежать либо только один из генераторов, написанных ранее
	или оба сразу. Затем можно итерировать по этому списку, чтобы
	обращаться к генераторам по очереди.
'''
def gen_numbers(even_or_odd=None):
	if even_or_odd is None:
		gens = [gen_evens(), gen_odds()]
	elif even_or_odd == "even":
		gens = [gen_evens()]
	elif even_or_odd == "odd":
		gens = [gen_odds()]
	else:
		raise ValueError(f"Неправильное значение аргумента even_or_odd: {even_or_odd}")
	while True:
		for gen in gens:
			yield next(gen)



'''
	Задание 4. Дан список имен и список фамилий. Напишите генератор,
	Который переберет все возможные комбинации имен и фамилий сгенерирует
	строки: Имя-Фамилия через пробел.

	Например: "John Brown"
'''


FIRST_NAMES = [
	"John", "Ann", "Hugo", "Gemima" "James",
	"Andrew", "Bob", "Alice", "Mary", "Victoria"
]	
FAMILY_NAMES = [
	"Brown", "Smith", "Cameron", "Dylan", "Douglas", "Parker",
	"Simpson", "Pearson", "Stevenson", "Carol", "Pasternak"
]


def gen_names():
	for name in FIRST_NAMES:
		for surname in FAMILY_NAMES:
			yield f"{name} {surname}"



'''
	Задание 5. Напишите генератор my_range, который
	является генераторным эквивалентом range().

	Range имеет три параметра: 
		1) Start, то есть начало последоватльности
		2) Stop, то есть остановка. Значение, на котором надо закончить,
		   которое к тому же не включено в последовательность.
		3) Step, то есть шаг последовательности.

	Важно понимать, что ели мы хотим написать полный аналог range(),
	то нужно учесть все возможные инициализации, то есть варианты создания range.
	Если мы отправляет один аргумент, то это значение присваивается параметру Stop,

	Если вызываем range с двумя аргументами, то это Start и Stop соответственно.
	Если три аргумента, то это Start, Stop и Step, то есть в таком порядке.

	Как можно заметить, первый аргумент может быть как и началом, так и 
	остановкой последвательности. Поэтому нужно поработать со значениями по умолчанию.

	Если порядковый аргумент не указан, значит он принимает значение по умолчанию,
	тогда можно понять количество вызванных аргументов.

'''
def my_range(first, second=None, step=1):

	# Инициализация
	start = 0
	end = None
	if second is None:
		end = first
	else:
		start = first
		end = second

	# Генерация
	current = start
	while current < end and step > 0 or current > end and step < 0:
		yield current
		current += step

'''
	Задание 6. Напишите тривиальный генератор простых чисел.
	Число является простым, если оно делится только на само себя
	или на единицу. Например 2, 5, 11, 23.

	Подсказка: Тривиальная реализация заключается в том, что
	каждое целое число, начиная с 2, проверяется на предмет того,
	простое ли оно, и если оно таковым является, то число выдается
	генератором.

	Задание 6.1. Напишите вспомогательную функцию is_prime, которая
	получает на вход число и возвращает True, если данное число простое,
	иначе возвращает False.

	Подсказка. Чтобы проверить данное число на простоту по определению, можно перебрать
	все числа, кроме данного и единицы, и посмотреть, делится ли данное на них или нет.
	Понятно, что не имеет смысла проверять числа больше данного, 
	так как оно точно не будет делиться. Но на самом деле можно не проверять числа больше
	квадратного корня от данного, так как квадратный корень от числа, если он целый, это
	наибольший возможный делитель данного числа. Чтобы найти квадратный корень числа,
	можно воспользоваться функцией math.sqrt.

	Резюме подсказки: Проверьте все числя от 2 до math.sqrt(n).
'''
def is_prime(n):
	for i in range(2, 1 + int(math.sqrt(n))):
		if n % i == 0 and n != i:
			return False
	return True


'''
	Задание 6.2 Используя функцию is_prime для проверки простоты чисел,
	Напишите сам генератор чисел.
'''
def gen_primes():
	current = 2
	while True:
		if is_prime(current):
			yield current
		current += 1



'''
	Задание 7. Реализуйте генерацию определенного числа паролей нужной длины. 

	Даны наборы символов, а именно буквы, заглавные и маленькие,
	а также цифры и специальные символы. Дана также минимальная требуемая
	величина пароля, равная 8 символам.
'''
LETTERS_LOWER = "qwertyuiopasdfghjklzxcvbnm"
LETTERS_UPPER = "QWERTYUIOPASDFGHJKLZXCVBNM"
DIGITS = "0123456789"
SPECIALS = "~`!@#$%^&*()_+-={}[]|\\/:;\"'<>.,"
NUMBER_OF_CHARSETS = 4
MINIMUM_PASSWORD_SIZE = 8


'''
	Задание 7.1
	Напишите функцию password_policy_satisfied, проверяющую пароль на предмет того, 
	соответствует ли он необходимым мерам безопасности, а именно:

	Пароль обязан иметь хотябы одну букву и в верхнем, и в нижнем регистре,
	хотя бы один специальный символ и одну цифру.
	
	Подсказка: Пройдитесь по каждому из данных наборов символов и проверьте,
	присутствует ли в пароле хоть один из символов этого набора. Это можно
	сделать с помощью функции any и конструкцией list comprehension.
	Затем убедитесь в верности каждого условия с помощью функции all.
'''
def password_policy_satisfied(password):
	contains_lower = any([char in password for char in LETTERS_LOWER])
	contains_upper = any([char in password for char in LETTERS_UPPER])
	contains_digit = any([char in password for char in DIGITS])
	contains_special = any([char in password for char in SPECIALS])
	return all([contains_lower, contains_upper, contains_digit, contains_special])


'''
	Задание 7.2
	Реализуйте функцию generate, которая принимает число, означающее длину пароля,
	а возвращает случайную последовательность символов соответствующей длины.

	Не нужно делать проверку на соответствие проверке безопасности. Это можно сделать
	в задании 7.3

	Подсказка. Используйте функцию random.randint для выбора случайного набора символов,
	буквы, цифры или специальные, а затем с помощью этой же функции выберите случайный
	символ в наборе. Так можно сделать столько раз, сколько симмволов 
	указано в аргументе функции.
'''
def generate(length):
	password = ""
	for j in range(length):
		charsets = [
			LETTERS_LOWER,
			LETTERS_UPPER,
			DIGITS,
			SPECIALS
		]
		charset = charsets[random.randint(0, NUMBER_OF_CHARSETS - 1)]
		rand_index = random.randint(0, len(charset) - 1)
		password += charset[rand_index]
	return password


'''
	Задание 7.3
	Используя две предыдущие функции напишите генератор паролей.
	На вход подаются два аргумента, длина пароля, и количество паролей.
	Необходимо сгенерировать нужное количество паролей, соответствующее
	политике безопасности. 

	Нужно также убедиться, что указанная длина
	не меньше чем значение константы MINIMUM_PASSWORD_SIZE.	
	В противном случае необходимо вызвать ValueError.

	Подсказка. Это конечно не оптимальный вариант решения, но сойдет.
	Если сгенерированный пароль не соответствует требованиям безопасности,
	то его можно не выдавать инструкцией yield, а попробовать сгенерировать
	еще раз, и так, пока не сгенерируется Удовлетворительный пароль.
'''
def gen_passwords(length, num_passwords):
	if length < MINIMUM_PASSWORD_SIZE:
		raise ValueError("length too short")
	for i in range(num_passwords):
		password = ""
		while not password_policy_satisfied(password):
			password = generate(length)
		yield password