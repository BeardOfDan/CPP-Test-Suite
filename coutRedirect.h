// Note: The below struct was inspired by the answer by "Björn Pollex"
//   https://stackoverflow.com/questions/5419356/redirect-stdout-stderr-to-a-string

#include <iostream>
using std::cout;

#include <streambuf>
using std::streambuf;

#include <sstream>
using std::stringstream;

#include <string>
using std::string;

struct redirectOutput {
  redirectOutput() : originalCoutBuffer(cout.rdbuf()) {
    cout.rdbuf(capturedOutput.rdbuf());  // capture cout's output
  }

  ~redirectOutput() {
    cout.rdbuf(originalCoutBuffer);  // restore cout's flow
  }

  string getContents() { return capturedOutput.str(); }

 private:
  streambuf* originalCoutBuffer;
  stringstream capturedOutput;
};

/* Example of use

#include "coutRedirect.h"
// redirectOutput struct

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

int main() {
  string capturedContent;

  {
    redirectOutput redirection;

    // multiline output
    cout << "Testing...\n" << endl << "Further analysis..." << endl;

    capturedContent = redirection.getContents();
  }  // end of local scope, this causes the redirectOutput destructor to execute

  cout << "Outside" << endl;  // confirms that cout acts normally

  cout << "capturedContent: '" << capturedContent << "'" << endl;

  return 0;
}


*/
