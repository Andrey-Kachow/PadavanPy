# This application works properly
import time
from copy import deepcopy

def display(arr):
	for row in range(9):
		if row % 3 == 0:
			print("+---+---+---+")
		line = ""
		for col in range(9):
			if col % 3 == 0:
				line += "|"
			elem = arr[row][col]
			if type(elem) is int:
				line += str(elem)
			else:
				line += " "
		print(line + "|")
	print("+---+---+---+")


def initialize(arr, string_representation=""):
	if len(string_representation) == 81:
		index = 0
		for row in range(9):
			for col in range(9):
				inp = int(string_representation[index])
				index += 1
				if  0 < inp < 10:
					field[row][col] = inp
				else:
					field[row][col] = [candidate for candidate in range(1, 10)]
	else:
		for row in range(9):
			for col in range(9):
				inp = int(input("{},{}> ".format(row, col)))
				if  0 < inp < 10:
					field[row][col] = inp
				else:
					field[row][col] = [candidate for candidate in range(1, 10)]
				display(field)
	display(field)


def narrow_candidates(arr, row, col):
	candidates = arr[row][col]
	if type(candidates) is list:
		for y in range(1, 9):
			not_candidate = arr[row - y][col]
			if not_candidate in candidates:
				candidates.remove(not_candidate)

		for x in range(1, 9):
			not_candidate = arr[row][col - x]
			if not_candidate in candidates:
				candidates.remove(not_candidate)

		for y in range(-(row % 3), 3 - row % 3):
			for x in range(-(col % 3), 3 - col % 3):
				not_candidate = arr[row + y][col + x]
				if not_candidate in candidates:
					candidates.remove(not_candidate)

		if len(candidates) == 1:
			arr[row][col] = candidates[0]


def guess_by_exclusion(arr, row, col):
	candidates = arr[row][col]
	if type(candidates) is list:
		num = None
		for candidate in candidates:

			presence = 1
			for y in range(1, 9):
				try:
					if candidate in arr[row - y][col]:
						presence += 1
				except TypeError:
					pass
			if presence == 1:
				num = candidate
				print(row, col, ":", num)

			presence = 1
			for x in range(1, 9):
				try:
					if candidate in arr[row][col - x]:
						presence += 1
				except TypeError:
					pass
			if presence == 1:
				num = candidate
				print(row, col, ":", num)

			presence = 0
			for y in range(-(row % 3), 3 - row % 3):
				for x in range(-(col % 3), 3 - col % 3):
					try:
						if candidate in arr[row + y][col + x]:
							presence += 1
					except TypeError:
						pass
			if presence == 1:
				num = candidate
				print(row, col, ":", num)
		if num:
			arr[row][col] = num
			narrow_candidates_in_each_cell(arr)


def narrow_candidates_in_each_cell(arr):
	for row in range(9):
		for col in range(9):
			narrow_candidates(arr, row, col)


def check_complete_row_column_square(row, col, playground):
	if col == 8:
		checks = 0
		for num in range(1, 10):
			if num in playground[row]:
				checks += 1
		if checks != 9 or sum(playground[row]) != 45:
			return False

	if row == 8:
		total = 0
		for y in range(9):
			total += playground[row - y][col]
		checks = 0
		column = [playground[row - y][col] for y in range(9)]
		for num in range(1, 10):
			if num in column:
				checks += 1
		if checks != 9 or total != 45:
			return False

	if row % 3 == col % 3 == 2:
		total = 0
		checks = 0
		square = []
		for y in range(3):
			for x in range(3):
				total += playground[row - y][col - x]
				square.append(playground[row - y][col - x])
		for num in range(1, 10):
			if num in square:
				checks += 1
		if checks != 9 or total != 45:
			return False

	return True


def check(row, col, playground):
	if not check_complete_row_column_square(row, col, playground):
		return False

	for num in range(1, 10):
		presence = 0
		for x in range(col + 1):
			if num == playground[row][col - x]:
				presence += 1
		if presence > 1:
			return False

	for num in range(1, 10):
		presence = 0
		for y in range(row + 1):
			if num == playground[row - y][col]:
				presence += 1
		if presence > 1:
			return False

	cells_in_square = 3 * (row % 3) + (col % 3) + 1
	square_origin = (row - row % 3, col - col % 3)
	for num in range(1, 10):
		presence = 0
		for small_pointer in range(cells_in_square):
			small_row = small_pointer // 3
			small_col = small_pointer % 3
			if num == playground[square_origin[0] + small_row][square_origin[1] + small_col]:
				presence += 1
		if presence > 1:
			return False

	return True
	

def try_option(pointer, arr, playground):
	global solved_game
	if pointer < 81 and not solved_game:
		row = pointer // 9
		col = pointer % 9
		try:
			for option in arr[row][col]:
				playground[row].append(option)
				if check(row, col, playground):
					try_option(pointer + 1, arr, playground)
				playground[row].pop()
		except TypeError:
			playground[row].append(arr[row][col])
			if check(row, col, playground):
				try_option(pointer + 1, arr, playground)
			playground[row].pop()
	else:
		if check(8, 8, playground):
			print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
			display(playground)
			arr = deepcopy(playground)
			solved_game = True


def try_every_permutation(arr):
	pointer = 0
	playground = [[] for row in range(9)]
	try_option(pointer, arr, playground)


def solve(arr):
	extra_arr = deepcopy(arr)
	narrow_candidates_in_each_cell(arr)
	for row in range(9):
		for col in range(9):
			guess_by_exclusion(arr, row, col)
	if extra_arr == arr:
		try_every_permutation(extra_arr)
		arr = deepcopy(extra_arr)


field_str = "800000000003600000070090200050007000000045700000100030001000068008500010090000400"
field = [[0 for i in range(9)] for j in range(9)]

initialize(field, field_str)
solved_game = False
while not solved_game:
	solve(field)




# def solved(arr):
# 	for row in arr:
# 		for elem in arr:
# 			if type(elem) is list:
# 				return False
# 	for row in arr:
# 		if sum(row) != 45:
# 			return False
# 	return True

# def guess_by_exclusion(arr, row, col):
# 	candidates = arr[row][col]
# 	num = None
# 	if type(candidates) is list:
# 		for candidate in candidates:
# 			if not num:
# 				presence = 1
# 				for y in range(1, 9):
# 					try:
# 						if candidate in arr[row - y][col]:
# 							presence += 1
# 					except TypeError:
# 						pass
# 				if presence == 1:
# 					num = candidate

# 				presence = 1
# 				for x in range(1, 9):
# 					try:
# 						if candidate in arr[row][col - x]:
# 							presence += 1
# 					except TypeError:
# 						pass
# 				if presence == 1:
# 					num = candidate

# 				presence = 0
# 				for y in range(-row % 3, 3 - row % 3):
# 					for x in range(-col % 3, 3 - col % 3):
# 						try:
# 							if candidate in arr[row + y][col + x]:
# 								presence += 1
# 						except TypeError:
# 							pass
# 				if presence == 1:
# 					num = candidate
# 	if num and num in candidates:
# 		arr[row][col] = num