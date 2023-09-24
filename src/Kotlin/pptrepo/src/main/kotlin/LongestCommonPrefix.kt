/**
 * https://leetcode.com/problems/longest-common-prefix/
 */
class LongestCommonPrefix {
    fun longestCommonPrefix(strs: Array<String>): String {
        var returnstring = ""
        for(i in 0 .. strs.size){
            val c = strs[0][i]
            for(j in 0..strs[i].length)
                if(c == strs[i][j]){
                    returnstring = returnstring +  c


            }
        }

    }
    //not a necessary function//
    fun splitToList(s: String): MutableList<String>{
        val list = mutableListOf<String>()
        for(i in 0..s.length){
            list.add(s[i].toString())
        }
        return list
    }



}
fun main(){
    val lsp = LongestCommonPrefix()
    println(lsp.longestCommonPrefix(arrayOf("abd, abc, abdefm")))
}