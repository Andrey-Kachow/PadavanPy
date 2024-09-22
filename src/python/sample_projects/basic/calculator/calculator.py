import math


def exponentiation(number, exponent):
    result = 1
    for x in range(exponent):
        result *= number
    return result


print("Добро пожаловать в калькулятор")
previous_answer = None

while True:
    x = int(input("Введите первое число  (или 'ans' для предыдущего ответа): "))
    y = int(input("Введите второе число (или 'ans' для предыдущего ответа): "))

    if x.lower() == "ans" and previous_answer is not None:
        x = previous_answer
    else:
        x = int(x)

    if y.lower() == "ans" and previous_answer is not None:
        y = previous_answer
    else:
        y = int(y)

    operation = input("Введите оператор ")

    if operation == "+":
        answer = x + y
    elif operation == "-":
        answer = x - y
    elif operation == "*":
        answer = x * y
    elif operation == "/":
        answer = x / y
    elif operation == "mod":
        answer = x % y
    elif operation == "^":
        answer = exponentiation(x, y)
    elif operation == "log":
        answer = math.log(x, y)
    elif operation == "max":
        answer = max(x, y)
    elif operation == "min":
        answer = min(x, y)
    elif operation == "avg":
        answer = (x + y) / 2
    elif operation == "pythagoras":
        answer = math.sqrt(x ** 2 + y ** 2)
    else:
        print(f"Операция {operation} не поддерживается")
        continue

    print(f"Ответ: {answer}")
    previous_answer = answer

    z = input("Хотите ли вы продолжить? ")
    if z.lower() == "нет":
        break
print("Спасибо за использование")