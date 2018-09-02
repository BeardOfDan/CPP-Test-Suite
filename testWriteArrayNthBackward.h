
#include "testInstance.h"
// base class to extend

#include "writeArrayNthBackward.h"
// file with function (of same name) to test

#include "coutRedirect.h"
// contains redirectOutput

#include <tuple>
using std::get;
using std::tuple;

// string is included by the base class

class testWriteArrayNthBackward : public testInstance {
 public:
  //                       (string,    tuple<const char *, int, int, int>)
  testWriteArrayNthBackward(string eo, tuple<const char *, int, int, int> args)
      : arguments{args} {}

  ~testWriteArrayNthBackward() {}

  bool execTest() {  // returns bool of if it passed
    redirectOutput output;

    // execute function here
    writeArrayNthBackward(get<0>(arguments), get<1>(arguments),
                          get<2>(arguments), get<3>(arguments));

    actualOutput = output.getContents();

    return expectedOutput.compare(actualOutput);
  }

  tuple<const char *, int, int, int> arguments;

 private:
};
