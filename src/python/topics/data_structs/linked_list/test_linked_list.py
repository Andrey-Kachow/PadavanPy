from linked_list import LinkedList


# ============================================================
# Empty list
# ============================================================

def test_new_list_has_size_zero():
    ll = LinkedList()

    assert ll.size() == 0


def test_get_from_empty_list():
    ll = LinkedList()

    with pytest.raises(IndexError):
        ll.get(0)


def test_get_negative_index_from_empty_list():
    ll = LinkedList()

    with pytest.raises(IndexError):
        ll.get(-1)


def test_remove_front_from_empty_list():
    ll = LinkedList()

    with pytest.raises(IndexError):
        ll.remove_front()


def test_remove_back_from_empty_list():
    ll = LinkedList()

    with pytest.raises(IndexError):
        ll.remove_back()


def test_insert_zero_into_empty_list():
    ll = LinkedList()

    ll.insert(0, 10)

    assert ll.size() == 1
    assert ll.get(0) == 10


# ============================================================
# size()
# ============================================================

def test_size_after_one_element():
    ll = LinkedList()

    ll.push_back(10)

    assert ll.size() == 1


def test_size_after_multiple_elements():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    assert ll.size() == 3


def test_size_after_push_front():
    ll = LinkedList()

    ll.push_front(10)
    ll.push_front(20)
    ll.push_front(30)

    assert ll.size() == 3


def test_size_after_remove_front():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    ll.remove_front()

    assert ll.size() == 2


def test_size_after_remove_back():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    ll.remove_back()

    assert ll.size() == 2


def test_size_after_insert():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(30)

    ll.insert(1, 20)

    assert ll.size() == 3


# ============================================================
# get()
# ============================================================

def test_get_first_element():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    assert ll.get(0) == 10


def test_get_middle_element():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    assert ll.get(1) == 20


def test_get_last_element():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    assert ll.get(2) == 30


def test_get_every_element():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)
    ll.push_back(40)
    ll.push_back(50)

    assert ll.get(0) == 10
    assert ll.get(1) == 20
    assert ll.get(2) == 30
    assert ll.get(3) == 40
    assert ll.get(4) == 50


def test_get_index_equal_to_size():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    with pytest.raises(IndexError):
        ll.get(3)


def test_get_negative_index():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    with pytest.raises(IndexError):
        ll.get(-1)


def test_get_large_invalid_index():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    with pytest.raises(IndexError):
        ll.get(100)


# ============================================================
# push_back()
# ============================================================

def test_push_back_one_element():
    ll = LinkedList()

    ll.push_back(10)

    assert ll.size() == 1
    assert ll.get(0) == 10


def test_push_back_two_elements():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)

    assert ll.size() == 2
    assert ll.get(0) == 10
    assert ll.get(1) == 20


def test_push_back_three_elements():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    assert ll.size() == 3
    assert ll.get(0) == 10
    assert ll.get(1) == 20
    assert ll.get(2) == 30


def test_push_back_preserves_existing_elements():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)

    ll.push_back(30)

    assert ll.get(0) == 10
    assert ll.get(1) == 20
    assert ll.get(2) == 30


def test_push_back_negative_number():
    ll = LinkedList()

    ll.push_back(-10)

    assert ll.get(0) == -10


def test_push_back_zero():
    ll = LinkedList()

    ll.push_back(0)

    assert ll.get(0) == 0


def test_push_back_duplicate_values():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(10)
    ll.push_back(10)

    assert ll.size() == 3
    assert ll.get(0) == 10
    assert ll.get(1) == 10
    assert ll.get(2) == 10


# ============================================================
# push_front()
# ============================================================

def test_push_front_one_element():
    ll = LinkedList()

    ll.push_front(10)

    assert ll.size() == 1
    assert ll.get(0) == 10


def test_push_front_two_elements():
    ll = LinkedList()

    ll.push_front(10)
    ll.push_front(20)

    assert ll.size() == 2
    assert ll.get(0) == 20
    assert ll.get(1) == 10


def test_push_front_three_elements():
    ll = LinkedList()

    ll.push_front(10)
    ll.push_front(20)
    ll.push_front(30)

    assert ll.size() == 3
    assert ll.get(0) == 30
    assert ll.get(1) == 20
    assert ll.get(2) == 10


def test_push_front_preserves_existing_elements():
    ll = LinkedList()

    ll.push_back(20)
    ll.push_back(30)

    ll.push_front(10)

    assert ll.get(0) == 10
    assert ll.get(1) == 20
    assert ll.get(2) == 30


def test_push_front_negative_number():
    ll = LinkedList()

    ll.push_front(-10)

    assert ll.get(0) == -10


def test_push_front_zero():
    ll = LinkedList()

    ll.push_front(0)

    assert ll.get(0) == 0


def test_push_front_duplicate_values():
    ll = LinkedList()

    ll.push_front(10)
    ll.push_front(10)
    ll.push_front(10)

    assert ll.size() == 3
    assert ll.get(0) == 10
    assert ll.get(1) == 10
    assert ll.get(2) == 10


