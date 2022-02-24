from sep import pretty_print_separation_between_demos_dont_pay_much_attention_to_me




# Iterating through the list
fruits = ["apple", "banana", "cherry"]
for fruit in fruits:
  print(fruit)





pretty_print_separation_between_demos_dont_pay_much_attention_to_me()






# Iterating through the string:
for character in "banana":
  print(character)






pretty_print_separation_between_demos_dont_pay_much_attention_to_me()





# range() function for the sequence of numbers
print( range )

print( range(10) )

print( list( range(10) ) )

print( list(range(3, 10)) )

print( list(range(0, 10, 2)) )

print( list(range(30)) )






pretty_print_separation_between_demos_dont_pay_much_attention_to_me()






# Doing something several times
for i in range(10):
	print(i)





pretty_print_separation_between_demos_dont_pay_much_attention_to_me()





# Nested loops

for x in range(10):
	for y in range(10):
		print(x, y)


for adjective in ["red", "big", "tasty"]:
	for fruit in ["apple", "banana", "cherry"]:
		print(adjective, fruit)




pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




# Tuple assignment
a, b = 10, 20
print(a)
print(b)

# swapping two variable values
a, b = b, a
print(a)
print(b)




pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




# Two variables "for" loop
for y, x in ((0, 0), (1, 0), (-1, 0), (0, 1), (0, -1)):
	print(x)
	print(y)
	print()





pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




# Looping through dictionaries
for item in {1: 5, 2: 10}:
	print(item)
	# prints 1, 2





pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




big_dic = {1: 5, 2: 10}

for item in big_dic:
	print(big_dic[item])
	# prints 5, 10






pretty_print_separation_between_demos_dont_pay_much_attention_to_me()





# Get a list of keys of a dictionary with .keys() method
heroes = {"Batman": "Bruce Wayne", "Spider Man": "Peter Parker", "Ironman": "Tony Stark"}
print(heroes)
print(heroes.keys())







pretty_print_separation_between_demos_dont_pay_much_attention_to_me()







# Iterating thruough the list of dictionary keys
for key in big_dic.keys():
	print(big_dic[key])






pretty_print_separation_between_demos_dont_pay_much_attention_to_me()





# "break" keyword
fruits = ["apple", "banana", "cherry"]
for fruit in fruits:
	if fruit == "banana":
		break
	print(fruit)





pretty_print_separation_between_demos_dont_pay_much_attention_to_me()






# "continue" keyword
fruits = ["apple", "banana", "cherry"]
for fruit in fruits:
	if fruit == "banana":
		continue
	print(fruit)





pretty_print_separation_between_demos_dont_pay_much_attention_to_me()





# "else" at the end of the loop executes its code if loop didn't run into "break" statement


print("without break")

for x in range(6):
	print(x)
	# if x == 3:
	# 	break
else:
	print("Finally finished!")


print("with break")

for x in range(6):
	print(x)
	if x == 3:
		print("breaking!")
		break
else:
	print("Finally finished!")





pretty_print_separation_between_demos_dont_pay_much_attention_to_me()





# new method for working with strings join()
print("-".join(["1", "2", "3", "4"]))






pretty_print_separation_between_demos_dont_pay_much_attention_to_me()




# List comprehension

# "for" key word used for generator statements
test_list = [num for num in range(10)]
print(test_list)







pretty_print_separation_between_demos_dont_pay_much_attention_to_me()





minimap = [["-" for x in range(20)] for y in range(20)]

print("\n".join(" ".join(minimap[row]) for row in range(20)))


