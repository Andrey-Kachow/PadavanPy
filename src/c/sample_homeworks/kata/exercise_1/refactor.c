#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

# define M_PIl          3.141592653589793238462643383279502884L /* pi */


/*  PRELUDE: For testing the correctness of the answers */
//
//  DO NOT TOUCH THAT
//
#define TEST_CASE_VERBOSE "The provided example contains an unnecessary large quantity of words, because it is entended to demonstrate what the word verbose means"
void __assertEquals(char *, int, int, char *);
void __assertStringEquals(char *, char *, char *, char *);
void __assertDoubleEquals(char *, double, double, char *);
char test_buffer_expected[300];
char test_buffer_actual[300];
int double_approx_equal(double first, double second) {
    double comparison_delta = 0.00001;
    double difference = expected - actual;
    if (difference < 0) {
        difference = - difference;
    }
}
//////////////

/**
 *
 *   Refactoring is the process of restructuring code, while not changing its original functionality. 
 *   The goal of refactoring is to improve internal code by making many small changes without altering the code's **external behaviour**.
 *
 *   The main function of this file is running tests for the provided functions.
 *   Notice that initially all test cases pass.
 *   That is because the behaviour of the code is correct.
 *   However, the code is not maintainable and can be improved.
 *   The goal of this exercise is to improve the code withour breaking the tests (i.e. altering the code's **external behaviour**)
 */

//////////////////////////////////////////////////////////////////////////
//    Exercise 0: Before making any changes compile and run the code.   //
//    Observe that test cases pass.                                     //
//////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//    Exercise 1: Refactor the exponentiation functions as much as possible. //
///////////////////////////////////////////////////////////////////////////////

/*
    NOTE: refactor means you cannot delete the functions bellow and
    you are not allowed to change their type signature (return type and arguments).
    You have to remove duplication in the function body.
*/

double square(double number) {
    return number * number;
}

double cube(double number) {
    return number * number * number;
}

double quartic(double number) {
    double accumulator = 1;
    for (int count = 0; count < 4; count++) {
        accumulator *= number;
    }
    return accumulator;
}

double quintic(double number) {
    double accumulator = 1;
    for (int count = 0; count < 5; count++) {
        accumulator *= number;
    }
    return accumulator;
}

double sextic(double number) {
    double accumulator = 1;
    for (int count = 0; count < 6; count++) {
        accumulator *= number;
    }
    return accumulator;
}

double heptic(double number) {
    double accumulator = 1;
    for (int count = 0; count < 7; count++) {
        accumulator *= number;
    }
    return accumulator;
}

double power(double base, int exponent) {
    double accumulator = 1;
    for (int count = 0; count < exponent; count++) {
        accumulator *= base;
    }
    return accumulator;
}

//////////////////////////////////////////////////////////////////////////////
//    Exercise 2: Refactor the message logging functions as you see fit.    //
//////////////////////////////////////////////////////////////////////////////

/*
    Note: You may need to visit the documentation for `sprintf` function.
*/


char * log_ERROR(char *output_text_buffer, char * message) {
    int successful_sprinf = sprintf(output_text_buffer, "ERROR: %s", message);
    if (successful_sprinf < 0) {
        printf("Error during the string write!\n");
        return NULL;
    }
    return output_text_buffer;
}

char * log_WARNING(char *output_text_buffer, char * message) {
    int successful_sprinf = sprintf(output_text_buffer, "WARNING: %s", message);
    if (successful_sprinf < 0) {
        printf("Error during the string write!\n");
        return NULL;
    }
    return output_text_buffer;
}

char * log_INFO(char *output_text_buffer, char * message) {
    int successful_sprinf = sprintf(output_text_buffer, "INFO: %s", message);
    if (successful_sprinf < 0) {
        printf("Error during the string write!\n");
        return NULL;
    }
    return output_text_buffer;
}

char * log_VERBOSE(char *output_text_buffer, char * message) {
    int successful_sprinf = sprintf(output_text_buffer, "VERBOSE: %s", message);
    if (successful_sprinf < 0) {
        printf("Error during the string write!\n");
        return NULL;
    }
    return output_text_buffer;
}

/*
    Note: You may need to learn how enums work by yourself.
*/
enum LogType {
    ERROR,
    WARNING,
    INFO,
    VERBOSE
};

