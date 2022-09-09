

def inv_nums_series_sum(limit):

    sum_front = 0.0
    for n in range(1, limit + 1):
        sum_front += 1 / n

    sum_back = 0.0
    for n in range(limit, 0, -1):
        sum_back += 1 / n

    print(f"{sum_front} = 1 + 1/2 + 1/3 + ... + 1/{limit - 1} + 1/{limit}")
    print(f"{sum_back} = 1/{limit} + 1/{limit - 1} + ... + 3 + 2 + 1")

    return not (sum_front == sum_back)


def find_limit():
    found = False
    current = 5
    while not found:
        found = inv_nums_series_sum(current)
        print()
        current += 1
