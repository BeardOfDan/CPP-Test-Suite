// C++ Test Suite
// Programmer: Daniel Roberts
// Compiler(s) used: g++ -std=c++17 -Wall

// TODO: Implement the thing (macro?) that decides not to define previously
// defined things, as this is intended to be an included file.
// Do the same for redirectOutput.h

#include <string>
using std::string;

#include "redirectOutput.h"

#include <tuple>
using std::apply;
using std::get;
using std::tuple;

template <typename Func, typename tup>
string defaultFunc(Func f, tup t) {
  redirectOutput output;

  apply(f, t);

  return output.getContents();
}

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
