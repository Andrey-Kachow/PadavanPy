#include <stdio.h>


// test functions declaration
void run_tests();
void run_more_tests();


/*
    Given string arguments `text` and `prefix`,
    Write a predicate* that decides** whether or not the given
    text begins with the given prefix.
    
    Example:
        starts_with("Hello World!", "Hello") // should return true.
        starts_with("12345", "234") // returns false

    Footnotes: 
        *Predicate in programming is a common name for a function that returns boolean
        **Decision problems are such that have only two possible answers: yes or no (there are also undecidable problems)
*/
bool starts_with(char * text, char * prefix) {
    return false;
}

/*
    Given string arguments `text` and `suffix`,
    Write a predicate that decides whether or not the given
    text ends with the given suffix.
    
    Example:
        ends_with("Hello World!", "World!") // should return true.
        ends_with("Hello World!", "World") // returns false

*/
bool ends_with(char * text, char * suffix) {
    return false;
}

/*
    Given two strings `text` and `part` write a predicate that checks
    if the text fully contains the part as its substring. The function
    returns true if the part is a substring. 
    
    Note: 
        - Substring does not have to be shorter than the original text. 
          If two texts are identical, then they are substrings of each other,
          thus the function is_substring shall return true.
        
        - You may use Hint 1 for inspiration.

    Examples: 
        - In string "Hello World!", "llo Wo", "W", and "d!" are substrings.
        - "Hello World!" is also a substring of "Hello World!".
        - is_substring("12345", "34") returns true.
*/
bool is_substring(char * text, char * part) {
    return false;
}

/*
    Write a funciton that accepts two strings: 
        - `text` representing the whole text 
        - `part` that is a substring inside `text`

    and finds the position of part inside text.
    Position is the index at which the substring starts.
    
    Error Handling: 
        - If the substring was not found in the text, 
          the function shall return -1;

    Ambiguity Resolution: 
        - If the substring occurs in the text more than once, 
          return position of the first occurrence

    Examples:
        index_of_substring("To be or not to be", "to"); // evaluates to 12
        index_of_substring("To be or not to be", "be"); // shall return 3
        index_of_substring("To be or not to be", "bee"); // evaluates to -1
*/
int index_of_substring(char * text, char * part) {
    return -1;
}

/*
    Write a function that counts how many times 
    the substring `part` occurs in the whole `text`
    Occurences can overlap and still be incuded in the count.

    Examples:

    count_substring_occurrences("To be or not to be", "be"); // evaluates to 2
    count_substring_occurrences("AAA", "A"); // evaluates to 3
    count_substring_occurrences("AAA", "AA"); // returns 2
    count_substring_occurrences("To be or not to be", " "); // returns 5
*/
int count_substring_occurrences(char * text, char * part) {
    return -1;
}


/*
    Write an alphanumeric comparator for strings that may contain any ASCII characters

    The function should check which of the two strings goes first in alphabet 
    and return one of the three possible outcomes

    Returns;
        -1 ~ if the first string goes before the second alphabetically
         1 ~ if the first string goes after the second alphabetically
         0 ~ if both strings have identical contents

    For Example:
        compare_strings("Apple", "Banana")    //    -1
        compare_strings("Pear", "Pear")       //    0
        compare_strings("a", "A")             //    1
        
    Note: You may use hints 2 and 3 (at the bottom) to help find a solution
*/
int compare_strings(char * first, char * second) {
    return 0;
}


int main()
{
    run_tests();
    run_more_tests();
    return 0;
}

/*             HINTS:
##################################################################


Hint 1:
    - Substring is a suffix of a prefix... or a prefix of a suffix... 






Hint 2:
    - Computers cannot compare letters, but they can compare numbers.
    
    
    
    
    
    
Hint 3:
    - Remember, that a character of text is just a number between 0 and 127 (or up to 255 in extended ASCII)





##################################################################
*/

void run_tests() {
    // starts_with tests
    if (starts_with("Hello World!", "Hello") != true)
        printf("Error: starts_with(\"Hello World!\", \"Hello\") failed\n");

    if (starts_with("12345", "234") != false)
        printf("Error: starts_with(\"12345\", \"234\") failed\n");

    // ends_with tests
    if (ends_with("Hello World!", "World!") != true)
        printf("Error: ends_with(\"Hello World!\", \"World!\") failed\n");

    if (ends_with("Hello World!", "World") != false)
        printf("Error: ends_with(\"Hello World!\", \"World\") failed\n");

    // is_substring tests
    if (is_substring("Hello World!", "llo Wo") != true)
        printf("Error: is_substring(\"Hello World!\", \"llo Wo\") failed\n");

    if (is_substring("12345", "34") != true)
        printf("Error: is_substring(\"12345\", \"34\") failed\n");

    if (is_substring("Hello", "Hello") != true)
        printf("Error: is_substring(\"Hello\", \"Hello\") failed\n");

    if (is_substring("Hello", "xyz") != false)
        printf("Error: is_substring(\"Hello\", \"xyz\") failed\n");

    // index_of_substring tests
    if (index_of_substring("To be or not to be", "to") != 12)
        printf("Error: index_of_substring(\"To be or not to be\", \"to\") failed\n");

    if (index_of_substring("To be or not to be", "be") != 3)
        printf("Error: index_of_substring(\"To be or not to be\", \"be\") failed\n");

    if (index_of_substring("To be or not to be", "bee") != -1)
        printf("Error: index_of_substring(\"To be or not to be\", \"bee\") failed\n");

    // count_substring_occurrences tests
    if (count_substring_occurrences("To be or not to be", "be") != 2)
        printf("Error: count_substring_occurrences(\"To be or not to be\", \"be\") failed\n");

    if (count_substring_occurrences("AAA", "A") != 3)
        printf("Error: count_substring_occurrences(\"AAA\", \"A\") failed\n");

    if (count_substring_occurrences("AAA", "AA") != 2)
        printf("Error: count_substring_occurrences(\"AAA\", \"AA\") failed\n");

    if (count_substring_occurrences("To be or not to be", " ") != 5)
        printf("Error: count_substring_occurrences(\"To be or not to be\", \" \") failed\n");

    // compare_strings tests
    if (compare_strings("Apple", "Banana") != -1)
        printf("Error: compare_strings(\"Apple\", \"Banana\") failed\n");

    if (compare_strings("Pear", "Pear") != 0)
        printf("Error: compare_strings(\"Pear\", \"Pear\") failed\n");

    if (compare_strings("a", "A") != 1)
        printf("Error: compare_strings(\"a\", \"A\") failed\n");

    printf("Tests completed.\n");
}

