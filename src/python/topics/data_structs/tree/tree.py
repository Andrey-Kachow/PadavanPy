
class BinaryTree:

    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

    def insert(self, value):
        if self.value is None:
            self.value = value
            return
        if value < self.value:
            if self.left is None:
                self.left = BinaryTree(value)
            else:
                self.left.insert(value)
        else:
            if self.right is None:
                self.right = BinaryTree(value)
            else:
                self.right.insert(value)

    def is_tip(self):
        return self.value is None

    def is_leaf(self):
        return self.left is None and self.right is None

    def depth(self):
        if self.is_leaf():
            return 1
        return 1 + max(self.left.depth(), self.right.depth())

    def is_full(self):
        if self.is_leaf():
            return True
        return all([
            self.left is not None,
            self.right is not None,
            self.left.is_full(),
            self.right.is_full()
        ])

    def is_perfect(self):
        if self.is_leaf():
            return True
        return self.is_full() and self.left.depth() == self.right.depth()

    def is_balanced(self):
        if self.is_leaf():
            return True
        if not self.left:
            return self.right.is_leaf()
        if not self.right:
            return self.left.is_leaf()
        return abs(self.left.depth() - self.right.depth()) < 2

    # Traverse preorder
    def traverse_pre_order(self):
        print(self.value, end=' ')
        if self.left:
            self.left.traverse_pre_order()
        if self.right:
            self.right.traverse_pre_order()

    # Traverse inorder
    def traverse_in_order(self):
        if self.left:
            self.left.traverse_in_order()
        print(self.value, end=' ')
        if self.right:
            self.right.traverse_in_order()

    # Traverse postorder
    def traverse_post_order(self):
        if self.left:
            self.left.traverse_post_order()
        if self.right:
            self.right.traverse_post_order()
        print(self.value, end=' ')

    def contains(self, key):
        if self.value == key:
            return True
        if self.left in not None and self.left.contains(key):
            return True
        if self.right in not None and self.right.contains(key):
            return True
        return False
