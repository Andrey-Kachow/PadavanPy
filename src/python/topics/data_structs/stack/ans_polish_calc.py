from ans_stack import *
# from stack import *

DEFAULT_STACK_IMPL = Stack

class Operator:

    add = lambda x, y: int(x) + int(y)
    sub = lambda x, y: int(x) - int(y)
    mul = lambda x, y: int(x) * int(y)
    div = lambda x, y: int(x) // int(y)

    symbol_table = {
        "+": add,
        "-": sub,
        "*": mul,
        "/": div
    }

    @classmethod
    def by_token(cls, token):
        return cls.symbol_table[token]


def token_is_op(token):
    return token in "+-*/"


class PolishEvaluator:

    def __init__(self, expression, stack=None):
        self.stack = stack
        if stack is None:
            self.stack = DEFAULT_STACK_IMPL()
        self.expression = expression

    def evaluate(self):
        tokens = self.expression.split()
        for token in tokens:
            if token_is_op(token):
                second = self.stack.pop()
                first = self.stack.pop()
                self.stack.push(Operator.by_token(token)(first, second))
            else:
                self.stack.push(token)
        return self.stack.peek()
