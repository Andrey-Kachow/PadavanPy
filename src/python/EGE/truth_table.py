
import itertools

table = [
    [0, 1, 1, 1, 0],
    [1, 0, 1, 0, 1],
    # [None, 0, 0, None, 1]
]

def F(x, y, z, w):
    return ((y <= w) == (x <= (not z))) and (x or w)

def Fd(st):
    return F(st['x'], st['y'], st['z'], st['w'])

for ordering in itertools.permutations('xyzw'):
    # print(f'trying {ordering}')
    matches = True
    for row in table:
        symbol_table = {}
        for i in range(4):
            symbol_table[ordering[i]] = row[i]
        if Fd(symbol_table) != row[-1]:
            matches = False
            break
    if matches:
        print(ordering)
