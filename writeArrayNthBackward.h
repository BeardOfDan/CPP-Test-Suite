// // Lab 1, Write Array Nth Backwards
// // Programmer: Daniel Roberts
// // Editor(s) used: VS Code
// // Compiler(s) used: g++

#include <iostream>
// using std::cin;
using std::cout;
// using std::endl;

// void writeArrayNthBackward(const char[], int, int, int);
// void outputTestRun(const char arr[], int first = 0, int last = 6, int n = 1);

// int main() {  // driver function to test writeArrayNthBackward

//   cout << "Lab 1, Write Array Nth Backwards" << endl;
//   cout << "Programmer: Daniel Roberts" << endl;
//   cout << "Editor(s) used: VS Code" << endl;
//   cout << "Compiler(s) used: g++" << endl;
//   cout << "File: " << __FILE__ << endl;
//   cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl << endl;

//   // Option A. use the function a bunch of times, with comments noting the
//   // expected output. Possibly preface it with a cout saying, about to call
//   // functionName with args ... expecting to output "asdf", then call the
//   // function with those args

//   // Option B. use option A in combination with a bash script to check the
//   // output. Possibly have the script supply the input (ex. an array of
//   structs
//   // to main, then main uses the structs for input for the function)

//   // Option C. save cout to a var (to have it safe somewhere), then overwrite
//   // cout with something to trap the output. This will allow me to use the
//   // program to determine if the output is correct (possibly by using
//   asserts,
//   // or even formal unit testing), instead of a human reading the console

//   // Supplied example outputs:
//   // =========================
//   // Input string	  N 	Output
//   // -------------------------
//   // abc123	        2 	2ca
//   // hello	        1 	olleh
//   // hello	        3 	l
//   // c1c1c1	        2 	ccc

//   const char* inputs[4]{"abc123", "hello", "hello", "c1c1c1"};
//   int ns[4]{2, 1, 3, 2};
//   int lasts[4]{6, 5, 5, 6};

//   for (size_t i{}; i < 4; i++) {
//     outputTestRun(inputs[i], 0, lasts[i], ns[i]);

//     cout << endl << endl;
//   }

//   return 0;
// }

// void outputTestRun(const char arr[], int first, int last, int n) {
//   cout << "arr:    " << arr << " | n: " << n << endl;
//   cout << "output: ";
//   writeArrayNthBackward(arr, first, last, n);

//   // =========================================

//   // make 2 versions, one that reads from the command line, and another that
//   // accepts a struct that has the values, to give it bells/whistles, compute
//   // the 'last' value
// }

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
