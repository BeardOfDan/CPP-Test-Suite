#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "testInstances.h"

int main() {
  string s = "asdf";

  testInstances u{s};
  cout << u.expectedOutput << endl;

  return 0;
}
