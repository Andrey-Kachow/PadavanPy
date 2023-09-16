print("Please, enter your name:")
name = input()

print("Please, enter your age:")
age = int(input())

if age < 18:
    print(name + " cannot drive.")
else:
    print(name + " can drive legally.")

