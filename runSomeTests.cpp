/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Testing for test.h (It's turtles all the way down)                  *
 * Note: You do NOT need this file to use vitest. test.h contains all  *
 *  the implementation of the macros and functions                     *
 * The output is somewhat messy looking but it should be enough to fix *
 *  all the bugs in the program and learn how everything works.        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "test.h"
#include <iostream>

using namespace vitest;

// Returns (n+1) squared
int workingFunction(int n) {
	precondition(n < 10000, "Is n reasonably small?");
	precondition(n != 0, "n should be nonzero");
	precondition(n > -10000);
	n++;
	int x = 0;
	n = n * n;
	postcondition(n < 10000);
	postcondition(n != 1, "n shouldn't be one at this point");
	postcondition(n != 25, "n shouldn't be one at this point");
	postcondition(x == 0);
	return n;
}
unittest(
	test(workingFunction(5) == 36, "(5 + 1) ^ 2 is 36");
	test(workingFunction(6) == 49, "(6 + 1) ^ 2 is 49");
	test(workingFunction(-11) == 100, "(-11 + 1) ^ 2 is 100");
	test(workingFunction(-11) == 89, "10 ^ 2 == 89");
)

// Tries to return (n+1) squared, but fails
int brokenFunction(int n) {
	n++;
	if (n == 3)
		return n * n;
	return n * n + 1;
}
unittest(
	cout << "unittest 2\n";
)

void runNumberTests() {
	test(5 == 8, "Testing if numbers work");
	test(2 == 2, "You won't see this");
}

// Testing since unittest should run in random order--it does
unittest(
	cout << "unittest 3\n";
)
unittest(
	cout << "unittest 4\n";
)
unittest(
	cout << "unittest 5\n";
)
unittest(
	cout << "unittest 6\n";
)

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

void hereTest() {
	int x = 3;
	here();
	x--;
	x--;
	cout << "liftoff\n";
}

void messageTest() {
	int y = 100, k = 10;
	message("things are going well");
	y * 2 * k; // y2k == 2000
}

int main() {
	runUnitTests();

	hereTest();
	messageTest();

#ifndef NDEBUG
	runNumberTests();
	runWorkingTests();
	runBrokenTests();
	runOtherTests();
#endif

	cout << "Non debugging code" << endl;
}
