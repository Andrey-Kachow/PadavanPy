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

	# Чтобы регистр исходных данных не влиял на результат, необходимо привести строки к общему регистру,
	# неважно, к верхнему или нижнему. Применение методов lower() или upper() в помощь.

	query1 = query1.lower()  # Выражение с использованием query1
	query2 = query2.lower()  # Выражение с использованием query2
	query3 = query3.lower()  # Выражение с использованием query3
	query4 = query4.lower()  # Выражение с использованием query4

	# Возможно, стоит написать еще одну строчку кода. Вот она
	content = content.lower()

	if all([query1 in content, query2 in content, query3 in content, query4 in content]):
		print("Отлично! Поисковик заработал. Упражнение выполнено успешно!")
	else:
		print("К сожалению, что-то пошло не так.")


def ex_12_5_lambda():

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


	is_odd = lambda x: bool(x % 2)


	# Проверка:

	if is_odd(1) and not is_odd(2) and is_odd(1235):
		print("is_odd: Верно! Хорошая работа!")
	else:
		print("is_odd: К сожалению, что-то пошло не так")
	print()



	# Задание: Используя, is_odd, напишите функцию no_evens, которая принимает список чисел,
	# и возвращает True если в нем нет четных чисел


	no_evens = lambda nums: all(map(is_odd, nums))


	# Проверка:

	if no_evens([1, 3, 7, 5]) and not no_evens([1, 2, 4]):
		print("no_evens: Верно! Хорошая работа!")
	else:
		print("no_evens: К сожалению, что-то пошло не так")
	print()


def ex_12_5_dict():
	'''
		Запуск кода:

		> python -c "from module_12_answers import *; ex_12_5_dict()"

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

	# Функциональный способ без циклов и условных предложений. Страшный и не обязательный.
	get_type = lambda grocery_item: grocery_item["type"]
	get_price = lambda grocery_item: grocery_item["price"]

	regular_price = lambda shopping_list: sum(map(get_price, shopping_list))

	types = lambda shopping_list: list(map(get_type, shopping_list))

	is_valid_meal = lambda shopping_list: all([
		len(types(shopping_list)) == 3,
		"main course" in types(shopping_list),
		"snack" in types(shopping_list),
		"drink" in types(shopping_list)
	])

	deal_price = lambda shopping_list: MEAL_DEAL_PRICE if is_valid_meal(shopping_list) else None

	price = lambda shopping_list: deal_price(shopping_list) or regular_price(shopping_list)

	print(f"Стоимость покупок Андрея: { price(shopping_list_andrey) }")
	print(f"Стоимость покупок Маши: { price(shopping_list_masha) }")
