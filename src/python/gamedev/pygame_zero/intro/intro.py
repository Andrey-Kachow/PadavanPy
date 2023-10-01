
dark_red = (128, 0, 0)


alien = Actor('alien')
alien.topleft = (0, 10)


WIDTH = 500
HEIGHT = alien.height + 20

def draw():
    screen.fill(dark_red)
    alien.draw()


def update():
    alien.left += 2
    if alien.left > WIDTH:
        alien.right = 0

def on_mouse_down(pos):
    if alien.collidepoint(pos):
        print("Eek!")
    else:
        print("You missed me!")

