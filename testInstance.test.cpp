#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <tuple>
using std::make_tuple;

#include "testInstance.h"

#include "writeArrayNthBackward.h"
// function (of same name) to test

int main() {
  cout << endl;  // Basic program info
  cout << "Lab 1, Write Array Nth Backwards" << endl;
  cout << "Programmer: Daniel Roberts" << endl;
  cout << "Editor(s) used: VS Code" << endl;
  cout << "Compiler(s) used: g++ -std=c++17 -Wall" << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl << endl;

  vector<tuple<const char*, int, int, int>> args;
  vector<string> expectedOutputs;

  int passed{};

  // TODO: Define the number of tests at the beginning of the program
  //         to remove any 'magic numbers'

  // TODO: Refactor args to be filled from a file or something more efficient
  const char* inputs[4]{"abc123", "hello", "hello", "c1c1c1"};

  args.push_back(make_tuple(inputs[0], 0, 6, 2));
  expectedOutputs.push_back("2ca");

  args.push_back(make_tuple(inputs[1], 0, 5, 1));
  expectedOutputs.push_back("olleh");

  args.push_back(make_tuple(inputs[2], 0, 5, 3));
  expectedOutputs.push_back("l");

  args.push_back(make_tuple(inputs[3], 0, 6, 2));
  expectedOutputs.push_back("ccc");

  for (size_t i{}; i < args.size(); i++) {
    testInstance test{writeArrayNthBackward, args[i], expectedOutputs[i]};

    passed += test.passed() ? 1 : 0;
  }

  // TODO: Expand on the printout of the results
  //         (ex. percentage passed, specific info on failed tests, etc.)
  // TODO: Utilize color change and formatting to improve
  //       the visibility of the test results ... and make it look cooler
  cout << passed << " of " << args.size() << " tests passed!" << endl;

  return 0;
}
