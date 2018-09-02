
#include <string>
using std::string;

// TODO: See if there is a way to add a generic tuple (for args)
//       Then the execTest method could be placed here
//         ... assuming that a generic function pointer could be placed here,
//         then initialized in the extended class's constructor

// A base class to be extended for each type of test
class testInstance {
 public:
  testInstance(string eo = "") : expectedOutput{eo} {}

  ~testInstance() {}

  string expectedOutput;
  string actualOutput;

 private:
};
