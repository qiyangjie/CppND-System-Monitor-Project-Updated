#include <string>
#include <vector>

#include "linux_parser.h"
#include "processor.h"

using std::stof;
using std::string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  vector<string> cpuData = LinuxParser::CpuUtilization();

  int user = stof(cpuData[1]);
  int nice = stof(cpuData[2]);
  int system = stof(cpuData[3]);
  int idle = stof(cpuData[4]);
  int iowait = stof(cpuData[5]);
  int irq = stof(cpuData[6]);
  int softirq = stof(cpuData[7]);
  int steal = stof(cpuData[8]);
  //int guest = stof(cpuData[9]);
  //int guest_nice = stof(cpuData[10]);

  int Idle_ = idle + iowait;
  int NonIdle = user + nice + system + irq + softirq + steal;

  int Total_ = Idle_ + NonIdle;

  int totald = Total_ - Total;

  int idled = Idle_ - Idle;

  Total = Total_;

  Idle = Idle_;

  return (float)(totald - idled) / totald;
}