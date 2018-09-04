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

#include "enumeratedTestType.h"

// TODO: Create adjustable comparisons
//   Ex. compound data-types with equal values and regular framework methods
//   (greater/less than, not null, exists, etc.)

template <typename outputFormat>
class testInstance {
 public:
  template <typename Func,
            typename tup>  // TODO: Update type from string to Enum
  testInstance(Func functionToTest, tup arguments, outputFormat eo,
               enumeratedTestType ett = consoleStr)
      : expectedOutput{eo}, testType{ett} {
    // validate type, throw error if invalid,
    // might not need to do anymore, after is refactored to enum

    // use type to discern which method to use to run test
    // and what data to store
    switch (testType) {
      case consoleStr:
        testCout(functionToTest, arguments);
        break;

        // case returnVal:
        //   testReturn(functionToTest, arguments);
        //   break;

        // default:
        // throw error
    }

    // execute test
    // redirectOutput output;
    // apply(functionToTest, arguments);

    // // actualOutput = output.getContents();
    // capturedOutput = output.getContents();
  }

  ~testInstance() {}

  // The 'test...' methods execute the test and populate class data
  // they do not return anything

  template <typename Func, typename tup>
  void testCout(Func functionToTest, tup arguments) {
    redirectOutput output;
    apply(functionToTest, arguments);
    capturedOutput = output.getContents();
  }

  // template <typename Func, typename tup>
  // void testReturn(Func functionToTest, tup arguments) {
  //   if (typeid(functionToTest) != 'void')
  //     actualOutput = apply(functionToTest, arguments);
  // }

  bool passed() {
    switch (testType) {
      case consoleStr:
        return expectedOutput == capturedOutput;
        break;

        // case returnVal:
        //   return expectedOutput == actualOutput;
        //   break;

        // default:
        // throw error
    }
  }

  outputFormat expectedOutput;
  outputFormat actualOutput;
  string capturedOutput;
  enumeratedTestType testType;

 private:
};
