from pgzhelper import *
#add ice spice music for next lesson and replay button
import random

WIDTH = 700
HEIGHT = 700 

green = (0, 255, 128)
black = (0, 0, 0)

timer_started = False 
game_over = False


villain = Actor('alien')
villain.pos = (350,350)

happy = Actor('happy')
happy.scale = 0.11
happy.pos = (100, 100)

is_happy = False

happy_counter = 0
miss_counter = 0


def draw():
    screen.fill(green)

    if not game_over: 

        villain.draw()
        message = "You HIT the target " + str(happy_counter) + " times"
        message2 = "You MISSED the target " + str(miss_counter) + " times"
        message3 = "Smily face above:"

        screen.draw.text(message, (400, 40))
        screen.draw.text(message2, (400, 65))
        screen.draw.text(message3, (50, 230))

        if is_happy:
            happy.draw()

    else:
        screen.fill(black)
        screen.draw.text("GAME OVER", center = (350,350), fontsize = 120, color = (80, 225, 203))
        message_hits = "HITS: " + str(happy_counter)
        message_misses = "MISSES: " + str(miss_counter)
        
        # (95, 213, 255)
        # 252, 145, 255  

        screen.draw.text(message_hits, center = (350, 450), fontsize = 70, color = (95, 213, 255))
        screen.draw.text(message_misses, center = (350, 550), fontsize = 70, color = (252, 145, 255))
    
def end_game():
    global game_over
    game_over = True

    
def update():
    global timer_started
    
    if not timer_started:
        clock.schedule(end_game, 30)
        music.play("ice_spice2")
        timer_started = True




    horizontal_displacement = random.randint(-17, 17)
    vertical_displacement = random.randint(-17, 17)

    if villain.right >= WIDTH:
        horizontal_displacement = random.randint(-17, 0)

    if villain.left <= 0:
        horizontal_displacement = random.randint(0, 17)

    if villain.top <= 0:
        vertical_displacement = random.randint(0, 17) 


    if villain.bottom >= HEIGHT:
        vertical_displacement = random.randint(-17, 0)


    # if villain.left>= WIDTH:
    #     villain.right=0


    villain.left = villain.left + horizontal_displacement
    villain.top = villain.top + vertical_displacement


def on_mouse_down(pos):
    villain_got_hit = villain.collidepoint(pos)
    global is_happy
    global happy_counter
    global miss_counter

    print(villain_got_hit)

    if villain_got_hit:
        # something
        is_happy = True
        clock.schedule(remove_happy, 0.4)
        happy_counter = happy_counter + 1
    else: 
        is_happy = False
        miss_counter = miss_counter + 1


def remove_happy():
    global is_happy
    is_happy = False

    
        
      