# ============================================================
# remove_back()
# ============================================================

def test_remove_back_from_one_element():
    ll = LinkedList()

    ll.push_back(10)

    result = ll.remove_back()

    assert result == 10
    assert ll.size() == 0


def test_remove_back_from_two_elements():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)

    result = ll.remove_back()

    assert result == 20
    assert ll.size() == 1
    assert ll.get(0) == 10


def test_remove_back_from_three_elements():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    result = ll.remove_back()

    assert result == 30
    assert ll.size() == 2
    assert ll.get(0) == 10
    assert ll.get(1) == 20


def test_remove_back_multiple_times():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    assert ll.remove_back() == 30
    assert ll.remove_back() == 20
    assert ll.remove_back() == 10

    assert ll.size() == 0


def test_remove_back_empty_list():
    ll = LinkedList()

    with pytest.raises(IndexError):
        ll.remove_back()


def test_remove_back_preserves_front():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    ll.remove_back()

    assert ll.get(0) == 10


# ============================================================
# remove_front()
# ============================================================

def test_remove_front_from_one_element():
    ll = LinkedList()

    ll.push_back(10)

    result = ll.remove_front()

    assert result == 10
    assert ll.size() == 0


def test_remove_front_from_two_elements():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)

    result = ll.remove_front()

    assert result == 10
    assert ll.size() == 1
    assert ll.get(0) == 20


def test_remove_front_from_three_elements():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    result = ll.remove_front()

    assert result == 10
    assert ll.size() == 2
    assert ll.get(0) == 20
    assert ll.get(1) == 30


def test_remove_front_multiple_times():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    assert ll.remove_front() == 10
    assert ll.remove_front() == 20
    assert ll.remove_front() == 30

    assert ll.size() == 0


def test_remove_front_empty_list():
    ll = LinkedList()

    with pytest.raises(IndexError):
        ll.remove_front()


def test_remove_front_preserves_back():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    ll.remove_front()

    assert ll.get(1) == 30


# ============================================================
# insert()
# ============================================================

def test_insert_at_zero():
    ll = LinkedList()

    ll.push_back(20)
    ll.push_back(30)

    ll.insert(0, 10)

    assert ll.size() == 3
    assert ll.get(0) == 10
    assert ll.get(1) == 20
    assert ll.get(2) == 30


def test_insert_at_middle():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(30)

    ll.insert(1, 20)

    assert ll.size() == 3
    assert ll.get(0) == 10
    assert ll.get(1) == 20
    assert ll.get(2) == 30


def test_insert_before_last_element():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(40)

    ll.insert(2, 30)

    assert ll.size() == 4
    assert ll.get(0) == 10
    assert ll.get(1) == 20
    assert ll.get(2) == 30
    assert ll.get(3) == 40


def test_insert_at_end():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    ll.insert(3, 40)

    assert ll.size() == 4
    assert ll.get(0) == 10
    assert ll.get(1) == 20
    assert ll.get(2) == 30
    assert ll.get(3) == 40


def test_insert_into_single_element_at_zero():
    ll = LinkedList()

    ll.push_back(20)

    ll.insert(0, 10)

    assert ll.size() == 2
    assert ll.get(0) == 10
    assert ll.get(1) == 20


def test_insert_into_single_element_at_end():
    ll = LinkedList()

    ll.push_back(10)

    ll.insert(1, 20)

    assert ll.size() == 2
    assert ll.get(0) == 10
    assert ll.get(1) == 20


def test_insert_does_not_replace_element():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    ll.insert(1, 99)

    assert ll.size() == 4
    assert ll.get(0) == 10
    assert ll.get(1) == 99
    assert ll.get(2) == 20
    assert ll.get(3) == 30


def test_insert_duplicate_value():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    ll.insert(1, 20)

    assert ll.size() == 4
    assert ll.get(0) == 10
    assert ll.get(1) == 20
    assert ll.get(2) == 20
    assert ll.get(3) == 30


def test_insert_negative_value():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)

    ll.insert(1, -5)

    assert ll.get(0) == 10
    assert ll.get(1) == -5
    assert ll.get(2) == 20


def test_insert_zero_value():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)

    ll.insert(1, 0)

    assert ll.get(0) == 10
    assert ll.get(1) == 0
    assert ll.get(2) == 20


def test_insert_negative_index():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    with pytest.raises(IndexError):
        ll.insert(-1, 99)


def test_insert_index_greater_than_size():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_back(30)

    with pytest.raises(IndexError):
        ll.insert(4, 99)


def test_insert_large_invalid_index():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)

    with pytest.raises(IndexError):
        ll.insert(100, 99)


# ============================================================
# push_front + push_back
# ============================================================

def test_push_front_then_push_back():
    ll = LinkedList()

    ll.push_front(20)
    ll.push_back(30)
    ll.push_front(10)

    assert ll.size() == 3
    assert ll.get(0) == 10
    assert ll.get(1) == 20
    assert ll.get(2) == 30


