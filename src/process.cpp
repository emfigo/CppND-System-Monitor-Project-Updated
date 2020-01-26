#include <math.h>
#include <unistd.h>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::stringstream;
using std::stol;
using std::to_string;
using std::vector;

int Process::Pid() const { return pid_; }

float Process::CpuUtilization() const { 
  vector<int> times = LinuxParser::CpuUtilization(pid_);
  long systemUptime = LinuxParser::UpTime();
  long Hertz = sysconf(_SC_CLK_TCK);

  int utime = times[0];
  int stime = times[1];
  int cutime = times[2];
  int cstime = times[3];
  int starttime = times[4];

  int totalTime = utime + stime;

  totalTime = totalTime + cutime + cstime;

  float sec = systemUptime - (starttime / Hertz);

  float cpuUsage = (totalTime / Hertz) / sec;

  return cpuUsage; 
}

string Process::Command() { return command_; }

string Process::Ram() { 
  long ram = stol(LinuxParser::Ram(pid_));
  stringstream strm;

  strm << std::fixed << std::setprecision(2) << ram * pow(2.0, -10.0);

  return strm.str(); 
}

string Process::User() { 
  return user_; 
}

long int Process::UpTime() { 
  vector<int> times = LinuxParser::CpuUtilization(pid_);
  int starttime = times[4];
  long Hertz = sysconf(_SC_CLK_TCK);

  return LinuxParser::UpTime() - static_cast<long int>(starttime / Hertz);
}

bool Process::operator<(Process const& a) const { return CpuUtilization() > a.CpuUtilization(); }
