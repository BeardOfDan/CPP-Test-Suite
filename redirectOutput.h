// Note: The below struct was inspired by the answer by "Björn Pollex"
//   In particular, the constructor and destructor
//   https://stackoverflow.com/questions/5419356/redirect-stdout-stderr-to-a-string

// Note: The below function "getVectorOfLines" uses a method, to break up
// strings by a delimiter, that was from the answer by "Evan Teran"
//   https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string

#include <iostream>
using std::cout;

#include <streambuf>
using std::streambuf;

#include <sstream>
using std::stringstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

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
