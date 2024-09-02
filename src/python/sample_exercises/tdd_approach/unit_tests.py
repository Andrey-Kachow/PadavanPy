from task import *

def test_can_drink():
    assert can_drink(18, False)
    assert can_drink(21, False)
    assert can_drink(90, False)
    assert not can_drink(3, False)


def test_can_drink_united_states():
    assert not can_drink(18, True)
    assert can_drink(21, True)
    assert can_drink(90, True)
    assert not can_drink(3, True)


def test_plus():
	assert plus(1, 1) == 2
	assert plus(0, 100) == 100
	assert plus(100, 0) == 100
	assert plus(5, -5) == 0


def test_minus():
	assert minus(1, 1) == 0
	assert minus(0, 100) == -100
	assert minus(100, 0) == 100
	assert minus(5, -5) == 10


def test_is_even():
	assert is_even(0);
	assert is_even(2);
	assert is_even(-4);
	assert is_even(8);
	assert is_even(1000);
	assert not is_even(1);
	assert not is_even(3);
	assert not is_even(-5);


def test_celsius_to_kelvin_valid_temperature():
	assert celsius_to_kelvin(0) == 273
	assert celsius_to_kelvin(-273) == 0
	assert celsius_to_kelvin(100) == 373


def test_celsius_to_kelvin_illegal_arg():
	assert celsius_to_kelvin(-274) == 0
	assert celsius_to_kelvin(-999) == 0
	assert celsius_to_kelvin(-1234567890) == 0	


def test_throw_two_dice_range():
	for _ in range(1000):
		result = throw_two_dice()
		assert 2 <= result and result <= 12


def test_throw_two_dice_fairness():

	TOLERANCE = 500

	def more_or_less_the_same_frequency(f1, f2):
		return abs(f1 - f2) < TOLERANCE

	counts = {}
	for number in range(2, 13):
		counts[number] = 0

	for _ in range(100000):
		result = throw_two_dice()
		counts[result] += 1

	for first_num in range(2, 13):
		second_num = 14 - first_num
		assert more_or_less_the_same_frequency(counts[first_num], counts[second_num])