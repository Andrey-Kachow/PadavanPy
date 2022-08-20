RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

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

    def is_chess(self):
        return all([
            self.top_left == self.bot_right,
            self.bot_left == self.top_right,
            self.top_left != self.bot_left
        ])

    def rotated(self, clockwise):
        if clockwise:
            return Tile2x2(
                top_left=self.bot_left,
                top_right=self.top_left,
                bot_right=self.top_right,
                bot_left=self.bot_right
            )
        else:
            return Tile2x2(
                top_left=self.top_right,
                top_right=self.bot_right,
                bot_right=self.bot_left,
                bot_left=self.top_left
            )

    def rotate(self, clockwise):
        if clockwise:
            temp = self.bot_right
            self.bot_right = self.top_right
            self.top_right = self.top_left
            self.top_left = self.bot_left
            self.bot_left = temp
        else:
            temp = self.top_left
            self.top_left = self.top_right
            self.top_right = self.bot_right
            self.bot_right = self.bot_left
            self.bot_left = temp


class Warrior:

    def __init__(self, ws, bs, s, t, i, sv):
        self.ws = ws
        self.bs = bs
        self.s = s
        self.t = t
        self.i = i
        self.sv = sv


class Weapon:

    def __init__(self, s, ap, shots):
        self.s = s
        self.ap = ap
        self.shots = shots
