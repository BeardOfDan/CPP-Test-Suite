
#include <tuple>
using std::tuple;

#include <string>
using std::string;

// A base class to be extended for each type of test
class testInstances {
  // The extended class will add a particular tuple for the arguments
  testInstances(void (*func)(), string eo)
      : functionToTest{func}, expectedOutput{eo} {}

  ~testInstances() {}

  // This method will be defined in the extended class
  // void execTest() {
  //   // use coutRedirect
  //   // functionToTest(destructured tuple of arguments)
  //   // set actualOutput
  //   // if needed, add vector of output lines (to expanded class)
  //   //   would possibly need to override passed method if using this
  // } // end of scope executes coutRedirect's destructor

  // lookup inline functions, this should probably be one...
  bool passed() { return expectedOutput == actualOutput; }

  // comparison method for line by line difference
  // (use coutRedirect.getVectors())
  //   would need to implement the delimiter function on expectedOutput
  //   probably means would want to refactor it to a seperate .h file

  void (*functionToTest)();
  string expectedOutput;
  string actualOutput;

 private:
};
