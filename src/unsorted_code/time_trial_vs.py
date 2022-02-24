import time
# from copy import deepcopy, copy
# import random
# import PIL
# import numpy as np
# from scipy.optimize import least_squares

def fib_rec(n):
    if n > 1:
        return fib_rec(n - 1) + fib_rec(n  - 2)
    else:
        return 1


def fib_wle(n):
    x = y = i = 1
    while i < n:
        x, y = y, x + y
        i += 1
    return y


for iter_num in [10 ** xxx for xxx in range(3, 11, 1)]:
    print("Testing {} iterations:".format(iter_num))
    start = time.time()
    for ii in range(iter_num):
        # ----------------------------------------------------------- 1st snippet
        fib_rec(100)
        # ----------------------------------------------------------- enter here
    end = time.time()
    print("   ", end - start)
    start = time.time()
    for iii in range(iter_num):
        # ----------------------------------------------------------- 2nd snippet
        fib_wle(100)
        # ----------------------------------------------------------- enter here
    end = time.time()
    print("   ", end - start)