#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "linux_parser.h"

using std::string;

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) : pid_(pid) {};
  int Pid() const;                         
  string User();                           
  string Command();                        
  float CpuUtilization() const;            
  string Ram();                            
  long int UpTime();                       
  bool operator<(Process const& a) const;  

 private:
  int pid_;
  string command_ = LinuxParser::Command(pid_);
  string user_ = LinuxParser::User(pid_);
};

#endif
