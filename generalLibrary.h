
#ifndef GENERAL_LIBRARY_H
#define GENERAL_LIBRARY_H

#include <string>
using std::string;
using std::to_string;

#include <sstream>
using std::ostringstream;

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

#endif
