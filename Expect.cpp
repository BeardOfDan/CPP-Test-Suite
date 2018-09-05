// C++ Test Suite
// Programmer: Daniel Roberts
// Compiler(s) used: g++ -std=c++17 -Wall

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::to_string;

#include <array>
using std::size;

#include "generalLibrary.h"
// string arrToString(array)

#include "Expect.h"

int main() {
  cout << endl;  // formatting

  int vals[]{-1, 0, 1, 2, 3, 4, 5, 6, 9};

  Expect f{7, "not to be greater than every number in the array " +
                  arrToString(vals, size(vals))};

  auto a = f;

  auto b = Expect(a.getActual(), "to be greater than -3");

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
               .testStatus())
       << endl;

  auto alpha = []() {
    Expect c{9, "Expect to 'fail' due to constructor argument", true};
    cout << "c: " << c.toHaveFailed().testStatus(true, false) << endl;
  };

  []() {
    const int testInput = 11;
    Expect d{9, "to be less than a given number: " + to_string(testInput)};
    cout << "d: " << d.lessThan(testInput).testStatus() << endl;
  }();

  alpha();  // the lambda for test 'c'

  const int answerToEverything = 42;

  Expect e{42, "to be the answer to everything"};
  cout << "e: " << (string)e.equalTo(answerToEverything) << endl;

  Expect g{3.14, "Expect to be able to also use type double"};
  cout << "g: " << (string)g.equalTo(g.getActual()).testStatus(true, false)
       << endl;

  Expect h{"Actual value text", "Expect to be able to also use type string"};
  cout << "h: "
       << (string)h.equalTo("Actual value text").testStatus(true, false)
       << endl;

  cout << endl;  // formatting

  return 0;
}
