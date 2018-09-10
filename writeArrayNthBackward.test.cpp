// Lab 1, Write Array Nth Backward
// Programmer: Daniel Roberts
// Compiler(s) used: g++ -std=c++17 -Wall

#include "Expect.h"
// Testing framework

#include "writeArrayNthBackward.h"
// Function, of the same name, to test

#include "generalLibrary.h"
// toString, a templated function
// redirectOutput, a struct to capture output from 'cout' as a string

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include <tuple>
using std::apply;
using std::get;
using std::make_tuple;
using std::tuple;

#include <vector>
using std::vector;

string getArrayOutput(char*, int n = 1);
string getTestDescription(char* input, int n = 1, string result = "");
string getFuncCall(char*, int n = 1);

int main() {
  cout << endl;  // Basic program info
  cout << "Lab 1, writeArrayNthBackwards" << endl;
  cout << "Programmer: Daniel Roberts" << endl;
  cout << "Editor(s) used: VS Code" << endl;
  cout << "Compiler(s) used: g++ -std=c++17 -Wall" << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl;
  cout << "Standard: C++" << (to_string(__cplusplus)).substr(2, 2) << endl
       << endl;  // Note: Should be C++17, if not, then there will be errors!

  // arguments for calling writeArrayNthBackward
  // Note: I am assuming all calls to the function to test will be with the
  // whole of a supplied string, so first=0 and last=strlen(char* input)
  //           input, n
  vector<tuple<char*, int>> args;
  // what the function should print to the screen
  vector<string> expectations;

  // Supply arguments and the expected input
  args.push_back(make_tuple((char*)"abc123", 2));
  expectations.push_back("2ca");

  args.push_back(make_tuple((char*)"hello", 1));
  expectations.push_back("olleh");

  args.push_back(make_tuple((char*)"hello", 3));
  expectations.push_back("l");

  args.push_back(make_tuple((char*)"c1c1c1", 2));
  expectations.push_back("ccc");
  // End of supplied test values

  // Start of my own test values
  args.push_back(make_tuple((char*)"abcdefghijklmnopqrstuvwxyz", 1));
  expectations.push_back("zyxwvutsrqponmlkjihgfedcba");

  args.push_back(make_tuple((char*)"abcdefghijklmnopqrstuvwxyz", 2));
  expectations.push_back("ywusqomkigeca");

  args.push_back(make_tuple((char*)"c0i1t2e3b4a5h6p7l8a9", 2));
  expectations.push_back("alphabetic");

  args.push_back(make_tuple((char*)"9 8 7n6u5m4e3r2i1c", 2));
  expectations.push_back("123456789");

  // Test each argument/expectation pair
  for (size_t i{}; i < args.size(); i++) {
    const string actual = apply(getArrayOutput, args[i]);
    Expect test{actual, getTestDescription(get<0>(args[i]), get<1>(args[i]),
                                           expectations[i])};
    test.equalTo(expectations[i]).writeTestStatus(true, false);
  }

  cout << endl;  // formatting

  return 0;
}

// Captures the output from writeArrayNthBackward and returns it as a string
string getArrayOutput(char* input, int n) {
  redirectOutput output;
  writeArrayNthBackward(input, 0, strlen(input), n);
  return output.getContents();
}

// Dynamically creates a test description
string getTestDescription(char* input, int n, string result) {
  return ("Expect " + getFuncCall(input, n) + " to write \"" + result + "\"");
}

// Returns a string of what the function call looked like
string getFuncCall(char* input, int n) {
  return "writeArrayNthBackwards(\"" + toString(input) + +"\", 0, " +
         toString(strlen(input)) + ", " + toString(n) + ")";
}
