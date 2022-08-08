
# Sometimes error may occur when executing the error

# some_stuff = [1, "jopa", 25, {"name": "Andrey"}]
# print(some_stuff[100])





# # Use try-except statements
# try:
# 	some_stuff = [1, "jopa", 25, {"name": "Andrey"}]
# 	print(some_stuff[100])
# except IndexError:
# 	print("jopa")





# # "except" without error name means code will be executed if some other error occur
# try:
#  	print(some_undefined_variable)
# except NameError:
#  	print("Variable some_undefined_variable is not defined")
# except:
#  	print("Something else went wrong")





# # "else" defines a block of code which will be executed if no errors occured
# try:
# 	print("Hello")
# except:
# 	print("Something went wrong")
# else:
# 	print("Nothing went wrong")





# # "finally" keyword defines a block of code which will be executed in any case, no mater if errors occured or not
# try:
# 	print(x)
# except:
# 	print("Something went wrong")
# finally:
# 	print("The 'try except' is finished")





# # Practical "finally" usage example
# try:
# 	f = open("demofile.txt", "w+")
# 	f.write("Lorum Ipsum")
# except:
# 	print("Something went wrong when writing to the file")
# finally:
# 	f.close()





# # "raize" keyword is used to break the program in case if it acts incorrectly in the programmer point of view
# x = -1
# if x < 0:
# 	raise Exception("Sorry, no numbers below zero")
# x = "hello"
# if not type(x) is int:
# 	raise TypeError("Only integers are allowed")
