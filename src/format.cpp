#include <iomanip>
#include <string>

#include "format.h"

using std::string;
using std::to_string;

// Done: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// ToDo: Try to find a better methods
string Format::ElapsedTime(long seconds) {
  int h = seconds / 3600;
  int h_rest = seconds % 3600;

  int m = h_rest / 60;
  int s = h_rest % 60;

  // Format the output
  std::ostringstream HH, MM, SS;
  HH << std::setfill('0') << std::setw(2) << h;
  MM << std::setfill('0') << std::setw(2) << m;
  SS << std::setfill('0') << std::setw(2) << s;

  return HH.str() + ":" + MM.str() + ":" + SS.str();
}