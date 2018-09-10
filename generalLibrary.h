// C++ Test Suite
// Programmer: Daniel Roberts
// Compiler(s) used: g++ -std=c++17 -Wall

#ifndef GENERAL_LIBRARY_H
#define GENERAL_LIBRARY_H

#include <iostream>
using std::cout;

#include <streambuf>
using std::streambuf;

#include <sstream>
using std::ostringstream;
using std::stringstream;

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::to_string;

template <typename type>
string arrToString(type* arr, int size, string delimiter = ", ") {
  string s = "[ ";
  for (size_t i{}; i < size; i++) {
    s += to_string(arr[i]) + ((i + 1 < size) ? delimiter : " ");
  }
  return (s + "]");
}

// This function is required since the templated input types have to convert any
// given type to a string, but the different types require different conversion
// methods (assuming single line implementation)
template <typename type>
string toString(type value) {
  ostringstream oss;
  oss << value;
  return oss.str();
}

// Note: The below struct was inspired by the answer by "Björn Pollex"
//   In particular, the constructor and destructor
//   https://stackoverflow.com/questions/5419356/redirect-stdout-stderr-to-a-string

// Note: The below function "getVectorOfLines" uses a method, to break up
// strings by a delimiter, that was from the answer by "Evan Teran"
//   https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string

struct redirectOutput {
 public:
  redirectOutput() : originalCoutBuffer(cout.rdbuf()) {
    cout.rdbuf(capturedOutput.rdbuf());  // capture cout's output
  }

  ~redirectOutput() {
    cout.rdbuf(originalCoutBuffer);  // restore cout's flow
  }

  string getContents() { return capturedOutput.str(); }

  vector<string> getVectorOfLines(char delimiter = '\n') {
    stringstream content(capturedOutput.str());
    vector<string> result;

    string line;
    while (getline(content, line, delimiter)) {
      *(back_inserter(result)++) = line;
    }

    return result;
  }

 private:
  streambuf* originalCoutBuffer;
  stringstream capturedOutput;
};

#endif
