#include <string>
#include <vector>

#include "linux_parser.h"
#include "processor.h"

using std::string;
using std::vector;
using std::stoi;

float Processor::Utilization() { 
  CPUTimes times = Processor::readCPUTimes();

  int PrevIdle = prevTimes_.idle + prevTimes_.iowait;
  int Idle = times.idle + times.iowait;

  int PrevNonIdle = prevTimes_.user + prevTimes_.nice + prevTimes_.system + prevTimes_.irq + prevTimes_.softirq + prevTimes_.steal;
  int NonIdle = times.user + times.nice + times.system + times.irq + times.softirq + times.steal;

  int PrevTotal = PrevIdle + PrevNonIdle;
  int Total = Idle + NonIdle;

  // differentiate: actual value minus the previous one
  int totald = Total - PrevTotal;
  int idled = Idle - PrevIdle;

  Processor::saveCPUTimes(times);

  return ((totald - idled) * 1.0 ) / (totald * 1.0);
}

CPUTimes Processor::readCPUTimes() {
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

  return times;
}

void Processor::saveCPUTimes(CPUTimes const times) {
  prevTimes_.user = times.user;
  prevTimes_.nice = times.nice;
  prevTimes_.system = times.system;
  prevTimes_.idle = times.idle;
  prevTimes_.iowait = times.iowait;
  prevTimes_.irq = times.irq;
  prevTimes_.softirq = times.softirq;
  prevTimes_.steal = times.steal;
  prevTimes_.guest = times.guest;
  prevTimes_.guest_nice = times.guest_nice;
}