/*
    Note: You may need to learn about switch statement by yourself.
*/
char * from_LogType_to_string(enum LogType logType) {
    switch (logType) {
        case ERROR:
            return "ERROR";
        case WARNING:
            return "WARNING";
        case INFO:
            return "INFO";
        case VERBOSE:
            return "VERBOSE";
        default:
            printf("Incorrect log type...");
            return NULL;   
    };
}

char * log_message(char *output_text_buffer, enum LogType logType, char * message) {
    char *result_output;
    if (logType == ERROR) {
        result_output = log_ERROR(output_text_buffer, message);
    } else if (logType == WARNING) {
        result_output = log_WARNING(output_text_buffer, message);
    } else if (logType == INFO) {
        result_output = log_INFO(output_text_buffer, message);
    } else if (logType == VERBOSE) {
        result_output = log_VERBOSE(output_text_buffer, message);
    } else {
        printf("Incorrect log type...");
        return NULL;   
    }
    return result_output;
}

///////////////////////////////////////////////////////////////////////////
//    Exercise 3: Refactor the tigonometric functions as you see fit.    //
///////////////////////////////////////////////////////////////////////////

/*
    Note: The initial implementation of the trigonometric funcitons are provided here.
        https://math.libretexts.org/@api/deki/files/82284/clipboard_e8afaa2434d1b791a1a417519ad20ce3c.png?revision=1

    Note 2: In this exercise the behaviour of the function is to approximate the value of trigonometric calculations.
        Therefore we can sacrifice accuracy in favour of readability.

        Assume that readability is much more favourable than accuracy.
        If the test suite is passed, then the accuracy level is sufficient.

    Note 3: You are not allowed to use <math.h> for this exercise except sqrt (is it a hint?) and feel free to use the value of Pi. 
    Practice by yourself.
*/


double cos_radians(double x) {
    
    // McLaurin Series Expansion for Cos.
    double t_0_x0 = 1.0;
    double t_2_x2 = t_0_x0 * x / 1.0 * x / 2.0 * (-1.0);
    double t_4_x4 = t_2_x2 * x / 3.0 * x / 4.0 * (-1.0);
    double t_6_x6 = t_4_x4 * x / 5.0 * x / 6.0 * (-1.0);
    double t_8_x8 = t_6_x6 * x / 7.0 * x / 8.0 * (-1.0);
    double t_10_x10 = t_8_x8 * x / 9.0 * x / 10.0 * (-1.0);

    return t_10_x10 + t_8_x8 + t_6_x6 + t_4_x4 + t_2_x2 + t_0_x0;
}

double sin_radians(double x) {

    // McLaurin Series Expansion for Sin.
    double t_1_x1 = x;
    double t_3_x3 = t_1_x1 * x / 2.0 * x / 3.0 * (-1.0);
    double t_5_x5 = t_3_x3 * x / 4.0 * x / 5.0 * (-1.0);
    double t_7_x7 = t_5_x5 * x / 6.0 * x / 7.0 * (-1.0);
    double t_9_x9 = t_7_x7 * x / 8.0 * x / 9.0 * (-1.0);
    double t_11_x11 = t_9_x9 * x / 10.0 * x / 11.0 * (-1.0);
    
    return t_11_x11 + t_9_x9 + t_7_x7 + t_5_x5 + t_3_x3 + t_1_x1;
}

double cos_degrees(double deg) {
    
    // convert degrees to radians
    double x_rad = deg / 180 * M_PIl;  // 1° = π/180°
    double x = x_rad;

    // McLaurin Series Expansion for Cos.
    double t_0_x0 = 1.0;
    double t_2_x2 = t_0_x0 * x / 1.0 * x / 2.0 * (-1.0);
    double t_4_x4 = t_2_x2 * x / 3.0 * x / 4.0 * (-1.0);
    double t_6_x6 = t_4_x4 * x / 5.0 * x / 6.0 * (-1.0);
    double t_8_x8 = t_6_x6 * x / 7.0 * x / 8.0 * (-1.0);
    double t_10_x10 = t_8_x8 * x / 9.0 * x / 10.0 * (-1.0);

    return t_10_x10 + t_8_x8 + t_6_x6 + t_4_x4 + t_2_x2 + t_0_x0;
}

