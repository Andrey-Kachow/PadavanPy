from queue import *
import pytest

@pytest.mark.skip
def test_is_empty(queue_class):
    queue = queue_class()
    assert queue.is_empty()

@pytest.mark.skip
def test_add_poll(queue_class):
    queue = queue_class()
    queue.add(1)
    queue.add(2)
    queue.add(3)
    queue.add(4)
    queue.add(5)
    assert queue.poll() == 1
    assert queue.poll() == 2
    assert queue.poll() == 3
    assert queue.poll() == 4
    assert queue.poll() == 5

@pytest.mark.skip
def test_empty_poll(queue_class):
    queue = queue_class()
    try:
        queue.poll()
        assert False
    except Exception as e:
        pass


def test_ListQueue_is_empty():
    test_is_empty(ListQueue)


def test_ListQueue_add_poll():
    test_add_poll(ListQueue)


def test_ListQueue_empty_poll():
    test_empty_poll(ListQueue)


def test_Queue_is_empty():
    test_is_empty(Queue)


def test_Queue_add_poll():
    test_add_poll(Queue)


def test_Queue_empty_poll():
    test_empty_poll(Queue)
