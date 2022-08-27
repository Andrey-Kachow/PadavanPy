from sorts import *
import time
import random

def get_size():
    for power in range(1, 8):
        for value in range(1, 10):
            yield value * 10 ** power


def randlist(size):
    sample = []
    for _ in range(size):
        sample.append(random.randint(0, 100))
    return sample



for sortalg in [bubble_sort, isort_rec, insertion_sort, quicksort, merge_sort]:
    for size in get_size():
        unsorted_list = randlist(size)

        print(f"testing problem of size {size} of {sortalg.__name__} algorithm")
        try:
            start = time.time()
            sortalg(unsorted_list)
            end = time.time()
            elapsed_time = end - start
            print(f"  it took {elapsed_time} seconds!\n")
            if elapsed_time > 5:
                print(f"takes too long. no longer testing {sortalg.__name__}")
                break
        except Exception as e:
            print("Error occured!", e)
            break
