// Initially from scratch.cpp
//   A 'scratch' cpp file for me to mess around in

#include <iostream>
using std::cout;
using std::endl;

#include <sstream>
using std::ostream;

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::to_string;

#include <array>
using std::size;

#include "generalLibrary.h"

// arg part of function signature for lambda arg
// std::function<returnType (arg1Type, arg2Type, ...)> lambdaName

// TEST instanceRunning wrapper
// accept a vector (of tuples?) of everything
// vector failureDataStruct
// for(int i{}; i < vector<everything>.size(); i++) {
//   bool passed = false;
//   ... exec test and put pass/fail value into passed
//         use this file's class (currently named Expect
// ) to exec tests
//         ex. Expect
//  test{args here};
//             const passed = test.meth1().meth2.meth3()... .passed();
//   if (passed) {
//     // do little here... move onto next test...
//   } else {
//     auto fds = new failureDataStruct(iteration=i,
//     arguments=vector<everything>[i].args, expectedOutput, actualOutput);
//     // should probably have Expect
// class use a method to return fds as a value
//     // then can just push that method's return onto vector of fds's
//     failureDataStruct.push_back(fds);
//   }
// }
// cout << vector<everything>.size() - vector<failureDataStruct>.size() << "
// of " << vector<everything>.size() tests passed! << endl; for(let i = 0; i
// < vector<failureDataStruct>.size(); i++) {
//   failureDataStruct[i].generateReport(); // cout's a report of the
//   failure
// }

// TODO: Create an internal variable (vector?) to hold a record of the tests
// and the input to those tests for the final report Ex.
// instance(17).greaterThan(5).lessThan(33) would generate:
//   passed: Expected 17 to be greater than 5 but less than 33
// This would, presumably, have implications for the default and
// custom failureReport, along with passedStr()
template <typename inputType>
class Expect {
 public:
  Expect(inputType input, string d, bool f = false,
         string fr = "Default failure report")
      : actual{input}, description{d}, failed{f}, failureReport{fr} {
    if (failed) {
      failureReport = "Created as failed test through constructor argument";
    }
  }

  ~Expect() {}

  Expect& getFailed() {
    failed = true;
    return getThis();
  }

  // Returns this class (to enable method chaining)
  Expect& getThis() { return *this; }

  Expect& greaterThan(inputType test,
                      std::function<bool(int, int)> comparison =
                          [](int actual, int test) { return (actual > test); },
                      string customFailureReport = "") {
    customFailureReport = (customFailureReport.length() > 0)
                              ? customFailureReport
                              : "Expected " + to_string(actual) +
                                    " to be greater than " + to_string(test);

    return comparisonBody(comparison, actual, test, customFailureReport);
  }

  Expect& lessThan(inputType test,
                   std::function<bool(int, int)> comparison =
                       [](int actual, int test) { return (actual < test); },
                   string customFailureReport = "") {
    customFailureReport = (customFailureReport.length() > 0)
                              ? customFailureReport
                              : "Expected " + to_string(actual) +
                                    " to be less than " + to_string(test);

    return comparisonBody(comparison, actual, test, customFailureReport);
  }

  Expect& equalTo(inputType test,
                  std::function<bool(int, int)> comparison =
                      [](int actual, int test) { return (actual == test); },
                  string customFailureReport = "") {
    customFailureReport = (customFailureReport.length() > 0)
                              ? customFailureReport
                              : "Expected " + to_string(actual) +
                                    " to be equal to " + to_string(test);

    return comparisonBody(comparison, actual, test, customFailureReport);
  }

  // TODO: Create a toHaveFailed and/or toBeFalse method
  // This will allow for anticipation of falure of certain tests
  // as a test itself, obviously, care should be used when
  // employing such a method
  Expect& toHaveFailed(string customFailureReport = "") {
    customFailureReport = (customFailureReport.length() > 0)
                              ? customFailureReport
                              : "Expected a failure prior to this point";

    if (failed) {
      failed = false;  // failure was passing, so failure is now false
      return getThis();
    }

    failureReport = customFailureReport;
    return getFailed();
  }

