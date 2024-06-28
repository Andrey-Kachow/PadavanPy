import random

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



def random_int_gen(lower, upper, quantity):
	for _ in my_range(quantity):
		yield random.randint(lower, upper)



def call_count(inner_func):
	call_counter = 0

	def wrapper(*args, **kwargs):
		nonlocal call_counter
		inner_func(*args, **kwargs)
		call_counter += 1
		print(f"Функция {inner_func} была вызвана {call_counter} раз!")
	
	return wrapper


@call_count
def test_callable():
	print("Я вызвана, даа")