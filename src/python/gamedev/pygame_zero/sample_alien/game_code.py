import random
import math

HEIGHT = 800
WIDTH = 1600

'''
        We agreed that 'L' means LEFT, 'R' means Right
'''

blue = (0, 128, 247)
Speed = 5
alien = Actor("alien") 

horizontal_direction = "L" # L or R
vertical_direction = 'U' # U or D
Top = "U"
Right = "R"
alien.pos = WIDTH/2, HEIGHT/2
MOVING = 'M'
IDLE = 'I'
player_motion_state_h = IDLE
player_motion_state_v = IDLE
OUCH = {'text':'OUCH', 'is visible':False}

def shoot_bullet_player():
    bullet = bullet_create() 
    bullets.append(bullet)    
    clock.schedule(shoot_bullet_player,1)
def bullet_create ():

    distance_from_center = math.sqrt((WIDTH/2)**2+(HEIGHT/2)**2) 
    angle_of_position = math.radians(random.randint(0, 360))
    new_bullet_x = (WIDTH/2) + distance_from_center * math.cos(angle_of_position)
    new_bullet_y = (HEIGHT/2) + distance_from_center * math.sin(angle_of_position)

    



    # math.radians(), math.sin(), math.cos()

    # convert angle in degrees into angle in radians
    player_x, player_y = alien.pos   #  if player.pos is (4, 6), then python will put 4 to playr_x and 6 to player_y
    
    new_bullet_speed_x = (player_x - new_bullet_x)
    new_bullet_speed_y = (player_y - new_bullet_y)

    # find the magnitude
    magnitude =  math.sqrt(new_bullet_speed_x**2+new_bullet_speed_y**2)

    # normalize the vector
    new_bullet_speed_x = new_bullet_speed_x / magnitude
    new_bullet_speed_y = new_bullet_speed_y / magnitude

    # set the desired speed
    bullet_speed_magnitude = random.uniform(2,5)

    new_bullet_speed_x = new_bullet_speed_x * bullet_speed_magnitude
    new_bullet_speed_y = new_bullet_speed_y * bullet_speed_magnitude
    return {
        'x': new_bullet_x,
        'y': new_bullet_y,
        'speed': {
            'h': new_bullet_speed_x,
            'v': new_bullet_speed_y 
        }
    }


# bullet = bullet_create()
bullets = []
clock.schedule(shoot_bullet_player,1)

def draw_bullet(bullet):
    for neighbor_offset_x in [-2, -1, 0, 1, 2]:
        for neighbor_offset_y in [-2, -1, 0, 1, 2]:
            # Drawing a bullet as line

            # find a line start point
            line_start_x = bullet['x'] + bullet['speed']['h'] + neighbor_offset_x
            line_start_y = bullet['y'] + bullet['speed']['v'] + neighbor_offset_y

            # find a line end point
            line_end_x = bullet['x'] - bullet['speed']['h'] + neighbor_offset_x
            line_end_y = bullet['y'] - bullet['speed']['v'] + neighbor_offset_y

            # specify a color
            bullet_color = (255, 10, 10)

            # draw the line on screen finally
            screen.draw.line((line_start_x, line_start_y),(line_end_x, line_end_y), bullet_color)

    
def draw():
    screen.fill(blue)
    if OUCH['is visible']:
        screen.draw.text(
            OUCH['text'], # OUCH!!
            pos=(alien.left, alien.bottom)
        )


    for bullet in bullets:
        # screen.draw.filled_rect(Rect((bullet['x'], bullet["y"]), (35, 10)), (255, 10, 10))
        draw_bullet(bullet)
    alien.draw()

    
def OUCH_remove():
    OUCH['is visible'] = False




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
    
        if alien.collidepoint((bullet['x'], bullet['y'])):
            print('OUCH')
            OUCH['is visible'] = True 
            clock.schedule(OUCH_remove,2)
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