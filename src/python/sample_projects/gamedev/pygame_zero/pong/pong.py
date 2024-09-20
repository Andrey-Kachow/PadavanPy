WIDTH = 500
HEIGHT = 300

white = (255, 255, 255)

player_width = 20
player_height = 60

player_one_horisontal_position = 40
player_one_vertical_position = HEIGHT / 2 - player_height / 2

player_two_horisontal_position = WIDTH - player_width - 40
player_two_vertical_position = HEIGHT / 2 - player_height / 2


def draw_player_one():
    player_position = (player_one_horisontal_position, player_one_vertical_position)
    player_dimensions = (player_width, player_height)
    pong_paddle_rect = Rect(player_position, player_dimensions)
    screen.draw.filled_rect(pong_paddle_rect, color=white)

def draw_player_two():
    player_position = (player_two_horisontal_position, player_two_vertical_position)
    player_dimensions = (player_width, player_height)
    pong_paddle_rect = Rect(player_position, player_dimensions)
    screen.draw.filled_rect(pong_paddle_rect, color=white)

def draw():
   
    draw_player_one()
    draw_player_two()
