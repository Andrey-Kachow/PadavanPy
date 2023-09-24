import sys

counts = {}

for token in sys.stdin.read().split():
    if int(token) not in counts.keys():
        counts[int(token)] = 1
    else:
        counts[int(token)] += 1

for i in range(0, max(counts.keys()) + 1):
    print(i, "\t", counts.get(i, 0), "\t", "*" * counts.get(i, 0))
    
print(counts)
