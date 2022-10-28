#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;
using std::stringstream;

// Format integer of seconds into elapsed time string HH:MM:SS
string Format::ElapsedTime(long seconds) {
  int hh, mm, ss;
  stringstream elapsedString;
  hh = (seconds / 3600);
  mm = (seconds / 60) % 60;
  ss = seconds % 60;

  elapsedString 
         << std::setfill('0') << std::setw(2) << hh << ":"
         << std::setfill('0') << std::setw(2) << mm << ":"
         << std::setfill('0') << std::setw(2) << ss;
  
  return elapsedString.str();
}