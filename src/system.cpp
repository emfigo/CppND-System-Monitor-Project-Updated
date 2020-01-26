#include <unistd.h>
#include <algorithm>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::sort;

Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() { 
  vector<int> processesPids = LinuxParser::Pids();
  processes_ = {};

  for(int pid: processesPids) {
    processes_.push_back(Process(pid));
  }

  sort(processes_.begin(), processes_.end());

  return processes_; 
}

std::string System::Kernel() const { return kernelName_; }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() const { return operatingSystemName_; }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long int System::UpTime() { return static_cast<long int>(LinuxParser::UpTime()); }
