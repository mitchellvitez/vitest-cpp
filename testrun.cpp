/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	Testing for test.h (It's turtles all the way down)                 *
 * By Mitchell Vitez. Feel free to reuse and modify with attribution.  *
 * Originally built for testing coding projects at umich.              *
 * Nov 20 2014 | mvitez@umich.edu | www.vitez.me                       *
 *                                                                     *
 * USAGE: use precondition() at the very beginning of a function to    *
 *  check whether your assumptions are correct.                        *
 *  Likewise with postcondition(), except used right before returning  *
 *  at the end of a function.                                          *
 *                                                                     *
 *  test() does not exit the program. This is to encourage test-   *
 *  driven development without inducing frustration.                   *
 *                                                                     *
 *  Unlike with assert(), it is possible to pass an optional message   *
 *  along with your conditional so reading output you know exactly     *
 *  what you were trying to accomplish                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "test.h"
#include <iostream>

// Returns (n+1) squared
int workingFunction(int n) {
	precondition(n < 10000, "Is n reasonably small?");
	precondition(n != 0, "n should be nonzero");
	precondition(n > -10000);
	n++;
	x = 0;
	n = n * n;
	postcondition(n < 10000);
	postcondition(n != 1, "n shouldn't be one at this point");
	postcondition(n != 25, "n shouldn't be one at this point");
	postcondition(x == 0);
	return n;
}

// Tries to return (n+1) squared, but fails
int brokenFunction(int n) {
	n++;
	if (n == 3)
		return n * n;
	return n * n + 1;
}

void runNumberTests() {
	test(5 == 8, "Testing if numbers work");
	test(2 == 2, "You won't see this");
}

void runWorkingTests() {
	test(workingFunction(7) == 64);
	test(workingFunction(1) == 4, "Shouldn't see this");
	test(workingFunction(-7) == 36);
	test(workingFunction(2) == 49, 
		"Remember, your condition could be wrong...");
}

void runBrokenTests() {
	test(brokenFunction(7) == 64);
	test(brokenFunction(1) == 4, "Should see this");
	test(brokenFunction(-7) == 36);
	test(brokenFunction(2) == 9, 
		"...or your function may not be broken in all cases");
}

void runOtherTests() {
	int badPre = -20000, goodPre = 8, badPost = 4, goodPost = 7;
	
	// A pre/post check
	std::cout << workingFunction(goodPost) << std::endl;
	workingFunction(badPost);

	std::cout << "Yay, no errors!" << std::endl;
}

int main() {

#ifndef NDEBUG
	runNumberTests();
	runWorkingTests();
	runBrokenTests();
	runOtherTests();
#endif

	cout << "Non debugging code" << endl;
}