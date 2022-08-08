# from rec_answers import *
from rec import *

import random

def test_my_len():
	assert rec_len("") == 0
	assert rec_len([]) == 0
	assert rec_len([1]) == 1
	assert rec_len("a") == 1
	assert rec_len([1, 2, 3, 4, 5]) == 5
	assert rec_len("asdasdasdasd") == 12


def test_rec_all():
	assert rec_all([]) == True
	assert rec_all([True, 1, 2]) == True
	assert rec_all([True, False, 1]) == False

	for i in range(100):
		test_list = [random.randint(0, 10) for j in range(10)]
		assert rec_all(test_list) == all(test_list)


def test_rec_any():
	assert rec_any([]) == False
	assert rec_any([True, 1, 2]) == True
	assert rec_any([True, False, 1]) == True
	assert rec_any([False, 0, []]) == False

	for i in range(100):
		test_list = [random.randint(0, 1) for j in range(10)]
		assert rec_any(test_list) == any(test_list)


def test_rec_take():
	assert rec_take(0, []) == []
	assert rec_take(1, []) == []
	assert rec_take(5, []) == []
	assert rec_take(0, [1, 2, 3]) == []
	assert rec_take(1, [1, 2, 3]) == [1]
	assert rec_take(2, [1, 2, 3]) == [1, 2]
	assert rec_take(3, [1, 2, 3]) == [1, 2, 3]
	assert rec_take(4, [1, 2, 3]) == [1, 2, 3]

	for i in range(100):
		for j in range(100):
			test_list = list(range(i))
			assert rec_take(j, test_list) == test_list[0:j]

def test_rec_drop():
	assert rec_drop(0, []) == []
	assert rec_drop(1, []) == []
	assert rec_drop(5, []) == []
	assert rec_drop(0, [1, 2, 3]) == [1, 2, 3]
	assert rec_drop(1, [1, 2, 3]) == [2, 3]
	assert rec_drop(2, [1, 2, 3]) == [3]
	assert rec_drop(3, [1, 2, 3]) == []
	assert rec_drop(4, [1, 2, 3]) == []

	for i in range(100):
		for j in range(100):
			test_list = list(range(i))
			assert rec_drop(j, test_list) == test_list[j:]


def test_naive_split_at():
    assert naive_split_at(0, []) == ([], [])
    assert naive_split_at(3, []) == ([], [])
    assert naive_split_at(0, [1, 2, 3]) == ([], [1, 2, 3])
    assert naive_split_at(2, [1, 2, 3]) == ([1, 2], [3])
    assert naive_split_at(4, [1, 2, 3, 4]) == ([1, 2, 3, 4], [])
    assert naive_split_at(8, [1, 2, 3]) == ([1, 2, 3], [])


def test_rec_split_at():
    assert rec_split_at(0, []) == ([], [])
    assert rec_split_at(3, []) == ([], [])
    assert rec_split_at(0, [1, 2, 3]) == ([], [1, 2, 3])
    assert rec_split_at(2, [1, 2, 3]) == ([1, 2], [3])
    assert rec_split_at(4, [1, 2, 3, 4]) == ([1, 2, 3, 4], [])
    assert rec_split_at(8, [1, 2, 3]) == ([1, 2, 3], [])


def test_rec_range():
    for i in range(-30, 31, 1):
        for j in range(-30, 31, 1):
            for k in list(range(-10, 0, 1)) + list(range(1, 11, 1)):
                assert rec_range(i, j, k) == list(range(i, j, k))


def test_rec_range_zero_step():
    try:
        rec_range(1, 5, 0)
        assert False
    except ValueError as e:
        pass


def test_rec_map():
    square = lambda x: x*x
    cube = lambda x: x*x*x

    for f in [int, bool, str, square, cube]:
        for i in range(100):
            test_list = list(range(i))
            assert rec_map(f, test_list) == list(map(f, test_list))


def test_rec_filter():
	is_even = lambda x: x % 2 == 0
	is_odd = lambda x: x % 2 == 1
	not_5 = lambda x: x != 5

	for p in [bool, is_even, is_odd, not_5]:
		for i in range(100):
			test_list = list(range(i))
			assert rec_filter(p, test_list) == list(filter(p, test_list))