#include <string>
#include <vector>

#include "linux_parser.h"
#include "processor.h"

using std::string;
using std::vector;
using std::stoi;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  vector<string> utilization = LinuxParser::CpuUtilization();
  CPUTimes times;
  times.user = stoi(utilization[0]);
  times.nice = stoi(utilization[1]);
  times.system = stoi(utilization[2]);
  times.idle = stoi(utilization[3]);
  times.iowait = stoi(utilization[4]);
  times.irq = stoi(utilization[5]);
  times.softirq = stoi(utilization[6]);
  times.steal = stoi(utilization[7]);
  times.guest = stoi(utilization[8]);
  times.guest_nice = stoi(utilization[9]);

  int PrevIdle = previdle_ + previowait_;
  int Idle = times.idle + times.iowait;

  int PrevNonIdle = prevuser_ + prevnice_ + prevsystem_ + previrq_ + prevsoftirq_ + prevsteal_;
  int NonIdle = times.user + times.nice + times.system + times.irq + times.softirq + times.steal;

  int PrevTotal = PrevIdle + PrevNonIdle;
  int Total = Idle + NonIdle;

  // differentiate: actual value minus the previous one
  int totald = Total - PrevTotal;
  int idled = Idle - PrevIdle;

  float CPU_Percentage = ((totald - idled) * 1.0 ) / (totald * 1.0);

  prevuser_ = times.user;
  prevnice_ = times.nice;
  prevsystem_ = times.system;
  previdle_ = times.idle;
  previowait_ = times.iowait;
  previrq_ = times.irq;
  prevsoftirq_ = times.softirq;
  prevsteal_ = times.steal;
  prevguest_ = times.guest;
  prevguest_nice_ = times.guest_nice;

  return CPU_Percentage;
}
