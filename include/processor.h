#ifndef PROCESSOR_H
#define PROCESSOR_H

struct CPUTimes {
  int user;
  int nice;
  int system;
  int idle;
  int iowait;
  int irq;
  int softirq;
  int steal;
  int guest;
  int guest_nice;
};

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  int prevuser_ = 0;
  int prevnice_ = 0;
  int prevsystem_ = 0;
  int previdle_ = 0;
  int previowait_ = 0;
  int previrq_ = 0;
  int prevsoftirq_ = 0;
  int prevsteal_ = 0;
  int prevguest_ = 0;
  int prevguest_nice_ = 0;
};

#endif
