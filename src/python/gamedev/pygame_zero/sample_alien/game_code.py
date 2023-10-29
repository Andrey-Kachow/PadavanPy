
HEIGHT = 1000
WIDTH = 2000

'''
        We agreed that 'L' means LEFT, 'R' means Right
'''

blue = (0, 128, 247)
Speed = 2
alien = Actor("alien") 

horizontal_direction = "L" # L or R
vertical_direction = 'U' # U or D
Top = "U"
Right = "R"
alien.pos = 100, 100
MOVING = 'M'
IDLE = 'I'
player_motion_state_h = IDLE
player_motion_state_v = IDLE
bullet = { 'x':75, 'y' :100 }


def draw():
    screen.fill(blue)


    screen.draw.filled_rect(Rect((bullet['x'], bullet["y"]), (10, 10)), (255, 10, 10))

    alien.draw()


# Is called once per frame
def update():
    
    global horizontal_direction
    global vertical_direction

    if player_motion_state_v == MOVING:
        if vertical_direction == "U":
            alien.top -= Speed
        else:
            alien.top += Speed
    if player_motion_state_h == MOVING:
        if horizontal_direction == "L":
            alien.left -= Speed
        else:
            alien.left += Speed


    # # If it goes beyond the right-hand side edge of the screen
    # if alien.left > WIDTH:
    #     direction = "L"

    # # If it goes beyond the left-hand side edge of the screen
    # if alien.right < 0:
    #     direction = "R"
        
def on_key_down(key):
   
    global horizontal_direction
    global vertical_direction
    global player_motion_state_h
    global player_motion_state_v
    
    # a.k. if the user presses left arrow kßy, then...
    if key == keys.RIGHT:
        # Change direction to Right
        horizontal_direction = "R"
        player_motion_state_h = MOVING

    # a.k. if the user presses left arrow key, then...
    if key == keys.LEFT:
          # ...change ot left
        horizontal_direction = "L"
        player_motion_state_h = MOVING

    if key == keys.UP:
        vertical_direction = "U"
        player_motion_state_v = MOVING

    if key == keys.DOWN:
        vertical_direction = "D"
        player_motion_state_v = MOVING
    
def on_key_up(key): 
 
    global player_motion_state_v
    if key == keys.UP or key == keys.DOWN:
        player_motion_state_v = IDLE
   
    global player_motion_state_h
    if key == keys.LEFT or key == keys.RIGHT:
        player_motion_state_h = IDLE
