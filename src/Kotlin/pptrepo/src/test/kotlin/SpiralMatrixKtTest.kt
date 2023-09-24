import org.junit.jupiter.api.Test

internal class SpiralMatrixKtTest {
    @Test
    fun testSpiralMatrixSimple() {
        val expected = """
            [1 2 3 4 5]
            [16 17 18 19 6]
            [15 24 25 20 7]
            [14 23 22 21 8]
            [13 12 11 10 9]
        """.trimIndent()
        assert(expected == matrixPrettyString(spiralMatrixII(5)))
    }
}
