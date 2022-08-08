
# # Use "def" key word to define function
# def my_function():
	# print("Hello from a function!")

# # to run the function you must call it
# my_function()





# # Variables can be declaired inside the functions. Such variables are called local variables
# def local_var_example():
# 	my_local_var = 33
# 	print(my_local_var)

# local_var_example()







# # Variables in the global scope are called global variables. 
# def variable_confusion():
# 	jopa = 10  # local jopa
# 	print(jopa)

# jopa = 20  # global jopa

# variable_confusion()

# print(jopa, "Why not 10?")







# # Use "global" keyword if the function changes global variable
# def magic():
# 	# global my_global_var

# 	print(my_global_var)

# 	my_global_var = 12

# 	print(my_global_var)

# my_global_var = 10
# magic()
# print(my_global_var)







# # Functions can have arguments (or they are also called papameters)
# def popov_family(name):
# 	print(name.capitalize() + " " + "Popov")

# popov_family("andrey")
# popov_family("Kirill")
# # popov_family("Nora") # ?






# # Keyword argument syntax
# def Adiyan_Soldatov_family(name):
# 	if name.lower() in ["tatiana", "tatyana"]:
# 		print(name.capitalize() + " " + "Soldatova")
# 	else:
# 		print(name.capitalize() + " " + "Adiyan")

# Adiyan_Soldatov_family(name="Nora")

# Example with print()
# print("a", "b", "c", sep="--", end="-<>-\n")







# # Arbitrary arguments   *args
# def list_all(*fruits):
# 	for fruit in fruits:
# 		print(fruit)

# list_all("Banana", "Apple")
# print()
# list_all("Melon", "Pineapple", "Mango", "Pear", "...")







# # Arbitrary keyword arguments   **kwargs
# def vegetable_description(**properties):
# 	print(properties['color'].capitalize(), properties['quality'], properties['taste'], properties['name']) 

# vegetable_description(name="Banana", quality="fresh", taste="sweet", color="yellow")
# print()
# vegetable_description(name="Banana", quality="fresh", taste="sweet", color="yellow", length="15cm")







# # Default value for the argument. Such arguments must be written after other arguments
# def display_message(message, repetitions=1):
# 	for rep in range(repetitions):
# 		print()
# 		print(message)
# 		print()


# display_message("Attention! I LOVE NORA!!!")
# print("---")
# display_message("I can't live without kissing Nora", 10)








# # "return" keyword allows variables to take the value of the function
# def add_two_numbers(a, b):
# 	return a + b


# s = add_two_numbers(10, 4)

# print(s)









# # Recursion. Function calls itself
# def rec(start, counter):
# 	counter -= 1
# 	print("Hello from function. I am on level {} of recursion".format(start - counter))
# 	if counter > 0:
# 		rec(start, counter)

# rec(20, 20)







# def fibonacci(index):
# 	if index == 0 or index == 1:
# 		return index
# 	else:
# 		return fibonacci(index - 1) + fibonacci(index - 2)

# F_1 = fibonacci(1)
# F_30 = fibonacci()
# print(F_1, F_30)








# # Be careful! There's a recursion depth limit
# def prepare_for_trouble():
# 	print("HAHAHAAHAHAAHHAHAHAHAHAHAH")
# 	and_make_it_double()

# def and_make_it_double():
# 	print("BUGAGA! BUGAGA! BUGAGA!")
# 	prepare_for_trouble()


# prepare_for_trouble()







# # Functions them selves can be stored in variables
# def some_function():
# 	print("Andrey is a sexy gorilla!")

# important_fact = some_function

# print(important_fact)
# important_fact()

# print(important_fact())








# # Closure

# def family_function_creator(family_name):

# 	def family_function(name):
# 		print(name.capitalize() + " " + family_name)

# 	return family_function


# ivanov_family = family_function_creator("Ivanov")
# sidorov_family = family_function_creator("Sidorov")

# ivanov_family("Ivan")
# ivanov_family("sergey")

# sidorov_family("Oleg")
# sidorov_family("Evgeny")








# # Use "lambda" keyword to create small anonymous functions. lambda arguments : expression

# y = lambda x : x + 10

# print(y(5))

# f = lambda a, b : a * b

# print(f(5, 6))








# # "lambda" closure

# def multiplier(n):
#  	return lambda a : a * n


# doubler = multiplier(2)
# tripler = multiplier(3)


# print(doubler(11))
# print(tripler(11))
