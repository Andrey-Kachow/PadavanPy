# from oop_ex1_ans import *
from oop_ex1 import *

def test_Tile2x2_is_chess():
    assert Tile2x2(1, 0, 1, 0).is_chess()
    assert not Tile2x2(1, 1, 1, 1).is_chess()
    assert not Tile2x2(1, 3, 1, 0).is_chess()
    assert not Tile2x2(0, 1, 1, 0).is_chess()


def test_Tile2x2_rotated():
    assert Tile2x2(1, 0, 1, 0).rotated(clockwise=True) == Tile2x2(0, 1, 0, 1)
    assert Tile2x2(1, 0, 1, 0).rotated(clockwise=False) == Tile2x2(0, 1, 0, 1)
    assert Tile2x2(1, 2, 3, 4).rotated(clockwise=False) == Tile2x2(2, 3, 4, 1)
    assert Tile2x2(1, 2, 3, 4).rotated(clockwise=True) == Tile2x2(4, 1, 2, 3)


def test_Tile2x2_rotate():
    t = Tile2x2(0, 1, 2, 3)
    tr1 = Tile2x2(3, 0, 1, 2)
    tr2 = Tile2x2(2, 3, 0, 1)
    tr3 = Tile2x2(1, 2, 3, 0)
    tr4 = Tile2x2(0, 1, 2, 3)

    assert t == tr4
    t.rotate(clockwise=True)
    assert t == tr1
    t.rotate(clockwise=True)
    assert t == tr2
    t.rotate(clockwise=True)
    assert t == tr3
    t.rotate(clockwise=True)
    assert t == tr4
    t.rotate(clockwise=False)
    assert t == tr3
    t.rotate(clockwise=False)
    assert t == tr2
    t.rotate(clockwise=False)
    assert t == tr1
    t.rotate(clockwise=False)
    assert t == tr4
