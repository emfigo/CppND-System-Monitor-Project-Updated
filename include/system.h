#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

#include "linux_parser.h"

using std::string;

class System {
 public:
  Processor& Cpu();                   
  std::vector<Process>& Processes();  
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  string Kernel() const;              
  string OperatingSystem() const;     

 private:
  Processor cpu_ = {};
  string operatingSystemName_ = LinuxParser::OperatingSystem();
  string kernelName_ = LinuxParser::Kernel();
  std::vector<Process> processes_ = {};
};

#endif
