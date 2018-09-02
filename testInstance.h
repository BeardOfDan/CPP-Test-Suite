
#include <string>
using std::string;

#include "redirectOutput.h"
// contains redirectOutput

#include <tuple>
using std::apply;
using std::get;
using std::tuple;

// TODO: Either pass an optional variable to constructor to handle flow control,
// and implement here, or extend this class to create a testInstance that allows
// for a particular test function to be used (since not all functions to test
// will automatically pipe their result to cout)

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
     // (affects cout's flow)

  ~testInstance() {}

  bool passed() { return expectedOutput.compare(actualOutput); }

  string expectedOutput;
  string actualOutput;

 private:
};
