from ans_stack import *
from ans_polish_calc import *
import pytest
# from stack import *
# from polish_calc import *

@pytest.mark.skip
def test_is_empty(stack_class):
    stack = stack_class()
    assert stack.is_empty()
    stack.push(1)
    assert not stack.is_empty()

@pytest.mark.skip
def test_empty_peek(stack_class):
    stack = stack_class()
    try:
        stack.peek()
        assert False
    except Exception as e:
        pass

@pytest.mark.skip
def test_empty_pop(stack_class):
    stack = stack_class()
    try:
        stack.pop()
        assert False
    except Exception as e:
        pass

@pytest.mark.skip
def test_push_pop_empty(stack_class):
    stack = stack_class()
    stack.push(1)
    stack.pop()
    assert stack.is_empty()

@pytest.mark.skip
def test_push_peek(stack_class):
    stack = stack_class()
    stack.push(1)
    assert stack.peek() == 1
    stack.push(2)
    assert stack.peek() == 2
    stack.push(3)
    assert stack.peek() == 3
    stack.push(4)
    assert stack.peek() == 4
    stack.push(5)
    assert stack.peek() == 5
    stack.push(6)
    assert stack.peek() == 6

@pytest.mark.skip
def test_push_size(stack_class):
    stack = stack_class()
    stack.push(1)
    assert stack.size() == 1
    stack.push(2)
    assert stack.size() == 2
    stack.push(3)
    assert stack.size() == 3
    stack.push(4)
    assert stack.size() == 4
    stack.push(5)
    assert stack.size() == 5
    stack.push(6)
    assert stack.size() == 6

@pytest.mark.skip
def test_pop_size(stack_class):
    stack = stack_class()
    stack.push(1)
    stack.push(2)
    stack.push(3)
    stack.push(4)
    stack.push(5)
    stack.push(6)
    assert stack.size() == 6
    stack.pop()
    assert stack.size() == 5
    stack.pop()
    assert stack.size() == 4
    stack.pop()
    assert stack.size() == 3
    stack.pop()
    assert stack.size() == 2
    stack.pop()
    assert stack.size() == 1
    stack.pop()
    assert stack.size() == 0

@pytest.mark.skip
def test_pop(stack_class):
    stack = stack_class()
    stack.push(1)
    stack.push(2)
    stack.push(3)
    stack.push(4)
    stack.push(5)
    stack.push(6)
    assert stack.pop() == 6
    assert stack.pop() == 5
    assert stack.pop() == 4
    assert stack.pop() == 3
    assert stack.pop() == 2
    assert stack.pop() == 1


def test_ListStack_is_empty():
    test_is_empty(ListStack)


def test_ListStack_empty_peek():
    test_empty_peek(ListStack)


def test_ListStack_empty_pop():
    test_empty_pop(ListStack)


def test_ListStack_push_pop_empty():
    test_push_pop_empty(ListStack)


def test_ListStack_push_peek():
    test_push_peek(ListStack)


def test_ListStack_push_size():
    test_push_size(ListStack)


def test_ListStack_pop_size():
    test_pop_size(ListStack)


def test_ListStack_pop():
    test_pop(ListStack)


def test_Stack_is_empty():
    test_is_empty(Stack)


def test_Stack_empty_peek():
    test_empty_peek(Stack)


def test_Stack_empty_pop():
    test_empty_pop(Stack)


def test_Stack_push_pop_empty():
    test_push_pop_empty(Stack)


def test_Stack_push_peek():
    test_push_peek(Stack)


def test_Stack_push_size():
    test_push_size(Stack)


def test_Stack_pop_size():
    test_pop_size(Stack)


def test_Stack_pop():
    test_pop(Stack)

@pytest.mark.skip
def test_polish_evaluator(stack_class):
    assert PolishEvaluator("1 1 +", stack_class()).evaluate() == 2
    assert PolishEvaluator("1 2 3 + +", stack_class()).evaluate() == 6
    assert PolishEvaluator("1 1 *", stack_class()).evaluate() == 1
    assert PolishEvaluator("5 4 -", stack_class()).evaluate() == 1
    assert PolishEvaluator("1 1 + 5 4 - +", stack_class()).evaluate() == 3
    assert PolishEvaluator("10 2 / 2 *", stack_class()).evaluate() == 10


def test_ListStack_polish_evaluator():
    test_polish_evaluator(ListStack)


def test_Stack_polish_evaluator():
    test_polish_evaluator(Stack)
