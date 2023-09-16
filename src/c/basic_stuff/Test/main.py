print("Please, enter your name:")
name = input()

print("Please, enter your age:")
age = int(input())

if age < 18:
    print(name + " cannot drive.")
else:
    print(name + " can drive legally.")


#    0 => 0
#    1 => 1 = 1     = 1 * (2^0)
#   10 => 2 = 2 + 0 = 1 * (2^1) + 0 * (2^0)
#   11 => 3
#  100 => 4
#  101 => 5
#  110 => 6
#  111 => 7
# 1000 => 8
# ...


# 1210 0101 

# 00000000
# ...
# 11111111 = 255

# 2^7 + 2^6 + ... + 2^0 = 128 + 64 + 32 + 16 + ... + 1 = 255

