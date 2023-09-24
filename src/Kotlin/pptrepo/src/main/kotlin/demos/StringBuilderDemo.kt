package demos

import kotlin.system.measureTimeMillis

class StringBuilderDemo {
    fun bigStringFromConcat(): String {
        var s = ""
        for (i in 0..10000) {
            s += i.toString()
        }
        return s
    }

    fun bigStringFromBuilder(): String {
        val sb = StringBuilder()
        for (i in 0..10000) {
            sb.append(i)
        }
        return sb.toString()
    }
}

fun main() {
    val demo = StringBuilderDemo()
    println("Starting concatenation")
    val elapsedConcat = measureTimeMillis {
        demo.bigStringFromConcat()
    }
    println("Concatenation of 10000 strings by concat took $elapsedConcat milliseconds")
    println("Now builder...")
    val elapsedBuilder = measureTimeMillis {
        demo.bigStringFromBuilder()
    }
    println("Concatenation of 10000 strings by builder took $elapsedBuilder milliseconds")
}

