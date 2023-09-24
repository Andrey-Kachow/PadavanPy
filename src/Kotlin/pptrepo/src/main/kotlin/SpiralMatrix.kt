enum class Direction {

    UP, DOWN, LEFT, RIGHT;

    fun turnRight(): Direction =
        when (this) {
            UP -> RIGHT
            RIGHT -> DOWN
            DOWN -> LEFT
            else -> UP
        }
}

class SpiralMatrixRunner(n: Int) {

    private val maxIndex = n

    private var row = 0
    private var col = 0
    private var direction = Direction.RIGHT

    fun turnRight() {
        direction = direction.turnRight()
    }

    fun advance() {
        when (direction) {
            Direction.RIGHT -> col++
            Direction.LEFT -> col--
            Direction.DOWN -> row++
            Direction.UP -> row--
        }
    }

    fun comeBack() {
        when (direction) {
            Direction.RIGHT -> col--
            Direction.LEFT -> col++
            Direction.DOWN -> row--
            Direction.UP -> row++
        }
    }

    fun placeNumber(arr: Array<IntArray>, number: Int) {
        arr[row][col] = number
    }

    fun stuck(arr: Array<IntArray>): Boolean =
        row == maxIndex || row == -1 || col == -1 || col == maxIndex || arr[row][col] != 0
}

fun spiralMatrixII(n: Int): Array<IntArray> {
    val nSquare = n * n
    val arr: Array<IntArray> = Array(n) { IntArray(n) }
    var acc = 1
    val runner = SpiralMatrixRunner(n)
    while (acc <= nSquare) {
        runner.placeNumber(arr, acc)
        runner.advance()
        if (runner.stuck(arr)) {
            runner.comeBack()
            runner.turnRight()
            runner.advance()
        }
        acc++
    }
    return arr
}

fun matrixPrettyString(arr: Array<IntArray>) =
    arr.joinToString("\n") {
        "[" + it.joinToString(" ") + "]"
    }

/**
 *  https://leetcode.com/problems/spiral-matrix-ii/
 */
fun main() {
    println(matrixPrettyString(spiralMatrixII(5)))
}
