class ListQueue:

    def __init__(self):
        self.values = []

    def is_empty(self):
        return self.values == []

    def add(self, value):
        self.values.append(value)

    def poll(self):
        if self.is_empty():
            raise Exception("Empty Queue")
        return self.values.pop(0)


class Queue:

    class Node:
        def __init__(self, value):
            self.value = value
            self.next = None

    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0

    def is_empty(self):
        return self.head is None

    def add(self, value):
        new_elem = Queue.Node(value)
        if self.is_empty():
            self.head = new_elem
            self.tail = new_elem
            self.size = 1
            return
        self.tail.next = new_elem
        self.tail = new_elem
        self.size += 1

    def poll(self):
        popped_head = self.head
        self.head = self.head.next
        if self.head is None:
            self.tail = None
        self.size -= 1
        return popped_head.value


class PriorityQueue:

    class Node:
        def __init__(self, value, priority):
            self.value = value
            self.priority = priority
            self.next = None

    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0

    def is_empty(self):
        return self.head is None

    def add(self, value, priority=None):
        if priority is None:
            priority = value
        new_elem = PriorityQueue.Node(value, priority)

        if self.is_empty():
            self.head = new_elem
            self.tail = new_elem
            self.size = 1
            return

        prev = None
        current = self.head
        while current is not None and current.priority > new_elem.priority:
            prev = current
            current = current.next

        if current is None:
            self.tail.next = new_elem
            self.tail = new_elem
        else:
            if prev is None:
                self.head = new_elem
            else:
                prev.next = new_elem
            new_elem.next = current

        self.size += 1

    def poll(self):
        popped_head = self.head
        self.head = self.head.next
        if self.head is None:
            self.tail = None
        self.size -= 1
        return popped_head.value
