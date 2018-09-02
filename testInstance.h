// C++ Test Suite
// Programmer: Daniel Roberts
// Compiler(s) used: g++ -std=c++17 -Wall

#include <string>
using std::string;

#include "redirectOutput.h"

#include <tuple>
using std::apply;
using std::get;
using std::tuple;

// TODO: Either pass an optional variable to constructor to handle flow control,
// and implement here, or extend this class to create a testInstance that allows
// for a particular test function to be used (since not all functions to test
// will automatically pipe their result to cout)
// ---- Possible implementation: create a generic function that simply executes
// functionToTest(arguments) in the same way it currently is. This function will
// be the default value for an additional constructor argument that allows a
// tester to define particular implementations of their tests.

template <typename Func, typename tup>
string defaultFunc(Func f, tup t) {
  redirectOutput output;

  apply(f, t);

  return output.getContents();
}

// possible constructor arg format
// , Func defFunc = defaultFunc

class testInstance {
 public:
  template <typename Func, typename tup>
  testInstance(Func f, tup t, string eo) : expectedOutput{eo} {
    // Initializing inside the braces to avoid 'undefined' errors
    // and issues resulting from use of template
    Func functionToTest{f};
    tup arguments{t};

    // execute test
    redirectOutput output;
    apply(functionToTest, arguments);
    actualOutput = output.getContents();
  }  // Note: the destructor for redirectOutput is called here
     // (restores cout's usual flow)

  ~testInstance() {}

  bool passed() { return expectedOutput == actualOutput; }

  string expectedOutput;
  string actualOutput;

 private:
};
