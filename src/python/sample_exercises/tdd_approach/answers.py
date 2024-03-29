import random

'''
    Реализуйте функцию сложения вух чисел,
    Хранящихся в параметрах first и second

    Параметр - это переменная, которая передается функции
               в качестве аргумента.

    Аргумент - значение или выражение, внутрь скобок при вызове функции.
               Например:

                         Аргумент
                            |
                 фунцкия    |
                    |       |
                    V       V
               my_function(123)
'''
def plus(first, second):
    return first + second


'''
    Реализуйте функцию сложения вух чисел,
    Хранящихся в параметрах first и second
'''
def minus(first, second):
    return first - second


'''
    Реализуйте функцию определения четности данного числа. Функция 
    должна вернуть True, если число четное, False, если не четное.
'''
def is_even(number):
    return number % 2 == 0


'''
    Напишите функцию, которая получает значение температуры
    в градусах цельсия и возвращает соответтвующее значение
    в кельвинах.

    Подсказка в виде таблички:

            Ввод   Результат
        +---------+---------+
        | Цельсий | Кельвин |
        +---------+---------+
        |    0    |   273   |  * Легитимное значения ввода
        +---------+---------+
        |   -273  |    0    |  * Легитимное значения ввода
        +---------+---------+
        |   100   |   373   |  * Легитимное значения ввода
        +---------+---------+
        |   -274  |    0    |  * Ошибка, отправляем аварийный 0
        +---------+---------+
        |   -999  |    0    |  * Ошибка, отправляем аварийный 0
        +---------+---------+
    
    Поскольку значение температуры в кельвинах не может быть
    меньше нуля
'''
def celsius_to_kelvin(temperature_degrees):
    ABSOLUTE_ZERO_TEMPERATURE = -273
    return max(0, temperature_degrees - ABSOLUTE_ZERO_TEMPERATURE)


'''
    Известно, что функция random.randint(x, y) 
    возвращает случайное целое число между x и y включительно.

    Используя random.randint(x, y),
    Напишите функцию, которая возвращает результат броска
    двух игральных костей (шестигранных кубиков D6).
'''
def throw_two_dice():
    first_result = random.randint(1, 6)
    second_result = random.randint(1, 6)
    return first_result + second_result