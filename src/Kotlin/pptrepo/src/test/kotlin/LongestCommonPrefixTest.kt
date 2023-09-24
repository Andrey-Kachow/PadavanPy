import org.junit.jupiter.api.Test
import kotlin.test.assertEquals

internal class LongestCommonPrefixTest {

    @Test
    fun emptyStringPrefix() {
        assertEquals(
            "",
            LongestCommonPrefix()
                .longestCommonPrefix(
                    arrayOf(
                        "babc, a",
                        "zabcdef",
                        "dabcsderpcse"
                    )
                ).also { println(it) }
        )
    }

    @Test
    fun someTests() {
        assertEquals(
            "abc",
            LongestCommonPrefix()
                .longestCommonPrefix(
                    arrayOf(
                        "abc, a",
                        "abcdef",
                        "abcsderpcse"
                    )
                ).also { println(it) }
        )
        assertEquals(
            "aaaaa",
            LongestCommonPrefix()
                .longestCommonPrefix(
                    arrayOf(
                        "aaaaaaaaaaaaaaaaa",
                        "aaaaabbbbb",
                        "aaaaaaaaaaaa"
                    )
                ).also { println(it) }
        )
    }
}
