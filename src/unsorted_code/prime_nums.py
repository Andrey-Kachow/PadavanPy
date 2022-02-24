from Fermats_lil import fermat_little_check

print("Please enter upper bound for the prime numbers")
candidates = list(range(1, int(input(">> ")) + 1, 1))
# print(candidates)
print("computing...")

start = 1
n = 0
while n < len(candidates):
    n = candidates[start]  # number after 1
    i = n + start
    while i < len(candidates):
        candidates[i] = None
        i += n
    while None in candidates:
        candidates.remove(None)
    start += 1
candidates.pop(0)

print("As a result, the following numbers are prime:")
for a in range(20):
    print("+" + "-" * (len(str(candidates[-1])) + 1), end="-")
print()
for i in range(len(candidates)):
    print("{}{}".format("| ", candidates[i]), end=" " + " "*(len(str(candidates[-1]))-len(str(candidates[i]))))
    if (i + 1) % 15 == 0:
        print()
        for a in range(20):
            print("+" + "-" * (len(str(candidates[-1])) + 1), end="-")
        print()
print("\nThere are {} of them!".format(len(candidates)))


