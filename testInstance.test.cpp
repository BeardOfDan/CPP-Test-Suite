// Lab 1, Write Array Nth Backward
// Programmer: Daniel Roberts
// Editor(s) used: VS Code
// Compiler(s) used: g++ -std=c++17 -Wall

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <tuple>
using std::make_tuple;
using std::tuple;

#include <vector>
using std::vector;

#include "testInstance.h"

#include "writeArrayNthBackward.h"
// function (of same name) to test

int main() {
  // TODO: accept an argument to main that would stop the 'Basic program info'
  // from printing to the screen
  cout << endl;  // Basic program info
  cout << "Lab 1, Write Array Nth Backwards" << endl;
  cout << "Programmer: Daniel Roberts" << endl;
  cout << "Editor(s) used: VS Code" << endl;
  cout << "Compiler(s) used: g++ -std=c++17 -Wall" << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl << endl;

  const int TEST_COUNT = 4;

  int passed{};  // number of tests passed

  // TODO: Refactor args to be filled from a file or something more efficient
  const char* inputs[TEST_COUNT]{"abc123", "hello", "hello", "c1c1c1"};
  const char* expectedOutputs[TEST_COUNT]{"2ca", "olleh", "l", "ccc"};
  const int nVals[TEST_COUNT]{2, 1, 3, 2};

  vector<tuple<const char*, int, int, int> > args;

  for (size_t i {} i < TEST_COUNT; i++) {  // populate args vector
    args.push_back(make_tuple(inputs[i], 0, strlen(inputs[i]), nVals[i]));
  }

  for (size_t i{}; i < TEST_COUNT; i++) {  // execute tests
    testInstance test{writeArrayNthBackward, args[i], expectedOutputs[i]};

    passed += test.passed() ? 1 : 0;
  }

  // TODO: Expand on the printout of the results
  //         (ex. percentage passed, specific info on failed tests, etc.)
  // TODO: Utilize color change and formatting to improve
  //       the visibility of the test results ... and make it look cooler
  //   Note: All implementations are platform dependent, so will have to
  //         make a version for Bash and another for DOS then make some sort
  //         of system call to determine which one to use at runtime
  cout << passed << " of " << TEST_COUNT << " tests passed!" << endl << endl;

  return 0;
}
