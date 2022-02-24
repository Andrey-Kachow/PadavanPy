import random
from sep import pretty_print_separation_between_demos_dont_pay_much_attention_to_me


# while <condition is true>:
# 	do something




# Do sertain action serveral times
counter = 0
while counter < 10:
	print(counter)
	counter = counter + 1





pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




# Get the value of number of items in the list
some_nums = [1, 2, 3]
length = len(some_nums)
print(some_nums, "has length", length)






pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




# loop through items in the list
groceries = ["Bananas", "Carrots", "Milk", "Eggs"]
index = 0
while index < len(groceries):
	print(groceries[index])
	index += 1





pretty_print_separation_between_demos_dont_pay_much_attention_to_me()



# generate random number
num = random.randint(0, 10)
print(num)




pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




# Doing something for unknown number of times
while random.randint(0, 10) > 0:
	print("I will do it one more time, because random number is not zero.")




pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




# New way of tring formatting using format() method
name = input("Please enter your name> ")

message1 = "Your name is {}.".format(name)
print(message1)

message2 = "{}, {}, {}, {}".format(name.lower(), name.upper(), name.capitalize(), name[-1])
print(message2)




pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




# Ensure that user enters correct data
print('Please, enter "a", "b", "c" or "d"')
entry = input()

while entry not in ["a", "b", "c", "d"]:

	print("{} is not a correct entry.".format(entry))
	print('Please, enter "a", "b", "c" or "d."')
	entry = input()




pretty_print_separation_between_demos_dont_pay_much_attention_to_me()






# Try to solve the problem, until it is not solved
problem_solved = False
while not problem_solved:

	print("What is the name of our planet?")
	answer = input("> ")
	if answer.lower() in ["earth", "the earth"]:
		problem_solved = True




pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




# Bellow are the snippets of code which will cause printing the same message other and other
# again and again. Because the condition expression alvays evalates to true
"""

>>> True
True
>>> 2 + 2 == 4
True

"""
# Do not uncomment infinite loops if you want to see demos afted it

# while True:
# 	print("forever...")

# while 2 + 2 == 4:
# 	print("I love Mathematics!")


# In fact sometimes we want our code to execute forever and maybe quit the process 
# if something happens.

# so...

# How to stop infinite loop? Or exit the loop in the middle of iteration? 






# Use "break" key work to stop the loop even if the condition is still True
a = 3
while a > 0:

	if a == 420:
		break

	a = random.randint(1, 420)
	print(a)





pretty_print_separation_between_demos_dont_pay_much_attention_to_me()






# "continue" key word to go to the next iteration

i = 0
while i < 10:
	
	if i == 5:
		i = 6
		continue

	print(i, "not equal to 5")

	i += 1 





pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




# "else" statement with while loops. The code in idented after "else" will be excecuted if the condition is false (i.e. loop didn't "break")
i = 1
while i < 6:
	print(i)
	i += 1
else:
	print("i is no longer less than 6")
 
# "break" and "continue" and "else" also work for "for" loops
