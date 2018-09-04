
// #include <string>
// using std::string;

// // template <typename Func, typename args>
// void TEST(string description) {
//   // _errorData vector <errorData> // ex struct? {}
//   //
// }

// // possibly use a lambda expression as an anon function then use a macro to
// // define certain regular functions as the lambda functions, this way can
// have a
// // nice unit testing framework style

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <string>
using std::string;

int foo(int x) { return 2 + x; }

// auto bar{[]()};
// #define bar = []()
// #define DEFINE_PREFUNC(name) []##()() DEFINE_PREFUNC(TEST)

#define DEFINE_PRINT_FUNCTION(NAME, COUNT, VALUE) \
  void NAME##COUNT() { std::cout << #VALUE << std::endl; }
DEFINE_PRINT_FUNCTION(fun, 123, Test 1 "2" 3)

// #define DEFINE_F(name, sym) \
//   void name##sym() {}
// DEFINE_F(TEST, ());

// #define DEF_F(B, P) \
//   auto B##P() {     \
//     return *[]() {} \
//   }
// DEF_F(TE, ST)

// void baz() { cout << "Inside baz" << endl; }

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
    // cout << "destructor | input: " << a << endl;

    if (failed) {
      cout << "Failure Report: " << failureReport << endl;
    }
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
                                     // 'inputType' to handle variable type
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

  Foo c{9, 5, true};

  cout << "c: " << c.getA() << endl;

  // using P = auto (*)(double)->void;

  // auto foo = []() { cout << "Inside foo" << endl; };

  // TEST();
  // { cout << "Inside alias" << endl; }

  // bar { cout << "Inside bar" << endl; }
  // ();

  // foo();

  // std::function<void()> bar = baz;

  // bar();

  // &TEST { foo(); }
  // ();

  // P()(5.3);

  return 0;
}
