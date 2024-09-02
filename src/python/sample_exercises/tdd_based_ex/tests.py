from task import *

def test_greatest_common_divisor():
    assert greatest_common_divisor(42, 56) == 14
    assert greatest_common_divisor(461952, 116298) == 18


def test_greatest_common_divisor_large():
    assert greatest_common_divisor(7966496, 314080416) == 32
    assert greatest_common_divisor(24826148, 45296490) == 526


def test_greatest_common_divisor_zeros():
    assert greatest_common_divisor(12, 0) == 12
    assert greatest_common_divisor(0, 0) == 0
    assert greatest_common_divisor(0, 9) == 9

def test_are_coprime_one():
    assert are_coprime(1, 2)
    assert are_coprime(1, 3) 
    assert are_coprime(1, 4) 
    assert are_coprime(1, 5)  
    assert are_coprime(1, 6) 
    assert are_coprime(1, 20)


def test_are_coprime():
    assert are_coprime(2, 3) 
    assert are_coprime(2, 5) 
    assert are_coprime(2, 7) 
    assert are_coprime(2, 9)
    assert are_coprime(3, 4) 
    assert are_coprime(4, 5)
    assert are_coprime(5, 6)
    assert are_coprime(5, 7) 


def test_is_digit():
    assert is_digit('1')
    assert is_digit('2')
    assert is_digit('3')

def test_is_not_digit():
    assert not is_digit('a')
    assert not is_digit('Y')
    assert not is_digit('_')
    assert not is_digit('$')
    assert not is_digit('?')


def test_arithmetic_sequence():
    assert arithmetic_sequence(1, 1, 1) == 2
    assert arithmetic_sequence(0, 4, 4) == 16
    assert arithmetic_sequence(10, -4, 2) == 2


def test_fibbonaci():
    assert fibbonaci(0) == 0
    assert fibbonaci(1) == 1
    assert fibbonaci(2) == 1
    assert fibbonaci(3) == 2
    assert fibbonaci(4) == 3
    assert fibbonaci(5) == 5
    assert fibbonaci(6) == 8
    assert fibbonaci(7) == 13
    assert fibbonaci(8) == 21
    assert fibbonaci(9) == 34
    assert fibbonaci(10) == 55
    assert fibbonaci(11) == 89
    assert fibbonaci(12) == 144
    assert fibbonaci(13) == 233
    assert fibbonaci(14) == 377
    assert fibbonaci(15) == 610
    assert fibbonaci(16) == 987
    assert fibbonaci(17) == 1597
    assert fibbonaci(18) == 2584
    assert fibbonaci(19) == 4181



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


def test_sum_digits():
    assert sum_digits(1234567890) == 45
    assert sum_digits(111) == 3
    assert sum_digits(0) == 0
    assert sum_digits(3) == 3
    assert sum_digits(80300) == 11


def test_exponentiation():
    assert exponentiation(0, 1) == 0
    assert exponentiation(2, 2) == 4
    assert exponentiation(3, 3) == 27
    assert exponentiation(10, 4) == 10000
    assert exponentiation(30, 0) == 1


def test_quotient_remainder_of():
    assert quotient_remainder_of(2, 4) == (0, 2)
    assert quotient_remainder_of(10, 3) == (3, 1)
    assert quotient_remainder_of(45, 9) == (5, 0)


def test_increment_every_decimal_digit():
    assert increment_every_decimal_digit(1234567890) == 2345678901
    assert increment_every_decimal_digit(0) == 1


def test_rotate_decimal_by():
    assert rotate_decimal_by(1000, 1) == 100
    assert rotate_decimal_by(3333333, 4) == 3333333
    assert rotate_decimal_by(234, 2) == 342
    assert rotate_decimal_by(12345, -2) == 34512
    assert rotate_decimal_by(100500, 0) == 100500 


def test_swapped():
    assert swapped(2, 4) == (4, 2)
    assert swapped(10, 10) == (10, 10)
    assert swapped(10000, 'test') == ('test', 10000)

def test_factorial():
    assert factorial(0) == 1
    assert factorial(1) == 1
    assert factorial(2) == 2
    assert factorial(3) == 6
    assert factorial(4) == 24
    assert factorial(5) == 120


def test_big_factorial():
    assert factorial(14) == 87178291200
    assert factorial(15) == 1307674368000
    assert factorial(16) == 20922789888000
    assert factorial(17) == 355687428096000
    assert factorial(18) == 6402373705728000
    assert factorial(19) == 121645100408832000
    assert factorial(20) == 2432902008176640000
