const SNAKE_BOARD_WIDTH = 520
const SNAKE_BOARD_SIZE = 20
const CELL_WIDTH = SNAKE_BOARD_WIDTH / SNAKE_BOARD_SIZE
const SNAKE_TIME_INTERVAL = 150

const Direction = {
  UP: 0,
  DOWN: 1,
  LEFT: 2,
  RIGHT: 3
}

const SNAKE_START_X = 5
const SNAKE_START_Y = 5
const SNAKE_START_DIR = Direction.RIGHT

const snake = {
  q: DQueue(),
  direction: SNAKE_START_DIR,
  nextDirection: SNAKE_START_DIR,
  head: {
    x: SNAKE_START_X,
    y: SNAKE_START_Y
  },
  alive: true,
  growth: 0
}

const food = {
  x: -1,
  y: -1
}

let snakeInterval = null

function initBoard() {
  const board = document.getElementById("snake-board")

  for (let i = 0; i < SNAKE_BOARD_SIZE; i++) {

    const row = document.createElement("div")
    row.classList.add("snake-board-row")
    board.appendChild(row)

    for (let j = 0; j < SNAKE_BOARD_SIZE; j++) {

      const cell = document.createElement("div")
      cell.classList.add("snake-board-cell")
      cell.classList.add("empty-cell")
      row.appendChild(cell)
    }
  }
}

function initSizes() {
  const board = document.getElementById("snake-board")
  board.style.width = px(SNAKE_BOARD_WIDTH)
  board.style.height = px(SNAKE_BOARD_WIDTH)

  const cells = document.querySelectorAll('.snake-board-cell')
  cells.forEach(cell => {
    cell.style.width = px(CELL_WIDTH)
    cell.style.height = px(CELL_WIDTH)
  });
}

function getCell(row, col) {
  const cells = document.getElementsByClassName("snake-board-cell")
  const index = row * SNAKE_BOARD_SIZE + col
  return cells[index]
}

function paintSnake(cell) {
  cell.classList.add('snake-body-cell')
  cell.classList.remove('food-cell')
  cell.classList.remove('empty-cell')
}

function paintEmpty(cell) {
  cell.classList.add('empty-cell')
  cell.classList.remove('snake-body-cell')
  cell.classList.remove('food-cell')
}

function paintFood(cell) {
  cell.classList.add('food-cell')
  cell.classList.remove('snake-body-cell')
  cell.classList.remove('empty-cell')
}

function isSnakeBody(cell) {
  return cell.classList.contains('snake-body-cell')
}

function initSnake() {
  const cell = getCell(SNAKE_START_Y, SNAKE_START_X)
  paintSnake(cell)
  snake.q.add(cell)
  window.addEventListener("keydown", keyEvent => {
    if (keyEvent.defaultPrevented) {
      return
    }
    switch (keyEvent.code) {
      case "ArrowUp":
      case "KeyW":
        if (snake.direction != Direction.DOWN) {
          snake.nextDirection = Direction.UP
        }
        break
      case "ArrowDown":
      case "KeyS":
        if (snake.direction != Direction.UP) {
          snake.nextDirection = Direction.DOWN
        }
        break
      case "ArrowLeft":
      case "KeyA":
        if (snake.direction != Direction.RIGHT) {
          snake.nextDirection = Direction.LEFT
        }
        break
      case "ArrowRight":
      case "KeyD":
        if (snake.direction != Direction.LEFT) {
          snake.nextDirection = Direction.RIGHT
        }
        break
    }
  })
}

function moveSnake() {
  if (snake.growth > 0) {
    snake.growth--;
  }
  else {
    const snakeTail = snake.q.poll()
    paintEmpty(snakeTail)
  }
  snake.direction = snake.nextDirection
  switch (snake.direction) {
    case Direction.UP:
      snake.head.y--
      break
    case Direction.DOWN:
      snake.head.y++
      break
    case Direction.LEFT:
      snake.head.x--
      break
    case Direction.RIGHT:
      snake.head.x++
      break
  }
  const minCoord = Math.min(snake.head.y, snake.head.x)
  const maxCoord = Math.max(snake.head.y, snake.head.x)
  if (minCoord < 0 || maxCoord >= SNAKE_BOARD_SIZE) {
    snake.alive = false
    clearInterval(snakeInterval)
    return
  }
  const newSnakeHead = getCell(snake.head.y, snake.head.x)
  if (isSnakeBody(newSnakeHead)) {
    snake.alive = false
    clearInterval(snakeInterval)
    return
  }
  paintSnake(newSnakeHead)
  snake.q.add(newSnakeHead)
  manageFood()
}

function placeFood() {
  do {
    food.y = randint(0, SNAKE_BOARD_SIZE - 1)
    food.x = randint(0, SNAKE_BOARD_SIZE - 1)
  }
  while (isSnakeBody(getCell(food.y, food.x)))
  paintFood(getCell(food.y, food.x))
}

function manageFood() {
  if (snake.head.y == food.y && snake.head.x == food.x) {
    snake.growth++
    placeFood()
  }
}

function snakeStart() {
  snakeInterval = setInterval(moveSnake, SNAKE_TIME_INTERVAL);
}

initBoard()
initSizes()
initSnake()
placeFood()
snakeStart()
