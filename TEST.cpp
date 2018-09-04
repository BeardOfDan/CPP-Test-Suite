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
  // TODO: Add string description
  //   good for describing what test failed in error report
  //   or to output what tests passed
  Foo(inputType input, bool f = false, string fr = "Default failure report")
      : actual{input}, failed{f}, failureReport{fr} {
    if (failed) {
      failureReport = "Created as failed test through constructor argument";
    }
  }

  ~Foo() {}

  Foo& getFailed() {
    failed = true;
    return getMe();
  }

  // Returns this class (to enable method chaining)
  Foo& getMe() { return *this; }

  Foo& greaterThan(inputType test,
                   std::function<bool(int, int)> comparison =
                       [](int actual, int test) { return (actual > test); },
                   string customFailureReport = "") {
    if (failed) {
      skippedTests++;
      return getMe();  // don't run further tests
    }

    if (comparison(actual, test)) {
      return getMe();  // continue chain
    } else {           // failed the test
      failureReport = (customFailureReport.length() > 0)
                          ? customFailureReport
                          : "Expected " + to_string(actual) +
                                " to be greater than " + to_string(test);
      return getFailed();
    }
  }

  inputType getActual() { return actual; }

  bool passed() { return !failed; }

  string passedStr(bool verbose = true) {
    return passed() ? "passed"
                    : (verbose ? ("failed: " + failureReport + "\n  skipped " +
                                  to_string(skippedTests) + " tests.")
                               : "failed");
  }

  operator int() { return (passed() ? 1 : 0); }

  operator bool() { return passed(); }

  operator string() { return passedStr(); }

 private:
  const inputType actual;  // the actual value, to be used for testing

  bool failed;  // Initially false, but a failed test turns it true

  string failureReport;

  int skippedTests = 0;
};

int main() {
  cout << endl;  // formatting

  Foo f{7};

  auto a = f;

  auto b = Foo(a.getActual());

  int vals[]{1, 2, 3, 4, 5, 9};

  cout << "a: "
       << (string)(a.greaterThan(
              vals[0],
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
    Foo c{9, true};
    cout << "c: " << c.greaterThan(-3).passedStr() << endl;
  };

  []() {
    Foo d{9};
    cout << "d: " << d.greaterThan(11).passedStr() << endl;  // test
  }();

  alpha();  // the lambda for 'c'

  cout << endl;  // formatting

  return 0;
}

//
// Randomly though up method for creating that syntax
//
// DEFINE_STRUCTS(name, value)
//   struct #name {string name = value}
//
// some loop that goes through all of the defined vars (strings),
// such as SquareRootTest, to create structs, then the defined TEST
// functions, such as below, are simply overloading the function

// TEST (SquareRootTest, PositiveNos) {
//     EXPECT_EQ (18.0, square-root (324.0));
//     EXPECT_EQ (25.4, square-root (645.16));
//     EXPECT_EQ (50.3321, square-root (2533.310224));
// }
