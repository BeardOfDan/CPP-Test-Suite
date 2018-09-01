
#include <tuple>
using std::tuple;

#include <string>
using std::string;

// A base class to be extended for each type of test
class testInstances {
 public:
  // The extended class will add a particular tuple for the arguments
  testInstances(void (*func)(int), string eo)
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
  void execTest() {
    functionToTest(1);
  }  // using a basic version for initial testing

  // lookup inline functions, this should probably be one...
  bool passed() { return expectedOutput == actualOutput; }

  // comparison method for line by line difference
  // (use coutRedirect.getVectors())
  //   would need to implement the delimiter function on expectedOutput
  //   probably means would want to refactor it to a seperate .h file

  void (*functionToTest)(int);
  string expectedOutput;
  string actualOutput;

 private:
};
