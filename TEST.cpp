// Initially from scratch.cpp
//   A 'scratch' cpp file for me to mess around in

// NOTE: This is currently an idea in a VERY raw form.
// The goal is to create something like the 'expect' library (for JS)

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
//         use this file's class (currently named Foo) to exec tests
//         ex. Foo test{args here};
//             const passed = test.meth1().meth2.meth3()... .passed();
//   if (passed) {
//     // do little here... move onto next test...
//   } else {
//     auto fds = new failureDataStruct(iteration=i,
//     arguments=vector<everything>[i].args, expectedOutput, actualOutput);
//     // should probably have Foo class use a method to return fds as a value
//     // then can just push that method's return onto vector of fds's
//     failureDataStruct.push_back(fds);
//   }
// }
// cout << vector<everything>.size() - vector<failureDataStruct>.size() << " of
// " << vector<everything>.size() tests passed! << endl;
// for(let i = 0; i < vector<failureDataStruct>.size(); i++) {
//   failureDataStruct[i].generateReport(); // cout's a report of the failure
// }

template <typename inputType>
class Foo {
 public:
  // add in optional parameter for vector of lambdas
  // The lambdas would be written by the tester, but not invoked
  // They can be invoked with a method
  // This method will accept an optional parameter, numLambda's to run
  // There will be an internal iterator that is incremented each time
  // a lambda runs. If iterator !< lambda.size(), then go to next
  // method in the chain
  Foo(inputType input, bool f = false, string fr = "Default failure report")
      : actual{input}, failed{f}, failureReport{fr} {
    if (failed) {
      failureReport = "Created as failed test through constructor argument";
    }
  }

  ~Foo() {}

  inputType a;

  Foo& getFailed() {
    failed = true;
    return getMe();
  }

  // Returns this class (to enable method chaining)
  Foo& getMe() { return *this; }

  Foo& greaterThan(inputType test) {
    if (failed) {  // don't run further tests
      skippedTests++;
      return getMe();
    }

    if (actual > test) {  // continue chain
      return *this;
    }

    // Reaching this point in the method indicates test failure

    failureReport = "Expected " + to_string(actual) + " to be greater than " +
                    to_string(test);
    return getFailed();
  }

  inputType getActual() { return actual; }

  bool passed() { return !failed; }

  string passedStr(bool verbose = true) {
    return (passed()) ? "passed"
                      : (verbose ? ("failed: " + failureReport) : "failed");
  }

  operator int() { return (passed() ? 1 : 0); }

  operator bool() { return passed(); }

  operator string() { return passedStr(); }

 private:
  inputType actual;  // the actual value, to be used for testing

  bool failed;  // will be true for failed tests

  string failureReport;

  // For vector of lambdas
  int lambdaCount = 0;
  int lambdaIterator = 0;

  int skippedTests = 0;
};

int main() {
  cout << endl;  // formatting

  Foo f{7};

  auto a = f;

  auto b = a.getMe();

  cout << "a: " << (string)a.greaterThan(9001) << endl;

  cout << "b: " << (b.greaterThan(-3).passedStr()) << endl;

  auto alpha = []() {
    Foo c{9, true};
    cout << "c: " << c.greaterThan(-3).passedStr() << endl;
  };

  []() {
    Foo d{9};
    cout << "d: " << d.greaterThan(11).passedStr() << endl;  // test
  }();

  alpha();  // the lambda for 'c'
  // if generic lambda signature =
  //   std::function<returnType (arg1Type, arg2Type, ...)>
  // then a vector of lambdas would look like
  //   vector<function<void ()> lambdasVectorName;

  cout << endl;  // formatting

  return 0;
}
