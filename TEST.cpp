// Initially from scratch.cpp
//   A 'scratch' cpp file for me to mess around in

// NOTE: This is currently an idea in a VERY raw form.
// The goal is to create something like the 'expect' library (for JS)

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::to_string;

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
  // Try to find a generic 'class pointer'

  // use an optional parameter to setup the 'failed' version, not the input

  // add in optional parameter for vector of lambdas
  // The lambdas would be written by the tester, but not invoked
  // They can be invoked with a method
  // This method will accept an optional parameter, numLambda's to run
  // There will be an internal iterator that is incremented each time
  // a lambda runs. If iterator !< lambda.size(), then go to next
  // method in the chain
  Foo(inputType input, bool f = false, string fr = "Created as failed test")
      : actual{input}, failed{f}, failureReport{fr} {
    // cout << "constructor | input: " << input << endl;
  }

  ~Foo() {
    // cout << endl
    //      << "destructor | input: " << a
    //      << endl;  // temp use of input as a unique identifier. Should
    //      probably
    //                // try to find a way to serialize these things

    // if (failed) {
    //   cout << "Failure Report: " << failureReport << endl;
    // }
    // cout << endl;  // formatting
  }

  inputType a;

  Foo& getFailed() {
    // Foo neg{a, eVal, true, failureReport};
    // return neg;

    failed = true;
    return *this;
  }

  // Returns this class (to enable method chaining)
  Foo& getMe() { return *this; }

  Foo& greaterThan(inputType test) {
    if (failed) {
      cout << "Skipping since failed previous test" << endl;
      return getMe();
    }

    if (actual > test) {
      return *this;
    }

    failureReport =
        "Expected " + to_string(a) + " to be greater than " + to_string(b);
    return getFailed();
  }

  inputType getA() {
    if (failed) {
      inputType unInitializedVal{};  // not initializing some variable of type
                                     // 'inputType' to handle the mutability of
                                     // variable type across different use cases
      return unInitializedVal;
    }
    return a;
  }

  bool passed() {
    return !failed;  // if all of the tests in the chain passed
    // ...technically might not need the 'getFailed' method,
    // since can just use this and have whatever would trigger
    // the 'getFailed' method set 'failed' to true
    // and possibly some other, internal, var to true, to skip
    // the running of any further tests in the chain (for efficiency)
    // (and for ease of only needing one failure report per chain of tests)
    // Could just use failed instead of another var, since it would always
    // be linked in purpose/value
  }

  string passedStr(bool verbose = true) {
    return (passed()) ? "passed"
                      : (verbose ? ("failed: " + failureReport) : "failed");
  }

  // inputType eVal;  // expected value

  string failureReport;  // should be used if

 private:
  bool failed;  // will be true for failed tests
};

int main() {
  Foo f{7};

  auto a = f;

  auto b = a.getMe();

  cout << endl << "a: " << a.greaterThan(9001).passedStr() << endl << endl;

  cout << endl << "b: " << b.greaterThan(-3).passedStr() << endl << endl;

  []() {
    Foo c{9, true};
    cout << "c: " << c.greaterThan(-3).passedStr() << endl;
  }();

  []() {
    Foo d{9};
    cout << endl << "d: " << d.greaterThan(11).passedStr() << endl;  // test
  }();

  return 0;
}
