def exercise_12_7_3():

    '''
        Дан словарь соответствия названий банков и процентная ставка в
        этом банке, а также пользователь вводит сумму денежного вклада через терминал.

        Необходимо посчитать годовую прибыль в каждом из банков и записать их в список,
        после чего вывести список на экран.
    '''

    per_cent = {'ТКБ': 5.6, 'СКБ': 5.9, 'ВТБ': 4.28, 'СБЕР': 4.0}

    money = int(input("Пожалуйста, введите сумму вклада >>> "))



def exercise_13_8_19():

    '''
        Продаются билеты на конференцию. Пользователь вводит количество билетов и возраст
        каждого участника конференции. Стоимость одного билета зависит от возраста.

            Моложе 18 лет - бесплатно
            От 18-24 лет  - 900 рублей
            Старше 25 лет - 1390 рублей

        Если куплено более 3 билетов, тогда покупатель получает скидку 10 процентов.

        Задача в том, чтобы посчитать стоимость покупки и вывести ее на экран.
    '''

    num_tickets = int(input("Пожалуйста, введите сколько билетов желаете приобрести.\n> "))

    # ages = ...


if __name__ == '__main__':

    exercise_13_8_19()
