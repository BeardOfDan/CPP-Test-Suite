#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <tuple>
using std::make_tuple;
using std::tuple;

#include "testWriteArrayNthBackward.h"

int main() {  // TODO: create test runner class to automate a bunch of this
  vector<tuple<const char*, int, int, int>> args;

  vector<string> expectedOutputs;
  vector<string> actualOutputs;

  int pass{};

  const char* inputs[4]{"abc123", "hello", "hello", "c1c1c1"};

  // TODO: Refactor args to be filled from a file or something more efficient
  args.push_back(make_tuple(inputs[0], 0, 6, 2));
  expectedOutputs.push_back("2ca");

  args.push_back(make_tuple(inputs[1], 0, 5, 1));
  expectedOutputs.push_back("olleh");

  args.push_back(make_tuple(inputs[2], 0, 5, 3));
  expectedOutputs.push_back("l");

  args.push_back(make_tuple(inputs[3], 0, 6, 2));
  expectedOutputs.push_back("ccc");

  for (size_t i{}; i < args.size(); i++) {
    testWriteArrayNthBackward test{expectedOutputs[i], args[i]};

    pass += test.execTest() ? 1 : 0;

    actualOutputs.push_back(test.actualOutput);
  }

  // TODO: Remove manual comparison (and actualOutputs vector),
  //        as they are now unnecessary (the bug was fixed)
  for (size_t i{}; i < args.size(); i++) {
    cout << "ExpectedOutputs[" << i << "]: | " << expectedOutputs[i] << endl;
    cout << "---------------------" << endl;
    cout << "ActualOutputs[" << i << "]:   | " << actualOutputs[i] << endl;

    cout << endl << "==================" << endl;
  }

  cout << endl << "=======" << endl;
  cout << "Of " << args.size() << " tests, " << pass << " passed." << endl;

  return 0;
}
