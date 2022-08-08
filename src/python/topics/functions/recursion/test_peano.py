from peano_answers import *
# from peano import *


def test_peano_str():
	assert peano_str(0) == "0"
	assert peano_str(1) == "succ(0)"
	assert peano_str(2) == "succ(succ(0))"
	assert peano_str(3) == "succ(succ(succ(0)))"

	try:
		peano_str(-1)
		assert False
	except ValueError as e:
		pass
	except:
		assert False

	for i in range (200):
		assert peano_str(i) == ("succ(" * i) + "0" + (")" * i)


def test_peano_add():
	assert peano_add(0, 0) == 0
	assert peano_add(0, 1) == 1
	assert peano_add(0, 2) == 2
	assert peano_add(0, 5) == 5
	assert peano_add(0, 10) == 10

	assert peano_add(2, 11) == 13
	assert peano_add(6, 10) == 16
	assert peano_add(3, 12) == 15
	assert peano_add(3, 10) == 13
	assert peano_add(2, 2) == 4
	assert peano_add(1, 14) == 15


def test_peano_sub():
	assert peano_sub(0, 0) == 0
	assert peano_sub(4, 0) == 4
	assert peano_sub(1, 0) == 1
	assert peano_sub(3, 0) == 3
	assert peano_sub(89, 0) == 89

	assert peano_sub(11, 2) == 9
	assert peano_sub(10, 6) == 4
	assert peano_sub(32, 12) == 20
	assert peano_sub(25, 10) == 15
	assert peano_sub(6, 2) == 4
	assert peano_sub(100, 14) == 86

def test_peano_mul():
	assert peano_mul(0, 1) == 0
	assert peano_mul(0, 2) == 0
	assert peano_mul(0, 3) == 0
	assert peano_mul(0, 4) == 0
	assert peano_mul(0, 5) == 0
	assert peano_mul(0, 6) == 0
	assert peano_mul(0, 7) == 0
	assert peano_mul(0, 8) == 0
	assert peano_mul(0, 9) == 0
	assert peano_mul(1, 1) == 1
	assert peano_mul(1, 2) == 2
	assert peano_mul(1, 3) == 3
	assert peano_mul(1, 4) == 4
	assert peano_mul(1, 5) == 5
	assert peano_mul(1, 6) == 6
	assert peano_mul(1, 7) == 7
	assert peano_mul(1, 8) == 8
	assert peano_mul(1, 9) == 9
	assert peano_mul(2, 1) == 2
	assert peano_mul(2, 2) == 4
	assert peano_mul(2, 3) == 6
	assert peano_mul(2, 4) == 8
	assert peano_mul(2, 5) == 10
	assert peano_mul(2, 6) == 12
	assert peano_mul(2, 7) == 14
	assert peano_mul(2, 8) == 16
	assert peano_mul(2, 9) == 18
	assert peano_mul(3, 1) == 3
	assert peano_mul(3, 2) == 6
	assert peano_mul(3, 3) == 9
	assert peano_mul(3, 4) == 12
	assert peano_mul(3, 5) == 15
	assert peano_mul(3, 6) == 18
	assert peano_mul(3, 7) == 21
	assert peano_mul(3, 8) == 24
	assert peano_mul(3, 9) == 27
	assert peano_mul(4, 1) == 4
	assert peano_mul(4, 2) == 8
	assert peano_mul(4, 3) == 12
	assert peano_mul(4, 4) == 16
	assert peano_mul(4, 5) == 20
	assert peano_mul(4, 6) == 24
	assert peano_mul(4, 7) == 28
	assert peano_mul(4, 8) == 32
	assert peano_mul(4, 9) == 36
	assert peano_mul(5, 1) == 5
	assert peano_mul(5, 2) == 10
	assert peano_mul(5, 3) == 15
	assert peano_mul(5, 4) == 20
	assert peano_mul(5, 5) == 25
	assert peano_mul(5, 6) == 30
	assert peano_mul(5, 7) == 35
	assert peano_mul(5, 8) == 40
	assert peano_mul(5, 9) == 45
	assert peano_mul(6, 1) == 6
	assert peano_mul(6, 2) == 12
	assert peano_mul(6, 3) == 18
	assert peano_mul(6, 4) == 24
	assert peano_mul(6, 5) == 30
	assert peano_mul(6, 6) == 36
	assert peano_mul(6, 7) == 42
	assert peano_mul(6, 8) == 48
	assert peano_mul(6, 9) == 54
	assert peano_mul(7, 1) == 7
	assert peano_mul(7, 2) == 14
	assert peano_mul(7, 3) == 21
	assert peano_mul(7, 4) == 28
	assert peano_mul(7, 5) == 35
	assert peano_mul(7, 6) == 42
	assert peano_mul(7, 7) == 49
	assert peano_mul(7, 8) == 56
	assert peano_mul(7, 9) == 63
	assert peano_mul(8, 1) == 8
	assert peano_mul(8, 2) == 16
	assert peano_mul(8, 3) == 24
	assert peano_mul(8, 4) == 32
	assert peano_mul(8, 5) == 40
	assert peano_mul(8, 6) == 48
	assert peano_mul(8, 7) == 56
	assert peano_mul(8, 8) == 64
	assert peano_mul(8, 9) == 72
	assert peano_mul(9, 1) == 9
	assert peano_mul(9, 2) == 18
	assert peano_mul(9, 3) == 27
	assert peano_mul(9, 4) == 36
	assert peano_mul(9, 5) == 45
	assert peano_mul(9, 6) == 54
	assert peano_mul(9, 7) == 63
	assert peano_mul(9, 8) == 72
	assert peano_mul(9, 9) == 81