double sin_degrees(double deg) {

    // convert degrees to radians
    double x_rad = deg / 180 * M_PIl; // 1° = π/180°
    double x = x_rad;

    // McLaurin Series Expansion for Sin.
    double t_1_x1 = x;
    double t_3_x3 = t_1_x1 * x / 2.0 * x / 3.0 * (-1.0);
    double t_5_x5 = t_3_x3 * x / 4.0 * x / 5.0 * (-1.0);
    double t_7_x7 = t_5_x5 * x / 6.0 * x / 7.0 * (-1.0);
    double t_9_x9 = t_7_x7 * x / 8.0 * x / 9.0 * (-1.0);
    double t_11_x11 = t_9_x9 * x / 10.0 * x / 11.0 * (-1.0);
    
    return t_11_x11 + t_9_x9 + t_7_x7 + t_5_x5 + t_3_x3 + t_1_x1;
}


double sec_radians(double x) {
    
    // McLaurin Series Expansion for Cos.
    double t_0_x0 = 1.0;
    double t_2_x2 = t_0_x0 * x / 1.0 * x / 2.0 * (-1.0);
    double t_4_x4 = t_2_x2 * x / 3.0 * x / 4.0 * (-1.0);
    double t_6_x6 = t_4_x4 * x / 5.0 * x / 6.0 * (-1.0);
    double t_8_x8 = t_6_x6 * x / 7.0 * x / 8.0 * (-1.0);
    double t_10_x10 = t_8_x8 * x / 9.0 * x / 10.0 * (-1.0);

    return 1 / (t_10_x10 + t_8_x8 + t_6_x6 + t_4_x4 + t_2_x2 + t_0_x0);
}

double cosec_radians(double x) {

    // McLaurin Series Expansion for Sin.
    double t_1_x1 = x;
    double t_3_x3 = t_1_x1 * x / 2.0 * x / 3.0 * (-1.0);
    double t_5_x5 = t_3_x3 * x / 4.0 * x / 5.0 * (-1.0);
    double t_7_x7 = t_5_x5 * x / 6.0 * x / 7.0 * (-1.0);
    double t_9_x9 = t_7_x7 * x / 8.0 * x / 9.0 * (-1.0);
    double t_11_x11 = t_9_x9 * x / 10.0 * x / 11.0 * (-1.0);
    
    return 1 / (t_11_x11 + t_9_x9 + t_7_x7 + t_5_x5 + t_3_x3 + t_1_x1);
}

double sec_degrees(double deg) {
    
    // convert degrees to radians
    double x_rad = deg / 180 * M_PIl;  // 1° = π/180°
    double x = x_rad;

    // McLaurin Series Expansion for Cos.
    double t_0_x0 = 1.0;
    double t_2_x2 = t_0_x0 * x / 1.0 * x / 2.0 * (-1.0);
    double t_4_x4 = t_2_x2 * x / 3.0 * x / 4.0 * (-1.0);
    double t_6_x6 = t_4_x4 * x / 5.0 * x / 6.0 * (-1.0);
    double t_8_x8 = t_6_x6 * x / 7.0 * x / 8.0 * (-1.0);
    double t_10_x10 = t_8_x8 * x / 9.0 * x / 10.0 * (-1.0);

    return 1 / (t_10_x10 + t_8_x8 + t_6_x6 + t_4_x4 + t_2_x2 + t_0_x0) ;
}

double cosec_degrees(double deg) {

    // convert degrees to radians
    double x_rad = deg / 180 * M_PIl; // 1° = π/180°
    double x = x_rad;

    // McLaurin Series Expansion for Sin.
    double t_1_x1 = x;
    double t_3_x3 = t_1_x1 * x / 2.0 * x / 3.0 * (-1.0);
    double t_5_x5 = t_3_x3 * x / 4.0 * x / 5.0 * (-1.0);
    double t_7_x7 = t_5_x5 * x / 6.0 * x / 7.0 * (-1.0);
    double t_9_x9 = t_7_x7 * x / 8.0 * x / 9.0 * (-1.0);
    double t_11_x11 = t_9_x9 * x / 10.0 * x / 11.0 * (-1.0);
    
    return 1 / (t_11_x11 + t_9_x9 + t_7_x7 + t_5_x5 + t_3_x3 + t_1_x1);
}

