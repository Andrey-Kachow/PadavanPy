
# first version
def add_two_numbers(first_number, second_number):
    return first_number + second_number
  
# second version
def print_sum_of_two_input_numbers():
    first_number = int(input())
    second_number = int(input())
    print(first_number + second_number)


def format_text(person):
    '''
    Задание 2: Вывод текста с помощью print
    Дан список информации о человеке: [Фамилия, Имя, день рождения, месяц рождения, год рождения, Пол(М/Ж)]
    С помощью return вернуть текст про человека, сохраненного в переменную person.
    "<Имя> <Фамилия> является [мужчиной|женщиной] <Год> г. рождения. Возраст: <X>"
    возраст необходимо посчитать, используя переменную today.
    Например, если person примет значения person_1, необходимо вернуть:
    "Андрей Попов является мужчиной 1999 г. рождения. Возраст: 24"
    А если person_2:
    "Дарина Романова является женщиной 1970 г. рождения. Возраст: 54"
    '''
    first_name = person[0]
    last_name = person[1]
    birth_day = person[2]
    birth_month = person[3]
    birth_year = person[4]
    gender = person[5]

    current_day = today[0]
    current_month = today[1]
    current_year = today[2]
    age = current_year - birth_year

    if current_month < birth_month or current_month == birth_month and current_day < birth_day:
        age -= 1
    if gender.upper() == 'М':
        gender_text = "мужчиной" 
    else:
        gender_text = "женщиной"


    return ""


print(
    add_two_numbers(10, 20),
    add_two_numbers(10, 25),
    add_two_numbers(10, int(input()))
)

person_1 = ['Андрей', 'Попов', 31, 10, 1999, 'М']

print(format_text(person_1))