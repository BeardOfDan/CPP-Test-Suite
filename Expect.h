
#include <string>
using std::string;
using std::to_string;

// TODO: Create an internal variable (vector?) to hold a record of the tests
// and the input to those tests for the final report Ex.
// instance(17).greaterThan(5).lessThan(33) would generate:
//   passed: Expected 17 to be greater than 5 but less than 33
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

    return comparisonBody(comparison, actual, testValue, customFailureReport);
  }

  Expect& lessThan(inputType testValue,
                   std::function<bool(inputType, inputType)> comparison =
                       [](inputType actual, inputType testValue) {
                         return (actual < testValue);
                       },
                   string customFailureReport = "") {
    customFailureReport = (customFailureReport.length() > 0)
                              ? customFailureReport
                              : "Expected " + to_string(actual) +
                                    " to be less than " + to_string(testValue);

    return comparisonBody(comparison, actual, testValue, customFailureReport);
  }

  Expect& equalTo(inputType testValue,
                  std::function<bool(inputType, inputType)> comparison =
                      [](inputType actual, inputType testValue) {
                        return (actual == testValue);
                      },
                  string customFailureReport = "") {
    customFailureReport = (customFailureReport.length() > 0)
                              ? customFailureReport
                              : "Expected " + to_string(actual) +
                                    " to be equal to " + to_string(testValue);

    return comparisonBody(comparison, actual, testValue, customFailureReport);
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
    return thisFailed();
  }

  // return the variable that gets tested
  // it is the actual value, because it might not be the expected one
  //   ex. It could be the output of a function with certain args
  inputType getActual() { return actual; }

  bool passed() { return !failed; }

  // TODO: Refactor name to report string,
  // it will more accurately describe what it will do
  string testStatus(bool verbose = true, bool prefaced = true) {
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
  operator string() { return testStatus(); }

 private:
  // These methods are private because they are internal methods
  Expect& thisFailed() {
    failed = true;
    return getThis();
  }

  Expect& comparisonBody(std::function<bool(inputType, inputType)> comparison,
                         inputType actual, inputType testValue,
                         string customFailureReport) {
    if (failed) {
      skippedTests++;
      return getThis();  // don't run further tests
    }

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
