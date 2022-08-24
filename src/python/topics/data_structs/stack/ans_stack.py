class ListStack:

    def __init__(self):
        self.values = []

    def is_empty(self):
        return not bool(self.values)

    def _empty_check(self, msg):
        if self.is_empty():
            raise Exception(msg)

    def size(self):
        return len(self.values)

    def peek(self):
        self._empty_check("Empty Stack peek")
        return self.values[-1]

    def push(self, data):
        self.values.append(data)

    def pop(self):
        self._empty_check("Empty Stack pop")
        return self.values.pop()


class Stack:

    class Node:
        def __init__(self, data):
            self.data = data
            self.next = None

    def __init__(self):
        self.top = None
        self.elements_count = 0

    def is_empty(self):
        return self.top is None

    def _empty_check(self, msg):
        if self.is_empty():
            raise Exception(msg)

    def size(self):
        return self.elements_count

    def peek(self):
        self._empty_check("Empty Stack peek")
        return self.top.data

    def push(self, data):
        new_node = Stack.Node(data)
        new_node.next = self.top
        self.top = new_node
        self.elements_count += 1

    def pop(self):
        self._empty_check("Empty Stack pop")
        popped_head = self.top
        self.top = self.top.next
        self.elements_count -= 1
        return popped_head.data
