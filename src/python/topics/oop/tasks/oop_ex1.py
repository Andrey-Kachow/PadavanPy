class Tile2x2:

    def __eq__(self, other):
        return all([
            self.top_left == other.top_left,
            self.top_right == other.top_right,
            self.bot_right == other.bot_right,
            self.bot_left == other.bot_left
        ])

    def __init__(self, top_left, top_right, bot_right, bot_left):
        self.top_left = top_left
        self.top_right = top_right
        self.bot_right = bot_right
        self.bot_left = bot_left

    def __repr__(self):
        return f"tile{self.top_left, self.top_right, self.bot_right, self.bot_left}"
