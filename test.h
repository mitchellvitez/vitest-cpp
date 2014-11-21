/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * DESCRIPTION:                                                        *
 *  Building on assert() in ~100 lines of macros.                      *
 *                                                                     *
 * AUTHOR:                                                             *
 *  By Mitchell Vitez. Feel free to reuse and modify with attribution. *
 *  Originally built for testing coding projects at umich.             *
 *  Nov 20 2014 | mvitez@umich.edu | www.vitez.me                      *
 *                                                                     *
 * USAGE: use precondition() at the very beginning of a function to    *
 *  check whether your assumptions are correct.                        *
 *  Likewise with postcondition(), except used right before returning  *
 *  at the end of a function.                                          *
 *                                                                     *
 *  test() does not exit the program. This is to encourage test-       *
 *  driven development without inducing frustration.                   *
 *                                                                     *
 *  Unlike with assert(), it is possible to pass an optional message   *
 *  along with your conditional so reading output you know exactly     *
 *  what you were trying to accomplish                                 *
 *                                                                     *
 *  unittest() lets you put several test() statements inside it. These *
 *  will be run in a randomized order as the first thing in your       *
 *  program if you call runUnitTests(); as the first line in main.     *
 *  They are useful for separating testing out from running code, as   *
 *  the unittest() macro doesn't need to be inside a function          *
 *                                                                     *
 *  unittest() can take arbitrary statements as well, if you need to   *
 *  set up tests (constructors, etc.)                                  *
 *                                                                     *
 *	message(string msg) outputs a message unconditionally              *
 *                                                                     *
 *  here() outputs if the program gets to a certain point, since I     *
 *  used to write a lot of cout << "function name got to here";        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <iostream>
#include <stdlib.h> 
#include <string>

using namespace std;

#ifndef TEST_H
#define TEST_H

/////// Above this line doesn't need functional, algorithm, vector ///////

#include <vector>
#include <functional>
#include <algorithm>

namespace vitest {

#define concat(a, b) a##b
#define concatenate(a, b) concat(a, b)
#define unittest( ... )  static int concatenate(unittest, __LINE__) = \
	addUnitTest([](){ __VA_ARGS__ }); 

vector<function<void()>> unitTests;

int addUnitTest(function<void()> func) {
	#ifndef NDEBUG
		unitTests.push_back(func);
		return 1;
	#endif
}

void runUnitTests() {
	#ifndef NDEBUG
		// Random seed, to help run unit tests in random order
		srand(unsigned(time(NULL)));
		// Ensures they are independent unit tests
		random_shuffle(unitTests.begin(), unitTests.end());
		for (auto unitTest = unitTests.begin(); 
				unitTest != unitTests.end(); unitTest++)
			(*unitTest)();
	#endif
}

} // namespace vitest

/////// Below this line doesn't need functional, algorithm, vector ///////
namespace vitest {

#define PRECONDITION "Precondition"
#define POSTCONDITION "Postcondition"
#define TEST "Test"
#define EXIT 1
#define NO_EXIT 0

/* Note: if __PRETTY_FUNCTION__ doesn't work for you, try __FUNCTION__ 
	or __func__ 
   Exiting is separate from pre/post/test types because while I like 
	pre and post to exit, and test to not, your preferences may differ */
#ifdef NDEBUG
# define precondition( ... )
# define postcondition( ... )
# define test( ... )
#else
# define precondition( condition, ... ) { if( ! (condition)) \
	conditionTest(#condition, ##__VA_ARGS__, __FILE__, __LINE__, \
	 __PRETTY_FUNCTION__, PRECONDITION, EXIT); }
# define postcondition( condition, ... ) { if( ! (condition)) \
	conditionTest(#condition, ##__VA_ARGS__, __FILE__, __LINE__, \
		__PRETTY_FUNCTION__, POSTCONDITION, EXIT); }
# define test( condition, ... ) { if( ! (condition)) \
	conditionTest(#condition, ##__VA_ARGS__, __FILE__, __LINE__, \
	__PRETTY_FUNCTION__, TEST, NO_EXIT/* By Sartre */); }
#endif

// Prints to cerr in assert()-like style if assert() would print
void conditionTest(string condition, string message, string file, 
		int line, string function, string type, bool shouldExit) {
	// Ignores the message if it's an empty string
	if (message.size() > 0) {
		message = " Message: `" + message + "'";
	}
	cerr << file << ":" << line << ": " << function << ": " << 
		type << " `" << condition << "' failed." << message << "\n";
	if (shouldExit)
		exit(EXIT_FAILURE);
}

// Print without a message specified
void conditionTest(string condition, string file, int line, 
		string function, string type, bool shouldExit) {
	conditionTest(condition, "", file, line, function, type, shouldExit);
}

#ifdef NDEBUG
# define message( ... )
# define here( ... )
#else
# define message( msg ) printMessage(msg, __FILE__, __LINE__, __PRETTY_FUNCTION__)
# define here( ) printHere(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#endif

void printMessage(string message, string file, int line, string function) {
	cerr << file << ":" << line << ": " << function << ": Message: " 
		<< message << "\n";
}

void printHere(string file, int line, string function) {
	cerr << file << ":" << line << ": " << function << ": here\n";
}
}

#endif