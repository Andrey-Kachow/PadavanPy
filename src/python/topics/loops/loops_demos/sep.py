# You don't have to know how it works for now. But good job if you do!
# Ignore invocations of this functions, they are not a part of the demos
def pretty_print_separation_between_demos_dont_pay_much_attention_to_me():
	""" Function which prints newlines and a message
	    indicating that the output related to the previous
	    demonstration is over and the next piece of code
	    is executed """

	global demo_counter
	demo_counter += 1

	print("\n".join([
			f"\n\n\n\nEnd of the demo {demo_counter - 1}\n",
			"\n" * 4,
			"+----------------------------+",
			"|  Demonstration %3d begins! |",
			"+----------------------------+",
			"\n\n\n"
    	]))

demo_counter = 0