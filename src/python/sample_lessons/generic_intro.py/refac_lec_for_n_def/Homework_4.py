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

#---------------------------------############################### Проверка корректности date_1 переменных
if date_1_month == 2:
    if (date_1_year % 4 == 0 and date_1_year % 100 != 0) or (date_1_year % 400 == 0):
        max_day = 29
    else:
        max_day = 28
elif date_1_month in [4, 6, 9, 11]:
    max_day = 30
else:
    max_day = 31

if date_1_day >= 1 and date_1_day <= max_day and date_1_month >= 1 and date_1_month <= 12 and date_1_year >= 1:
    date_1_is_valid = True
else:
    date_1_is_valid = False

#--------------------########### Проверка корректности date_2 переменных

if date_2_month == 2:
    if (date_2_year % 4 == 0 and date_2_year % 100 != 0) or (date_2_year % 400 == 0):
        max_day = 29
    else:
        max_day = 28
elif date_2_month in [4, 6, 9, 11]:
    max_day = 30
else:
    max_day = 31

if date_2_day >= 1 and date_2_day <= max_day and date_2_month >= 1 and date_2_month <= 12 and date_2_year >= 1:
    date_2_is_valid = True
else:
    date_2_is_valid = False

#---------------------------------############################### Правильны ли даты?
if date_1_is_valid and date_2_is_valid:
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