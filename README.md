cpptest
=======

Contains several macros that build on the basic assert() with more specific functionality to ease C++ testing

Originally built for testing coding projects at umich.

Usage
-----
 * Use `precondition()` at the very beginning of a function or even just before it begins to check whether your assumptions are correct.        
 * Likewise with `postcondition()`, except used right before returning at the end of a function, or in the calling function a line after the called function. I expect I will use precondition() more often, but hey, it's up to you.                 
 * Unlike pre- and post- condition, `test()` does not exit the program. This is to encourage test-driven development without inducing frustration.
 * Unlike with `assert()`, it is possible to pass an optional message along with your conditional so when reading output you know exactly what you were trying to accomplish
 * Use `unittest( /* ... */ )` to group tests and run them outside all other functions. All unittests will be run at the point you call `runUnitTests()` (first line of main makes sense) in a random order.
 * Print your location in the program along with a message using `message()`
 * Print your location in the program using `here()`
 * Everything is in namespace vitest (a portmanteau of "Vitez" and "test")
 * To avoid using c++11 or certain libraries (functional, algorithm, vector), just comment out the unittest section of the file

```cpp
int function(int test, string test2) {
  precondition(test <= 64, "Less than squares on a chess board");
  precondition(test2.size() > 0);
  message("Got to just before test++");
  test++;
  here();
  postcondition(test <= 65);
  return 7;
}

unittest (
  string str = "goodbye";
  test(function(5, "hello") == 7, "Should always be 7.");
  test(function(5, str) == 7);
)
```

*By Mitchell Vitez. Feel free to reuse and modify with attribution.*
