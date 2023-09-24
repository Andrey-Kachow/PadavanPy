fun twoSum(nums: IntArray, target: Int): IntArray {
    val differences = List(nums.size) { initIndex ->
        nums.map {
            it - nums[initIndex]
        }
    }
    println(differences.toString())
    return intArrayOf(0, 0)
}


fun main(args: Array<String>) {
    println("Hello World!")

    twoSum(intArrayOf(2, 7, 11, 15), 9)

//    xs.forEachIndexed { index, elem ->
//        println("$index, $elem")
//    }
}