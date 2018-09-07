// C++ Test Suite
// Programmer: Daniel Roberts
// Compiler(s) used: g++ -std=c++17 -Wall

#include <string>
using std::string;
using std::to_string;

#include "generalLibrary.h"
// toString

#include <iostream>
using std::cout;
using std::endl;

// Color Codes, for the console
// TEXT COLOR
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"
// BACKGROUND COLOR
// TODO: Add background color codes

// TODO: Create an internal variable (vector?) to hold a record of the tests
// and the input to those tests for the final report Ex.
// instance(17).greaterThan(5).lessThan(33) would generate:
//   passed: Expected 17 to be greater than 5 and less than 33
// This would, presumably, have implications for the default and
// custom failureReport, along with testStatus()
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

  // Returns this class (to enable method chaining)
  Expect& getThis() { return *this; }

  Expect& greaterThan(inputType testValue,
                      std::function<bool(int, int)> comparison =
                          [](int actual, int testValue) {
                            return (actual > testValue);
                          },
                      string customFailureReport = "") {
    customFailureReport = (customFailureReport.length() > 0)
                              ? customFailureReport
                              : "Expected " + to_string(actual) +
                                    " to be greater than " +
                                    to_string(testValue);

    return comparisonBody(actual, comparison, testValue, customFailureReport);
  }

  Expect& lessThan(inputType testValue,
                   std::function<bool(inputType, inputType)> comparison =
                       [](inputType actual, inputType testValue) {
                         return (actual < testValue);
                       },
                   string customFailureReport = "") {
    customFailureReport = (customFailureReport.length() > 0)
                              ? customFailureReport
                              : "Expected " + toString(actual) +
                                    " to be less than " + toString(testValue);

    return comparisonBody(actual, comparison, testValue, customFailureReport);
  }

  Expect& equalTo(inputType testValue,
                  std::function<bool(inputType, inputType)> comparison =
                      [](inputType actual, inputType testValue) {
                        return (actual == testValue);
                      },
                  string customFailureReport = "") {
    customFailureReport = (customFailureReport.length() > 0)
                              ? customFailureReport
                              : "Expected " + toString(actual) +
                                    " to be equal to " + toString(testValue);

    return comparisonBody(actual, comparison, testValue, customFailureReport);
  }

  Expect& toHaveFailed(string customFailureReport = "") {
    customFailureReport = (customFailureReport.length() > 0)
                              ? customFailureReport
                              : "Expected a failure prior to this point";

    if (failed) {
      failed = false;  // failure was passing, so failure is now false
      return getThis();
    }

    failureReport = customFailureReport;
    return thisFailed();  // it it 'passed' it failed
  }

  // return the variable that gets tested
  // it is the actual value, because it might not be the expected one
  //   ex. It could be the output of a function with certain args
  inputType getActual() { return actual; }

  bool passed() { return !failed; }

  // TODO: Refactor name to report string,
  // it will more accurately describe what it will do
  // TODO: Refactor below to reduce repeated code
  // TODO: Have report be function of inputType
  //   ex. if string, then put actual in quotes -> "\"" + actual + "\""
  string testStatus(bool verbose = true, bool prefaced = true) {
    if (verbose) {
      if (prefaced) {
        return passed()
                   ? ("passed: Expect " + toString(actual) + " " + description)
                   : ("failed: Expect " + toString(actual) + " " + description +
                      "\n  " + failureReport + "\n  skipped " +
                      toString(skippedTests) + " tests.");
      }
      return passed() ? ("passed: " + description)
                      : ("failed: " + description + "\n  " + failureReport +
                         "\n  skipped " + toString(skippedTests) + " tests.");
    }
    return passed() ? "passed" : "failed";
  }

  void writeTestStatus(bool verbose = true, bool prefaced = true) {
    if (prefaced) {
      if (passed()) {
        cout << GREEN << "passed" << RESET
             << (": Expect " + toString(actual) + " " + description) << endl;
      } else {  // Failed
        cout << RED << "failed" << RESET
             << (": Expect " + toString(actual) + " " + description + "\n  " +
                 failureReport + "\n  skipped " + toString(skippedTests) +
                 " tests.")
             << endl;
      }
    } else {  // not prefaced
      if (passed()) {
        cout << GREEN << "passed" << RESET << ": " << description << endl;
      } else {  // failed
        cout << RED << "failed" << RESET
             << (": " + description + "\n  " + failureReport + "\n  skipped " +
                 toString(skippedTests) + " tests.")
             << endl;
      }
    }
  }

  // Type overloads
  operator int() { return (passed() ? 1 : 0); }
  operator bool() { return passed(); }
  operator string() { return testStatus(); }

 private:
  // These methods are private because they are internal methods
  Expect& thisFailed() {
    failed = true;
    return getThis();
  }

  Expect& comparisonBody(inputType actual,
                         std::function<bool(inputType, inputType)> comparison,
                         inputType testValue, string customFailureReport) {
    if (failed) {
      skippedTests++;
      return getThis();  // don't run further tests
    }

    // TODO: add a try/catch block to capture the return of comparison
    // This way, if the user supplied comparison does something wierd,
    // the testing can still continue
    if (comparison(actual, testValue)) {
      return getThis();  // continue chain
    } else {             // failed the test
      failureReport = customFailureReport;
      return thisFailed();
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
