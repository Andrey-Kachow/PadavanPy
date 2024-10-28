from number_sys import *


def test_from_decimal_to_binary():
    assert from_decimal_to_binary("0") == "0"
    assert from_decimal_to_binary("1") == "1"
    assert from_decimal_to_binary("2") == "10"
    assert from_decimal_to_binary("3") == "11"
    assert from_decimal_to_binary("9") == "1001"
    assert from_decimal_to_binary("127") == "1111111"


def test_from_binary_to_decimal():
    assert from_binary_to_decimal("0") == "0"
    assert from_binary_to_decimal("1") == "1"
    assert from_binary_to_decimal("10") == "2"
    assert from_binary_to_decimal("11") == "3"
    assert from_binary_to_decimal("1001") == "9"
    assert from_binary_to_decimal("1111111") == "127"


def test_from_decimal_to_p_int():
    assert from_decimal_to_p_int("0", 7) == "0"
    assert from_decimal_to_p_int("15", 16) == "F"
    assert from_decimal_to_p_int("12", 5) == "22"
    assert from_decimal_to_p_int("100", 10) == "100"


def test_from_p_int_to_decimal():
    assert from_p_int_to_decimal("0", 7) == "0"
    assert from_p_int_to_decimal("F", 16) == "15"
    assert from_p_int_to_decimal("22", 5) == "12"
    assert from_p_int_to_decimal("100", 10) == "100"