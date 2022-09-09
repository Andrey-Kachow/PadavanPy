from trie import Trie
import random

def get_random_strings():
    for i in range(10000):
        s = ""
        for j in range(random.randint(3, 13)):
            s += chr(random.randint(65, 90))
        yield s

def calc_list_of_strings_size(strings):
    total = 0
    for s in strings:
        total += len(s)
    return total

def print_summary():
    print(f"word count: {count}")
    print(f"list size: {calc_list_of_strings_size(l)} bytes")
    print(f"trie size: {t.size()} bytes")
    print()

count = 0
l = []
t = Trie()

print_summary()
for string in get_random_strings():
    l.append(string)
    t.insert_str(string)
    count += 1
    print_summary()

print("checking equivalence...")
for word in l:
    if not t.contains(word):
        print("nope.", word)
        break
else:
    print("done. All ok")


print("A different example")

count = 0
l = []
t = Trie()

for string in [str(num) for num in range(100000)]:
    l.append(string)
    t.insert_str(string)
    count += 1
    print_summary()
