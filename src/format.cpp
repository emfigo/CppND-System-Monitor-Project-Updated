#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "format.h"

using std::string;
using std::stringstream;
using std::to_string;
using std::setw;
using std::setfill;

string Format::ElapsedTime(long seconds) { 
  int hour, min;
  stringstream strm;

  hour = seconds / 3600;
  seconds = seconds % 3600;
  min = seconds / 60;
  seconds = seconds % 60;

  strm << setw(2) << setfill('0') << hour << ':';
  strm << setw(2) << setfill('0') << min << ':';
  strm << setw(2) << setfill('0') << seconds;

  return strm.str();
}
