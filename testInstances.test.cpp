#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "testInstances.h"

void foo();

int main() {
  string s = "asdf";

  testInstances t{&foo, s};

  t.execTest();

  return 0;
}

void foo() { cout << "Inside foo!" << endl; }
