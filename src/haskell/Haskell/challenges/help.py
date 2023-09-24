with open("reinforcement.txt") as f:
    with open("Dictionary.hs", "w") as d:
        l = []
        for line in f:
            l.append(tuple(line.strip().split()[:3]))
        for tup in l:
            d.write(", " + str(tup).replace("\'", "\"") + "\n")
