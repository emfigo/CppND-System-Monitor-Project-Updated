#ifndef PROCESSOR_H
#define PROCESSOR_H

struct CPUTimes {
  int user = 0;
  int nice = 0;
  int system = 0;
  int idle = 0;
  int iowait = 0;
  int irq = 0;
  int softirq = 0;
  int steal = 0;
  int guest = 0;
  int guest_nice = 0;
};

class Processor {
 public:
  float Utilization();

 private:
  CPUTimes prevTimes_;
  CPUTimes readCPUTimes();

  void saveCPUTimes(CPUTimes const times);
};

#endif
