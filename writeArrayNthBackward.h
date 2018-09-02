// Lab 1, Write Array Nth Backwards
// Programmer: Daniel Roberts
// Editor(s) used: VS Code
// Compiler(s) used: g++ -std=c++17 -Wall

#include <iostream>
using std::cout;

void writeArrayNthBackward(const char arr[], int first, int last, int n) {
  if ((first > last) || (n < 1)) {  // error case
    return;
  } else if (first == last) {  // edge case
    cout << arr[last];
    return;
  } else {  // standard case
    cout << arr[last];
    writeArrayNthBackward(arr, first, last - n, n);
  }
}

// Supplied example outputs:
// =========================
// Input string	  N 	Output
// -------------------------
// abc123	        2 	2ca
// hello	        1 	olleh
// hello	        3 	l
// c1c1c1	        2 	ccc
