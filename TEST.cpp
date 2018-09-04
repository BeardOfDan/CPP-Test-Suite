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

template <typename inputType>
class Foo {
 public:
  // Try to find a generic 'class pointer'

  // use an optional parameter to setup the 'failed' version, not the input

  Foo(inputType input, inputType ev, bool f = false,
      string fr = "Some failure description")
      : a{input}, eVal{a + a}, failed{f}, failureReport{fr} {
    // cout << "constructor | input: " << input << endl;
  }

  ~Foo() {
    cout << endl
         << "destructor | input: " << a
         << endl;  // temp use of input as a unique identifier. Should probably
                   // try to find a way to serialize these things

    if (failed) {
      cout << "Failure Report: " << failureReport << endl;
    }
    cout << endl;  // formatting
  }

  inputType a;

  Foo& getFailed() {
    Foo neg{a, eVal, true, failureReport};

    return neg;
  }

  Foo& getMe() {
    if (!failed) {
      return *this;
    }

    return getFailed();
  }

  Foo& greaterThan(inputType b) {
    if (a > b) {
      return *this;
    }
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

  inputType eVal;  // expected value

  bool failed;  // will be true for failed tests

  string failureReport;  // should be used if

 private:
};

int main() {
  Foo f{7, 14};

  auto a = f;

  auto b = a.getMe().getA();

  cout << "b: " << b << endl;

  []() {
    Foo c{9, 5, true};

    cout << "c: " << c.getA() << endl;
  }();

  return 0;
}
