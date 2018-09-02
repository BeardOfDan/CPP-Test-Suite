#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "testInstance.h"

int main() {
  string s = "asdf";

  testInstance u{s};
  cout << u.expectedOutput << endl;

  return 0;
}
