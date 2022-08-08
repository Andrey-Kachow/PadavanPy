import random

def ex_12_4_rev():
	'''
		Данное упражнение предназначено только для запуска, а не написания кода.
		Запустите функцию ex_12_4_rev следующим образом в терминале или командной строке

		> python

		>>> from module_12_revision import *
		>>> ex_12_4_rev()

		Или одной единственной командой, приведенной ниже

		> python -c "from module_12_revision import *; ex_12_4_rev()"
	'''

	s = "0123456789"

	while True:

		l = random.randint(0, 9)
		u = random.randint(0, 9)
		i = random.randint(-2, 3) or 1

		upper = max(u, l)
		lower = min(u, l)

		with_increment = i != 1 and random.randint(0, 2)
		expected = None

		if with_increment:
			if i < 0:
				expected = f"s[{upper}:{lower}:{i}]"
			else:
				expected = f"s[{lower}:{upper}:{i}]"
		else:
			expected = f"s[{lower}:{upper}]"

		try:
			res = eval(expected)
			if not res:
				continue

			print()
			print(f"Переменная s равна \"{s}\"")
			expr = input(f"Введите такое выражение вида s[...], чтобы его значение равнялось {repr(eval(expected))}.\n> ")

			try:
				eval(expr)
			except:
				print("Спасибо за использование программы.")
				break

			print()

			if eval(expr) == eval(expected) and 's[' in expr and ']' in expr:
				print("Верно")
			else:
				print("Не верно")
				print(f"Правильный ответ: {expected}")
		except:
			pass


def ex_12_4_search():

	'''
		Задание упрощенной реализации поиска по тексту.
		Дано 4 вида похожих запроса query1..query4, а также текст, в котором встречается это слово.
		Однако если запустить код без изменений, слова в тексте не найдутся.
		Необходимо провести преобразования над имеющимися данными, чтобы можно было осуществить
		нечувствительный к регистру поиск запросов внутри тектса.
		То есть, чтобы сочетания заглавных и маленьких букв не влияло на результат применения оператора `in`.
	'''

	query1 = "ежик"
	query2 = "ЕЖиК"
	query3 = "ежиК"
	query4 = "ЕЖИК"

	content = """
		Всё тело ежа покрыто иголками (кроме брюшка, мохнатой мордочки и пушистых лапок).
		Глаза у колючего – словно две черные блестящие бусинки.
		Ежик видит плохо, зрение у него слабое.
		Нос у ежа всегда влажный.
	"""

	# TODO:


def ex_12_5_lambda():

	'''
		Запуск кода:

		> python -c "from module_12_revision import *; ex_12_5_lambda()"
	'''

	# lambda examples:

	# Синтаксис анонимной функции:
	# lambda <название_аргумента>: <выражение>

	square = lambda x: x * x

	print("square = lambda x: x * x")
	print(f"результатом вычисления выражения square(4) является {square(4)}")
	print(f"square(4) ---> 4 * 4 ---> {square(4)}")

	print(f"результатом вычисления выражения list(map(square, [1, 2, 3])) является {list(map(square, [1, 2, 3]))}")

	# Other examples:

	successor = lambda n: n + 1

	half = lambda num: num / 2

	mul = lambda factor1, factor2: factor1 * factor2

	string_to_lowercase = lambda s: s.lower()


	print()
	print("Упражнения is_odd и no_evens")
	print()


	# Задание: Напишите функцию is_odd, которая принимает одно число,
	# и возвращает True если число нечетное, а в противномслучае возвращает False


	# TODO


	# Проверка:

	if is_odd(1) and not is_odd(2) and is_odd(1235):
		print("is_odd: Верно! Хорошая работа!")
	else:
		print("is_odd: К сожалению, что-то пошло не так")
	print()



	# Задание: Используя, is_odd, напишите функцию no_evens, которая принимает список чисел,
	# и возвращает True если в нем нет четных чисел


	# TODO


	# Проверка:

	if no_evens([1, 3, 7, 5]) and not no_evens([1, 2, 4]):
		print("no_evens: Верно! Хорошая работа!")
	else:
		print("no_evens: К сожалению, что-то пошло не так")
	print()


def ex_12_5_dict():
	'''
		Запуск кода:

		> python -c "from module_12_revision import *; ex_12_5_dict()"

		Задание: Маша и Андрей отовариваются в продуктовом магазинчике,
		где действует акция "Meal Deal", согласно которой, можно взять
		одно основное блюдо (main course), одну легкую закуску (snack) и один напиток (drink),
		и такая комбинация будет стоить фиксированную цену в 350 рублей,
		что выходит дешевле, чем брать товары по отдельности.

		Дано два набора продуктов, в кажом из которых три товара, у которых есть
		название (name), цена (price) и тип (type),
		который может быть либо основным блюдом (main course), легкой закуской (snack) идт напитком (drink)

		Задача состоит в том, чтобы написать программу, которая определит,
		сколько будет стоить каждый набор продуктов с учетом возможной акции

	'''

	MEAL_DEAL_PRICE = 350

	shopping_list_andrey = [
		{
			"name": "BLT sandwich",
			"price": 250,
			"type": "main course"
		},
		{
			"name": "crisps",
			"price": 100,
			"type": "snack"
		},
		{
			"name": "apple juice",
			"price": 150,
			"type": "drink"
		},
	]

	shopping_list_masha = [
		{
			"name": "Mixed Fruits salad",
			"price": 300,
			"type": "main course"
		},
		{
			"name": "Granola",
			"price": 200,
			"type": "main course"
		},
		{
			"name": "Smart water",
			"price": 50,
			"type": "drink"
		},
	]

	# TODO
