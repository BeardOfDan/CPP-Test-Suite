
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
