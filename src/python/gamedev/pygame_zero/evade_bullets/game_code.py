import random
import math

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


def bullet_create ():

    distance_from_center = math.sqrt((WIDTH/2)**2+(HEIGHT/2)**2) 
    angle_of_position = math.radians(random.randint(0, 360))
    new_bullet_x = (WIDTH/2) + distance_from_center * math.cos(angle_of_position)
    new_bullet_y = (HEIGHT/2) + distance_from_center * math.sin(angle_of_position)

    

    new_bullet_speed = random.randint(5, 12)
    new_bullet_angle = random.randint(0, 360)


    # math.radians(), math.sin(), math.cos()

    # convert angle in degrees into angle in radians
    new_bullet_angle_in_radians = math.radians(new_bullet_angle)

    # extract the x and y from the angle and direction. Convert polar coordinates into cartesian.
    new_bullet_speed_x = new_bullet_speed * math.cos(new_bullet_angle_in_radians)
    new_bullet_speed_y = new_bullet_speed * math.sin(new_bullet_angle_in_radians)

    return {
        'x': new_bullet_x,
        'y': new_bullet_y,
        'speed': {
            'h': new_bullet_speed_x,
            'v': new_bullet_speed_y 
        }
    }

# bullet = bullet_create()
bullets = [bullet_create(), bullet_create(), bullet_create()]

for _ in range(100):
    new_bullet = bullet_create()
    bullets.append(new_bullet)

    
def draw():
    screen.fill(blue)


    for bullet in bullets:
        screen.draw.filled_rect(Rect((bullet['x'], bullet["y"]), (35, 10)), (255, 10, 10))

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

            
    for bullet in bullets:
        bullet['y'] = bullet['y'] + bullet['speed']['v']
        bullet['x'] = bullet['x'] + bullet['speed']['h']           # D = v * t
                                                               # v = D / t
                                                               # 
                                                               # D_new = D_old + v * t     
                                                               #    where
                                                               #        t ---> frequency of the frame
                                                               #        v ---> number of pixel per frame 
    
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
