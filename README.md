cpptest
=======

Contains several macros that build on the basic assert() with more specific functionality to ease C++ testing

Originally built for testing coding projects at umich.

Usage
-----
 * Use precondition() at the very beginning of a function to check whether your assumptions are correct.                        
 * Likewise with postcondition(), except used right before returning at the end of a function.                                          
 * test() does not exit the program. This is to encourage test-driven development without inducing frustration.
 * Unlike with assert(), it is possible to pass an optional message along with your conditional so reading output you know exactly what you were trying to accomplish                     

  int function(int test, string test2) {
    precondition(test <= 64, "Less than squares on a chess board");
    precondition(test2.size() > 0);
    test++;
    postcondition(test <= 65);
    return 7;
  }
  
  test(function(5, "hello") == 7, "Should always be 7.");
  test(function(5, "hello") == 7);

*By Mitchell Vitez. Feel free to reuse and modify with attribution.*