def test_peano_div_zero_division():
	try:
		peano_div(100, 0)
		assert False
	except ZeroDivisionError as e:
		pass


def test_peano_div_regular_division():
	assert peano_div(0, 1) == 0
	assert peano_div(0, 2) == 0
	assert peano_div(0, 3) == 0
	assert peano_div(0, 7) == 0
	assert peano_div(0, 10) == 0

	assert peano_div(10, 2) == 5
	assert peano_div(15, 5) == 3
	assert peano_div(121, 11) == 11
	assert peano_div(8, 2) == 4
	assert peano_div(16, 8) == 2
	assert peano_div(99, 11) == 9
	assert peano_div(20, 2) == 10


def test_peano_div_drop_remainder():
	assert peano_div(11, 2) == 5
	assert peano_div(17, 5) == 3
	assert peano_div(125, 11) == 11
	assert peano_div(7, 2) == 3
	assert peano_div(17, 8) == 2
	assert peano_div(100, 11) == 9
	assert peano_div(21, 2) == 10


def test_peano_mod():
	assert peano_mod(11, 2) == 1
	assert peano_mod(17, 5) == 2
	assert peano_mod(125, 11) == 4
	assert peano_mod(7, 2) == 1
	assert peano_mod(17, 8) == 1
	assert peano_mod(100, 11) == 1
	assert peano_mod(21, 2) == 1


def test_peano_pow_zero_power():
	assert peano_pow(0, 0) == 1
	assert peano_pow(1, 0) == 1
	assert peano_pow(2, 0) == 1
	assert peano_pow(5, 0) == 1
	assert peano_pow(10, 0) == 1
	assert peano_pow(20, 0) == 1


def test_peano_pow_zero_base():
	assert peano_pow(0, 1) == 0
	assert peano_pow(0, 2) == 0
	assert peano_pow(0, 3) == 0
	assert peano_pow(0, 4) == 0
	assert peano_pow(0, 5) == 0
	assert peano_pow(0, 10) == 0


def test_peano_pow_regular():
	assert peano_pow(0, 2) == 0
	assert peano_pow(0, 1) == 0
	assert peano_pow(2, 2) == 4
	assert peano_pow(3, 3) == 27
	assert peano_pow(3, 2) == 9
	assert peano_pow(4, 2) == 16
	assert peano_pow(2, 5) == 32
	assert peano_pow(3, 4) == 81