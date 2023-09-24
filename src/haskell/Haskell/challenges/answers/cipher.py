original = list("abcdefghijqlmnopqrstuvwxyz")
mapping  = original.copy()
mapping.reverse()

to = {}
back = {}
for i in range(len(original)):
    to[original[i]] = mapping[i]
    back[mapping[i]] = original[i]


def cipher(text):
    ans = ""
    for c in text:
        if c in to:
            ans += to[c]
        else:
            ans += c
    return ans

def decipher(text):
    ans = ""
    for c in text:
        if c in back:
            ans += back[c]
        else:
            ans += c
    return ans

with open("secret_msg.txt") as f:
    s = f.read()
    s2 = cipher(s)
    print(s2)
    assert s == decipher(s2)