  // return the variable that gets tested
  // it is the actual value, because it might not be the expected one
  //   ex. It could be the output of a function with certain args
  inputType getActual() { return actual; }

  bool passed() { return !failed; }

  // TODO: Refactor name to report string,
  // it will more accurately describe what it will do
  string passedStr(bool verbose = true, bool prefaced = true) {
    if (verbose) {
      if (prefaced) {
        return passed()
                   ? ("passed: \"Expect " + to_string(actual) + " " +
                      description + "\"")
                   : ("failed: \"Expect " + to_string(actual) + " " +
                      description + "\"\n  " + failureReport + "\n  skipped " +
                      to_string(skippedTests) + " tests.");
      }
      return passed() ? ("passed: \"" + description + "\"")
                      : ("failed: \"" + description + "\"\n  " + failureReport +
                         "\n  skipped " + to_string(skippedTests) + " tests.");
    }
    return passed() ? "passed" : "failed";
  }

  // Type overloads
  operator int() { return (passed() ? 1 : 0); }
  operator bool() { return passed(); }
  operator string() { return passedStr(); }

 private:
  // This is private because it is an internal method
  Expect& comparisonBody(std::function<bool(int, int)> comparison,
                         inputType actual, inputType test,
                         string customFailureReport) {
    if (failed) {
      skippedTests++;
      return getThis();  // don't run further tests
    }

    if (comparison(actual, test)) {
      return getThis();  // continue chain
    } else {             // failed the test
      failureReport = customFailureReport;
      return getFailed();
    }
  }

  const inputType actual;  // the actual value, to be used for testing

  // No longer const, because it's private and may need to be internally altered
  string description;  // describes the test being performed

  bool failed;  // Initially false, but a failed test turns it true

  string failureReport;

  int skippedTests = 0;
  int testsPerformed = 0;  // TODO: Update the code to update this variable
};                         // End of class Expect

int main() {
  cout << endl;  // formatting

  Expect f{7, "not to be greater than all numbers in an array"};

  auto a = f;

  auto b = Expect(a.getActual(), "to be greater than -3");

  int vals[]{-1, 0, 1, 2, 3, 4, 5, 6, 9};

  cout << "a: "
       << (string)(a.greaterThan(
                        vals[0],  // a dummy var to comply with type in function
                        // lambda for custom comparison
                        [vals](int actual, int testArg) -> bool {
                          // size() is a function from #include <array>
                          // int size is a local variable
                          const int size = std::size(vals);

                          for (size_t i{}; i < size; i++) {
                            if (actual <= vals[i]) {
                              return false;
                            }
                          }
                          return true;
                        },  // end of lambda
                        // Expression resolves to custom failure report argument
                        "expected " + to_string(a.getActual()) +
                            " to be greater than all of the values in "
                            "the array " +
                            arrToString(vals, size(vals)))
                       .toHaveFailed("The array included the number 9, but the "
                                     "expect was given a value of 7"))
       << endl;

  cout << "b: "
       << (b.greaterThan(-3, [](int a, int b) -> bool { return (a > b); })
               .passedStr())
       << endl;

  auto alpha = []() {
    Expect c{9, "Expect to 'fail' due to constructor argument", true};
    cout << "c: " << c.toHaveFailed().passedStr(true, false) << endl;
  };

  []() {
    Expect d{9, "to be less than a given number"};
    cout << "d: " << d.lessThan(11).passedStr() << endl;
  }();

  alpha();  // the lambda for test 'c'

  const int answerToEverything = 42;

  Expect e{42, "to be the answer to everything"};
  cout << "e: " << (string)e.equalTo(answerToEverything) << endl;

  Expect g{3.14, "Expect to be able to also use type double"};
  cout << "g: " << (string)g.equalTo(g.getActual()).passedStr(true, false)
       << endl;

  cout << endl;  // formatting

  return 0;
}