double tan_radians(double x) {
    
    // McLaurin Series Expansion for Cos.
    double t_0_x0 = 1.0;
    double t_2_x2 = t_0_x0 * x / 1.0 * x / 2.0 * (-1.0);
    double t_4_x4 = t_2_x2 * x / 3.0 * x / 4.0 * (-1.0);
    double t_6_x6 = t_4_x4 * x / 5.0 * x / 6.0 * (-1.0);
    double t_8_x8 = t_6_x6 * x / 7.0 * x / 8.0 * (-1.0);
    double t_10_x10 = t_8_x8 * x / 9.0 * x / 10.0 * (-1.0);

    double cos = t_10_x10 + t_8_x8 + t_6_x6 + t_4_x4 + t_2_x2 + t_0_x0;

    // McLaurin Series Expansion for Sin.
    double t_1_x1 = x;
    double t_3_x3 = t_1_x1 * x / 2.0 * x / 3.0 * (-1.0);
    double t_5_x5 = t_3_x3 * x / 4.0 * x / 5.0 * (-1.0);
    double t_7_x7 = t_5_x5 * x / 6.0 * x / 7.0 * (-1.0);
    double t_9_x9 = t_7_x7 * x / 8.0 * x / 9.0 * (-1.0);
    double t_11_x11 = t_9_x9 * x / 10.0 * x / 11.0 * (-1.0);

    double sin =  t_11_x11 + t_9_x9 + t_7_x7 + t_5_x5 + t_3_x3 + t_1_x1;

    return sin / cos;
}

double tan_degrees(double deg) {
    
    // convert degrees to radians
    double x_rad = deg / 180 * M_PIl;  // 1° = π/180°
    double x = x_rad;

    // McLaurin Series Expansion for Cos.
    double t_0_x0 = 1.0;
    double t_2_x2 = t_0_x0 * x / 1.0 * x / 2.0 * (-1.0);
    double t_4_x4 = t_2_x2 * x / 3.0 * x / 4.0 * (-1.0);
    double t_6_x6 = t_4_x4 * x / 5.0 * x / 6.0 * (-1.0);
    double t_8_x8 = t_6_x6 * x / 7.0 * x / 8.0 * (-1.0);
    double t_10_x10 = t_8_x8 * x / 9.0 * x / 10.0 * (-1.0);

    double cos = t_10_x10 + t_8_x8 + t_6_x6 + t_4_x4 + t_2_x2 + t_0_x0;

    // McLaurin Series Expansion for Sin.
    double t_1_x1 = x;
    double t_3_x3 = t_1_x1 * x / 2.0 * x / 3.0 * (-1.0);
    double t_5_x5 = t_3_x3 * x / 4.0 * x / 5.0 * (-1.0);
    double t_7_x7 = t_5_x5 * x / 6.0 * x / 7.0 * (-1.0);
    double t_9_x9 = t_7_x7 * x / 8.0 * x / 9.0 * (-1.0);
    double t_11_x11 = t_9_x9 * x / 10.0 * x / 11.0 * (-1.0);
    
    double sin = t_11_x11 + t_9_x9 + t_7_x7 + t_5_x5 + t_3_x3 + t_1_x1;

    return sin / cos;
}

double cot_radians(double x) {
    
    // McLaurin Series Expansion for Cos.
    double t_0_x0 = 1.0;
    double t_2_x2 = t_0_x0 * x / 1.0 * x / 2.0 * (-1.0);
    double t_4_x4 = t_2_x2 * x / 3.0 * x / 4.0 * (-1.0);
    double t_6_x6 = t_4_x4 * x / 5.0 * x / 6.0 * (-1.0);
    double t_8_x8 = t_6_x6 * x / 7.0 * x / 8.0 * (-1.0);
    double t_10_x10 = t_8_x8 * x / 9.0 * x / 10.0 * (-1.0);

    double cos = t_10_x10 + t_8_x8 + t_6_x6 + t_4_x4 + t_2_x2 + t_0_x0;

    // McLaurin Series Expansion for Sin.
    double t_1_x1 = x;
    double t_3_x3 = t_1_x1 * x / 2.0 * x / 3.0 * (-1.0);
    double t_5_x5 = t_3_x3 * x / 4.0 * x / 5.0 * (-1.0);
    double t_7_x7 = t_5_x5 * x / 6.0 * x / 7.0 * (-1.0);
    double t_9_x9 = t_7_x7 * x / 8.0 * x / 9.0 * (-1.0);
    double t_11_x11 = t_9_x9 * x / 10.0 * x / 11.0 * (-1.0);
    
    double sin =  t_11_x11 + t_9_x9 + t_7_x7 + t_5_x5 + t_3_x3 + t_1_x1;

    return cos / sin;
}

