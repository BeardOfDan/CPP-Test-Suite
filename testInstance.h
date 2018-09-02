
#include <string>
using std::string;

#include "coutRedirect.h"
// contains redirectOutput

#include <tuple>
using std::apply;
using std::get;
using std::tuple;

class testInstance {
 public:
  template <typename Func, typename tup>
  testInstance(Func f, tup t, string eo) : expectedOutput{eo} {
    Func functionToTest{f};
    tup arguments{t};

    // execute test
    redirectOutput output;
    apply(functionToTest, arguments);
    actualOutput = output.getContents();
  }

  ~testInstance() {}

  bool passed() { return expectedOutput.compare(actualOutput); }

  string expectedOutput;
  string actualOutput;

 private:
};
