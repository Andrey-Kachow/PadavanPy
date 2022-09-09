
class Trie:
    def __init__(self):
        self.is_present = False
        self.children = {}

    def insert_str(self, string):
        if not string:
            self.is_present = True
            return

        head = string[0]
        tail = string[1:]

        if head not in self.children:
            self.children[head] = Trie()

        self.children[head].insert_str(tail)

    def size(self):
        result = 2  # flag size and letter size in total
        for child in self.children:
            result += self.children[child].size()
        return result

    def contains(self, string):
        if not string:
            return self.is_present

        head = string[0]
        tail = string[1:]

        if head in self.children:
            return self.children[head].contains(tail)
        return False
