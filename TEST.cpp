// Initially from scratch.cpp
//   A 'scratch' cpp file for me to mess around in

// NOTE: This is currently an idea in a VERY raw form.
// The goal is to create something like the 'expect' library (for JS)

// NOTE/QUESTION: What happens if you define a pointer to an empty lambda
// in a class, then return the pointer (through a method), then define the
// lambda in that (the caller's) scope, then go back in the class and execute
// that lambda?
// Ex. compiler error? awesome functionality? etc.

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
    return getMe();
  }

  // Returns this class (to enable method chaining)
  Expect& getMe() { return *this; }

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
      return getMe();
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
      return getMe();  // don't run further tests
    }

    if (comparison(actual, test)) {
      return getMe();  // continue chain
    } else {           // failed the test
      failureReport = customFailureReport;
      return getFailed();
    }
  }

  const inputType actual;  // the actual value, to be used for testing

  const string description;  // describes the test being performed

  bool failed;  // Initially false, but a failed test turns it true

  string failureReport;

  int skippedTests = 0;
  int testsPerformed = 0;  // TODO: Update the code to update this variable
};

int main() {
  cout << endl;  // formatting

  Expect f{7, "to be greater than all numbers in an array"};

  auto a = f;

  auto b = Expect(a.getActual(), "to be greater than -3");

  int vals[]{1, 2, 3, 4, 5, 6};

  cout << "a: "
       << (string)(a.greaterThan(
              vals[0],  // a dummy var to comply with type in function signature
              // lambda for custom comparison
              [vals](int a, int b) -> bool {
                const int size = (sizeof(vals) / sizeof(vals[0]));

                for (size_t i{}; i < size; i++) {
                  if (a <= vals[i]) {
                    return false;
                  }
                }
                return true;
              },  // end of lambda
              // Expression resolves to custom failure report argument
              "expected " + to_string(a.getActual()) +
                  " to be greater than all of the values in "
                  "the array " +
                  [vals]() -> string {
                string s = "[ ";
                const int size = (sizeof(vals) / sizeof(vals[0]));
                for (size_t i{}; i < size; i++) {
                  s += to_string(vals[i]) + ((i + 1 < size) ? ", " : " ");
                }
                return (s + "]");
              }()  // end of custom failure report argument expression
              ))
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
    cout << "d: " << d.lessThan(11).passedStr() << endl;  // test
  }();

  alpha();  // the lambda for 'c'

  cout << endl;  // formatting

  return 0;
}