def test_push_back_then_push_front():
    ll = LinkedList()

    ll.push_back(20)
    ll.push_front(10)
    ll.push_back(30)

    assert ll.size() == 3
    assert ll.get(0) == 10
    assert ll.get(1) == 20
    assert ll.get(2) == 30


def test_alternating_front_and_back():
    ll = LinkedList()

    ll.push_back(2)
    ll.push_front(1)
    ll.push_back(3)
    ll.push_front(0)
    ll.push_back(4)

    assert ll.size() == 5
    assert ll.get(0) == 0
    assert ll.get(1) == 1
    assert ll.get(2) == 2
    assert ll.get(3) == 3
    assert ll.get(4) == 4


# ============================================================
# Complex operation sequences
# ============================================================

def test_complex_sequence_one():
    ll = LinkedList()

    ll.push_back(10)
    ll.push_back(20)
    ll.push_front(5)
    ll.insert(2, 15)

    assert ll.size() == 4
    assert ll.get(0) == 5
    assert ll.get(1) == 10
    assert ll.get(2) == 15
    assert ll.get(3) == 20

    assert ll.remove_front() == 5
    assert ll.remove_back() == 20

    assert ll.size() == 2
    assert ll.get(0) == 10
    assert ll.get(1) == 15


def test_complex_sequence_two():
    ll = LinkedList()

    ll.push_front(3)
    ll.push_front(2)
    ll.push_front(1)
    ll.push_back(4)
    ll.push_back(5)

    assert ll.remove_front() == 1

    ll.insert(1, 99)

    assert ll.remove_back() == 5

    assert ll.size() == 4
    assert ll.get(0) == 2
    assert ll.get(1) == 99
    assert ll.get(2) == 3
    assert ll.get(3) == 4


def test_complex_sequence_three():
    ll = LinkedList()

    ll.push_back(1)
    ll.push_back(2)
    ll.push_back(3)
    ll.push_back(4)
    ll.push_back(5)

    assert ll.remove_front() == 1
    assert ll.remove_back() == 5

    ll.insert(0, 10)
    ll.insert(2, 20)
    ll.insert(ll.size(), 30)

    assert ll.size() == 6
    assert ll.get(0) == 10
    assert ll.get(1) == 2
    assert ll.get(2) == 20
    assert ll.get(3) == 3
    assert ll.get(4) == 4
    assert ll.get(5) == 30


# ============================================================
# Empty/non-empty transitions
# ============================================================

def test_remove_last_element_then_add_with_push_back():
    ll = LinkedList()

    ll.push_back(10)

    assert ll.remove_back() == 10
    assert ll.size() == 0

    ll.push_back(20)

    assert ll.size() == 1
    assert ll.get(0) == 20


def test_remove_last_element_then_add_with_push_front():
    ll = LinkedList()

    ll.push_back(10)

    assert ll.remove_front() == 10
    assert ll.size() == 0

    ll.push_front(20)

    assert ll.size() == 1
    assert ll.get(0) == 20


def test_remove_all_from_front_then_push_back():
    ll = LinkedList()

    ll.push_back(1)
    ll.push_back(2)
    ll.push_back(3)

    assert ll.remove_front() == 1
    assert ll.remove_front() == 2
    assert ll.remove_front() == 3

    assert ll.size() == 0

    ll.push_back(4)
    ll.push_back(5)

    assert ll.size() == 2
    assert ll.get(0) == 4
    assert ll.get(1) == 5


def test_remove_all_from_back_then_push_front():
    ll = LinkedList()

    ll.push_back(1)
    ll.push_back(2)
    ll.push_back(3)

    assert ll.remove_back() == 3
    assert ll.remove_back() == 2
    assert ll.remove_back() == 1

    assert ll.size() == 0

    ll.push_front(4)
    ll.push_front(5)

    assert ll.size() == 2
    assert ll.get(0) == 5
    assert ll.get(1) == 4


# ============================================================
# Larger lists
# ============================================================

def test_push_back_100_elements():
    ll = LinkedList()

    for i in range(100):
        ll.push_back(i)

    assert ll.size() == 100

    for i in range(100):
        assert ll.get(i) == i


def test_push_front_100_elements():
    ll = LinkedList()

    for i in range(100):
        ll.push_front(i)

    assert ll.size() == 100

    for i in range(100):
        assert ll.get(i) == 99 - i


def test_remove_front_100_elements():
    ll = LinkedList()

    for i in range(100):
        ll.push_back(i)

    for i in range(100):
        assert ll.remove_front() == i

    assert ll.size() == 0


def test_remove_back_100_elements():
    ll = LinkedList()

    for i in range(100):
        ll.push_back(i)

    for i in range(99, -1, -1):
        assert ll.remove_back() == i

    assert ll.size() == 0


def test_insert_100_elements_at_end():
    ll = LinkedList()

    for i in range(100):
        ll.insert(i, i)

    assert ll.size() == 100

    for i in range(100):
        assert ll.get(i) == i


def test_insert_100_elements_at_front():
    ll = LinkedList()

    for i in range(100):
        ll.insert(0, i)

    assert ll.size() == 100

    for i in range(100):
        assert ll.get(i) == 99 - i
