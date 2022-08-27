from search import *
import time
import random

def get_size():
    for power in range(1, 16):
        for value in range(1, 10):
            yield value * 10 ** power


for search_algorithm in [binary_search, linear_search]:

    print(f"Проверка скорости работы {search_algorithm.__name__}")

    for size in get_size():

        skip_alg = False

        sorted_list = range(size)

        print(f" Производительность {search_algorithm.__name__} на списке размера {size}. ", end="")

        start = time.time()
        search_algorithm(size + 1, sorted_list)
        end = time.time()

        elapsed_time = end - start
        print("Потребовалось %02.03f секунд" % elapsed_time)
        if elapsed_time > 2:
            print("-------- Слишком долго дальше ждать. Прерываем --------------")
            skip_alg = True
            break

        if skip_alg == True:
            break

    print()
    print()
    print()
    print()