double cot_degrees(double deg) {
    
    // convert degrees to radians
    double x_rad = deg / 180 * M_PIl;  // 1° = π/180°
    double x = x_rad;

    // McLaurin Series Expansion for Cos.
    double t_0_x0 = 1.0;
    double t_2_x2 = t_0_x0 * x / 1.0 * x / 2.0 * (-1.0);
    double t_4_x4 = t_2_x2 * x / 3.0 * x / 4.0 * (-1.0);
    double t_6_x6 = t_4_x4 * x / 5.0 * x / 6.0 * (-1.0);
    double t_8_x8 = t_6_x6 * x / 7.0 * x / 8.0 * (-1.0);
    double t_10_x10 = t_8_x8 * x / 9.0 * x / 10.0 * (-1.0);

    double cos = t_10_x10 + t_8_x8 + t_6_x6 + t_4_x4 + t_2_x2 + t_0_x0;

    // McLaurin Series Expansion for Sin.
    double t_1_x1 = x;
    double t_3_x3 = t_1_x1 * x / 2.0 * x / 3.0 * (-1.0);
    double t_5_x5 = t_3_x3 * x / 4.0 * x / 5.0 * (-1.0);
    double t_7_x7 = t_5_x5 * x / 6.0 * x / 7.0 * (-1.0);
    double t_9_x9 = t_7_x7 * x / 8.0 * x / 9.0 * (-1.0);
    double t_11_x11 = t_9_x9 * x / 10.0 * x / 11.0 * (-1.0);
    
    double sin = t_11_x11 + t_9_x9 + t_7_x7 + t_5_x5 + t_3_x3 + t_1_x1;

    return cos / sin;
}

/*
    Hint: If you are lost with trigonometric functions, then check the following link...
    https://www.dummies.com/wp-content/uploads/323191.image0.png
*/

///////////////////////////////////////////////////////////////////////////
//                Exercise 4: Challenge: See below                       //
///////////////////////////////////////////////////////////////////////////

/*
    Description:
    After you completed tasks 1-3 and all of the test cases pass,
    look at the ____assert[Something]Equals functions at the bottom of the file.
    Then answer the questions bellow. Replace lines with typewritten text.

    
    I.  
    Do you see any similiaries between them? List your observations here:
        1) ______________
        2) ______________
        ... maybe more or not at all.


    II. 
    Do you see any differences between them? List your observations here:
        1) ______________
        2) ______________
        ... maybe more or not at all.
    

    III. 
    Do you think it is possible to create some universal assertion method?
    List any ideas or thoughts bellow.
        1) ______________
        2) ______________
        ... maybe more or not at all.

    IV.
    Does any of your ideas undoubtedly improves the code? Does implementing them worth the time and effort?
        (a) yes       (b) no        (c) unsure
        (d) some of them may worth it (write in the comments)

        Comments: ________________________
        __________________________________
        __________________________________
        __________________________________

    V.
    If you chose (a) or (d) in question (IV), 
    then attempt to implement your idea(s) and create the following funcitons, utilising some common code or properties.
        1) __assertEquals__task_4v
        2) __assertStringEquals__task_4v
        3) __assertDoubleEquals__task_4v

        Note: that there are still shall be three functions, so we can pretend to implement the same I N T E R F A C E.
        (We will learn the concept of interfaces soon)

    VI. 
    The challenge for real 313373 tryhards or graphomaniacs (voluntary task)
        //
        Design a universal assertion framework that supports the following features:
            1) Comparison between int, double, string and maybe even more types.
            2) Generation of sensible error messages that break down the input and output.
            3) Ability to append custom error messages.
        
        Note: Feel free to use macros, structs, function pointers (in C)
              or even classes, lambas and other language features (in C++)

*/

////////////////////////////////////////////////////////////////////
//                      EXERCISES END HERE                        //
////////////////////////////////////////////////////////////////////

