'''
    Задание 1: Даны 3 переменные: day, month, year.
    в отмеченном блоке напишите код, который выведет "Да", если дата правильная и не является ошибкой, или "Нет" в противном случае.

    Например:
        31 10 1999 - верная дата. Такой день существует
        32 10 1999 - Неправильная дата. В октябре 31 день, но указано 32-е число.
        31 11 1999 - Неправильная дата. В ноябре 30 дней, но указано 31-е число.
        29 2 2024  - верная дата. Такой день был
        29 2 2023  - некорректная дата. 2023 год не является високосным. 

    Справка:
        Високосный год:
            Год, номер которого кратен 4 високосный.  Например 2004, 2008, 2012
            Но если номер кратен 100, тогда не високосный, несмотря на кратность 4-ем. 1800, 1900
            Если же кратен 400, то он високосный, несмотря на кратность 100-ам. Например 2000
'''
day = int(input())
month = int(input())
year = int(input())

answer = "I don't know"

################## Начало Вашего Кода #######################


################## Конец Вашего Кода ########################

print(answer)