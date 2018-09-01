#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "testInstances.h"

void foo();
void bar(int);

int main() {
  string s = "asdf";

  // testInstances t{&foo, s};

  // cout << t.expectedOutput << endl;
  // t.execTest();

  // cout << endl << "======\n" << endl;

  testInstances u{&bar, s};
  cout << u.expectedOutput << endl;
  u.execTest();

  return 0;
}

void foo() { cout << "Inside foo!" << endl; }
void bar(int i) { cout << "Inside bar!\n  i: " << i << endl; }
