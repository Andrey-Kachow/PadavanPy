"""

This is the special code for better displaying the demo files.
It will display the code snippets followed by its execution with outputs

run one of the following:

----windows

>  python output_and_code.py path/to/demo/python/file.py

or

----Mac or Linux

$  python3 output_and_code.py path/to/demo/python/file.py

"""

import sys


num_arguments = len(sys.argv)

print(f"You provided {num_arguments} arguments")

if num_arguments != 2:
	print("provide only the argument, which is a path to python file")
	sys.exit(-1)


separator = "pretty_print_separation_between_demos_dont_pay_much_attention_to_me()"
python_filename = sys.argv[-1]
snippets = []

print(f"Reading {python_filename} and looking for snippets...")

try:
	with open(python_filename, 'r') as f:
		snippets = f.read().split(separator)
except:
	print(f"Could not read {python_filename}. Please enter a valid python file")
	sys.exit(-1)


if snippets == []:
	print("Didn't find any snippets")
	sys.exit(-1)

for snippet in snippets:

	print("# Another example of python code")
	print()
	print(snippet)
	print("\n\n\n# The code above gives the following output:")
	print()
	exec(snippet)
	print("\n\n\n\n")
	print("# done.")


print("Finished all snippets!")


