'''
    Задание 4. Напишите программу -- доработку программы из задания 3, которая выведет сообщение об ошибке,
    если хотябы одна из двух дат является некорректной. Например 29/02/2017.
'''
date_1_day = int(input("date_1_day: "))
date_1_month = int(input("date_1_month"))
date_1_year = int(input("date_1_year: "))

date_2_day = int(input("date_2_day: "))
date_2_month = int(input("date_2_month: "))
date_2_year = int(input("date_2_year: "))

answer = "I don't know"

################## Начало Вашего Кода #######################

dates = [
    (date_1_day, date_1_month, date_1_year),
    (date_2_day, date_2_month, date_2_year)
]

date_validies = []

for date in dates:
    day, month, year = date
    
    if month == 2:
        if (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0):
            max_day = 29
        else:
            max_day = 28
    elif month in [4, 6, 9, 11]:
        max_day = 30
    else:
        max_day = 31

    if day >= 1 and day <= max_day and month >= 1 and month <= 12 and year >= 1:
        is_valid = True
    else:
        is_valid = False

    date_validies = date_validies + [is_valid]

    # date_validies.append(is_valid)

#---------------------------------############################### Правильны ли даты?
if all(date_validies):
    date_1 = (date_1_year, date_1_month, date_1_day)
    date_2 = (date_2_year, date_2_month, date_2_day)
    if date_1 < date_2:
        answer = "Первая дата раньше"
    elif date_1 > date_2:
        answer = "Первая дата позже"
    else:
        answer = "Обе даты одинаковые"
else:
    answer = "Является некорректной"


################## Конец Вашего Кода ########################

print(answer)