int main() {
    __assertEquals("Case 01 square(0)", power(0, 2), square(0), "exponentiation of zero");
    __assertEquals("Case 02 square(1)", power(4, 2), square(4), "regular exponentiation");
    __assertEquals("Case 03 cube(1)", power(1, 3), cube(1), "exponentiation of one");
    __assertEquals("Case 04 cube(3)", power(3, 3), cube(3), "regular exponentiation");
    __assertEquals("Case 05 quartic(4)", power(4, 4), quartic(4), "regular exponentiation");
    __assertEquals("Case 06 quartic(0)", power(0, 4), quartic(0), "exponentiation of zero");
    __assertEquals("Case 07 quartic(2)", power(2, 4), quartic(2), "regular exponentiation");
    __assertEquals("Case 08 quintic(3)", power(3, 5), quintic(3), "exponentiation of zero");
    __assertEquals("Case 09 quintic(4)", power(4, 5), quintic(4), "regular exponentiation");
    __assertEquals("Case 10 quintic(5)", power(5, 5), quintic(5), "regular exponentiation");
    __assertEquals("Case 11 quintic(8)", power(8, 5), quintic(8), "regular exponentiation");
    __assertEquals("Case 12 sextic(6)", power(6, 6), sextic(6), "regular exponentiation");
    __assertEquals("Case 13 sextic(1)", power(1, 6), sextic(1), "regular exponentiation");
    __assertEquals("Case 14 sextic(5)", power(5, 6), sextic(5), "regular exponentiation");
    __assertEquals("Case 15 heptic(5)", power(5, 7), heptic(5), "regular exponentiation");
    __assertEquals("Case 16 heptic(2)", power(2, 7), heptic(2), "regular exponentiation");
    __assertEquals("Case 17 heptic(1)", power(1, 7), heptic(1), "regular exponentiation");

    __assertStringEquals(
        "Case 18 log_ERROR(\"some error message\")", 
        log_message(test_buffer_expected, ERROR, "some error message"),
        log_ERROR(test_buffer_actual, "some error message"), 
        "log message should begin with ERROR"
    );
    __assertStringEquals(
        "Case 19 log_WARNING(\"some warning message\")",
        log_message(test_buffer_expected, WARNING, "some warning message"),
        log_WARNING(test_buffer_actual, "some warning message"), 
        "log message should begin with WARNING"
    );
    __assertStringEquals(
        "Case 20 log_INFO(\"some info message\")", 
        log_message(test_buffer_expected, INFO, "some info message"),
        log_INFO(test_buffer_actual, "some info message"), 
        "log message should begin with INFO"
    );
    __assertStringEquals(
        "Case 21 log_VERBOSE(TEST_CASE_VERBOSE)", 
        log_message(test_buffer_expected, VERBOSE, TEST_CASE_VERBOSE),
        log_VERBOSE(test_buffer_actual, TEST_CASE_VERBOSE), 
        "log message should begin with VERBOSE"
    );


    //
    __assertDoubleEquals("Case 22", 0, sin_degrees(0), "Standard table value");
    __assertDoubleEquals("Case 23", 1.0/2.0, sin_degrees(30), "Standard table value");
    __assertDoubleEquals("Case 24", sqrt(2)/2.0, sin_degrees(45), "Standard table value");
    __assertDoubleEquals("Case 25", sqrt(3)/2.0, sin_degrees(60), "Standard table value");
    __assertDoubleEquals("Case 26", 1, sin_degrees(90), "Standard table value");
    //
    __assertDoubleEquals("Case 27", 1.0, cos_degrees(0), "Standard table value");
    __assertDoubleEquals("Case 28", sqrt(3)/2.0, cos_degrees(30), "Standard table value");
    __assertDoubleEquals("Case 29", sqrt(2)/2.0, cos_degrees(45), "Standard table value");
    __assertDoubleEquals("Case 30", 1.0/2.0, cos_degrees(60), "Standard table value");
    __assertDoubleEquals("Case 31", 0.0, cos_degrees(90), "Standard table value");
    //
    __assertDoubleEquals("Case 32", 0.0, tan_degrees(0), "Standard table value");
    __assertDoubleEquals("Case 33", 1.0/sqrt(3.0), tan_degrees(30.0), "Standard table value");
    __assertDoubleEquals("Case 34", 1.0, tan_degrees(45.0), "Standard table value");
    __assertDoubleEquals("Case 35", sqrt(3.0), tan_degrees(60), "Standard table value");
    //
    __assertDoubleEquals("Case 36", sqrt(3), cot_degrees(30), "Standard table value");
    __assertDoubleEquals("Case 37", 1.0, cot_degrees(45), "Standard table value");
    __assertDoubleEquals("Case 38", 1.0/sqrt(3.0), cot_degrees(60), "Standard table value");
    __assertDoubleEquals("Case 39", 0.0, cot_degrees(90), "Standard table value");
    //
    __assertDoubleEquals("Case 40", 1.0, sec_degrees(0), "Standard table value");
    __assertDoubleEquals("Case 41", 2/sqrt(3), sec_degrees(30), "Standard table value");
    __assertDoubleEquals("Case 42", sqrt(2), sec_degrees(45), "Standard table value");
    __assertDoubleEquals("Case 43", 2.0, sec_degrees(60), "Standard table value");
    //
    __assertDoubleEquals("Case 44", 2.0, cosec_degrees(30), "Standard table value");
    __assertDoubleEquals("Case 45", sqrt(2), cosec_degrees(45), "Standard table value");
    __assertDoubleEquals("Case 46", 2.0/sqrt(3), cosec_degrees(60), "Standard table value");
    __assertDoubleEquals("Case 47", 1.0, cosec_degrees(90), "Standard table value");
    //

    //
    __assertDoubleEquals("Case 48", 0, sin_radians(0), "Standard table value");
    __assertDoubleEquals("Case 49", 1.0/2.0, sin_radians(30.0/ 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 50", sqrt(2)/2, sin_radians(45.0/ 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 51", sqrt(3)/2, sin_radians(60.0/ 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 52", 1.0, sin_radians(90.0/ 180 * M_PIl), "Standard table value");
    //
    __assertDoubleEquals("Case 54", 1.0, cos_radians(0), "Standard table value");
    __assertDoubleEquals("Case 55", sqrt(3)/2, cos_radians(30.0/ 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 56", sqrt(2)/2, cos_radians(45.0/ 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 57", 1.0/2.0, cos_radians(60.0/ 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 58", 0, cos_radians(90.0/ 180 * M_PIl), "Standard table value");
    //
    __assertDoubleEquals("Case 59", 0.0, tan_radians(0), "Standard table value");
    __assertDoubleEquals("Case 60", 1.0/sqrt(3), tan_radians(30.0 / 180.0 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 61", 1, tan_radians(45.0/ 180.0 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 62", sqrt(3), tan_radians(60.0 / 180.0 * M_PIl), "Standard table value");
    //
    __assertDoubleEquals("Case 63", sqrt(3), cot_radians(30.0 / 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 64", 1.0, cot_radians(45 / 180.0 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 65", 1.0/sqrt(3), cot_radians(60.0 / 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 66", 0, cot_radians(90.0 / 180.0 * M_PIl), "Standard table value");
    //
    __assertDoubleEquals("Case 67", 1.0, sec_radians(0), "Standard table value");
    __assertDoubleEquals("Case 68", 2.0/sqrt(3), sec_radians(30.0 / 180.0 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 69", sqrt(2), sec_radians(45.0 / 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 70", 2, sec_radians(60.0 / 180 * M_PIl), "Standard table value");
    //
    __assertDoubleEquals("Case 71", 2.0, cosec_radians(30.0 / 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 72", sqrt(2), cosec_radians(45.0 / 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 73", 2.0/sqrt(3), cosec_radians(60.0 / 180 * M_PIl), "Standard table value");
    __assertDoubleEquals("Case 74", 1.0, cosec_radians(90.0 / 180.0 * M_PIl), "Standard table value");
    //
}

void __assertEquals(char *caseName, int expected, int actual, char *errorMsg) {
    if (expected == actual) {
        printf("%s: PASS\n", caseName);
    } else {
        printf(
            "%s: FAIL --> expected %d, but got %d (comments:  %s)\n",
             caseName,          expected,     actual,       errorMsg
        );
    }
}

void __assertStringEquals(char *caseName, char *expected, char *actual, char *errorMsg) {
    if (strcmp(expected, actual) == 0) {
        printf("%s: PASS\n", caseName);
    } else {
        printf(
            "%s: FAIL --> expected \"%s\", but got \"%s\" (comments:  %s)\n",
             caseName,            expected,        actual,           errorMsg
        );
    }
}

void __assertDoubleEquals(char *caseName, double expected, double actual, char *errorMsg) {
    if (double_approx_equal(expected, actual)) {
        printf("%s: PASS\n", caseName);
    } else {
        printf(
            "%s: FAIL --> expected %0.10f, but got %0.10f (comments:  %s)  (extra notes: double comparison deviation is too high)\n",
             caseName,            expected,        actual,          errorMsg
        );
    }
}