void run_more_tests() {
    // starts_with edge cases
    if (starts_with("", "") != true)
        printf("Error: starts_with(\"\", \"\") failed\n");

    if (starts_with("Hello", "") != true)
        printf("Error: starts_with(\"Hello\", \"\") failed\n");

    if (starts_with("", "Hi") != false)
        printf("Error: starts_with(\"\", \"Hi\") failed\n");

    if (starts_with("abc", "abcd") != false)
        printf("Error: starts_with(\"abc\", \"abcd\") failed\n");

    // ends_with edge cases
    if (ends_with("", "") != true)
        printf("Error: ends_with(\"\", \"\") failed\n");

    if (ends_with("Hello", "") != true)
        printf("Error: ends_with(\"Hello\", \"\") failed\n");

    if (ends_with("", "Hi") != false)
        printf("Error: ends_with(\"\", \"Hi\") failed\n");

    if (ends_with("abc", "abcd") != false)
        printf("Error: ends_with(\"abc\", \"abcd\") failed\n");

    // is_substring edge cases
    if (is_substring("", "") != true)
        printf("Error: is_substring(\"\", \"\") failed\n");

    if (is_substring("abc", "") != true)
        printf("Error: is_substring(\"abc\", \"\") failed\n");

    if (is_substring("", "a") != false)
        printf("Error: is_substring(\"\", \"a\") failed\n");

    if (is_substring("aaaaa", "aaa") != true)
        printf("Error: is_substring(\"aaaaa\", \"aaa\") failed\n");

    if (is_substring("abcdef", "def") != true)
        printf("Error: is_substring(\"abcdef\", \"def\") failed\n");

    if (is_substring("abcdef", "gh") != false)
        printf("Error: is_substring(\"abcdef\", \"gh\") failed\n");

    // index_of_substring edge cases
    if (index_of_substring("", "") != 0)
        printf("Error: index_of_substring(\"\", \"\") failed\n");

    if (index_of_substring("abc", "") != 0)
        printf("Error: index_of_substring(\"abc\", \"\") failed\n");

    if (index_of_substring("", "a") != -1)
        printf("Error: index_of_substring(\"\", \"a\") failed\n");

    if (index_of_substring("aaaaa", "aaa") != 0)
        printf("Error: index_of_substring(\"aaaaa\", \"aaa\") failed\n");

    if (index_of_substring("abcabcabc", "abc") != 0)
        printf("Error: index_of_substring(\"abcabcabc\", \"abc\") failed\n");

    if (index_of_substring("abcabcabc", "bca") != 1)
        printf("Error: index_of_substring(\"abcabcabc\", \"bca\") failed\n");

    // count_substring_occurrences edge cases
    if (count_substring_occurrences("", "") != 0)
        printf("Error: count_substring_occurrences(\"\", \"\") failed\n");

    if (count_substring_occurrences("abc", "") != 0)
        printf("Error: count_substring_occurrences(\"abc\", \"\") failed\n");

    if (count_substring_occurrences("", "a") != 0)
        printf("Error: count_substring_occurrences(\"\", \"a\") failed\n");

    if (count_substring_occurrences("aaaa", "aa") != 3)
        printf("Error: count_substring_occurrences(\"aaaa\", \"aa\") failed\n");

    if (count_substring_occurrences("abababa", "aba") != 3)
        printf("Error: count_substring_occurrences(\"abababa\", \"aba\") failed\n");

    if (count_substring_occurrences("abcde", "f") != 0)
        printf("Error: count_substring_occurrences(\"abcde\", \"f\") failed\n");

    // compare_strings edge cases
    if (compare_strings("", "") != 0)
        printf("Error: compare_strings(\"\", \"\") failed\n");

    if (compare_strings("", "a") != -1)
        printf("Error: compare_strings(\"\", \"a\") failed\n");

    if (compare_strings("a", "") != 1)
        printf("Error: compare_strings(\"a\", \"\") failed\n");

    if (compare_strings("abc", "abcd") != -1)
        printf("Error: compare_strings(\"abc\", \"abcd\") failed\n");

    if (compare_strings("abcd", "abc") != 1)
        printf("Error: compare_strings(\"abcd\", \"abc\") failed\n");

    if (compare_strings("ABC", "abc") != -1)
        printf("Error: compare_strings(\"ABC\", \"abc\") failed\n");

    if (compare_strings("abc", "ABC") != 1)
        printf("Error: compare_strings(\"abc\", \"ABC\") failed\n");

    printf("More tests completed.\n");
}
