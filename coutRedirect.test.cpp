#include "coutRedirect.h"
// redirectOutput struct

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

int main() {
  string capturedContent;

  vector<string> lines;

  {  // scope to localize the redirectOutput struct
    redirectOutput redirection;

    // multiline output
    cout << "Testing...\n" << endl << "Further analysis..." << endl;

    capturedContent = redirection.getContents();

    lines = redirection.getVectorOfLines();
  }  // end of local scope, this causes the redirectOutput destructor to execute

  cout << "Outside" << endl;  // confirms that cout acts normally

  cout << "capturedContent: '" << capturedContent << "'" << endl;

  cout << endl << "vector: " << endl;
  cout << "  size: " << lines.size() << endl;

  for (size_t i{}; i < lines.size(); i++) {
    cout << "    '" << lines[i] << "'" << endl;
  }

  return 0;
}
