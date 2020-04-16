#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// Done: Return this process's ID
int Process::Pid() { return pid; }

// Done: Return this process's CPU utilization
float Process::CpuUtilization() {
  // Get the uptime of the system
  long uptime = LinuxParser::UpTime();

  // Get proc state
  vector<string> CpuData = LinuxParser::ProcessCpuUtilization(pid);
  int utime = stof(CpuData[13]);
  int stime = stof(CpuData[14]);
  int cutime = stof(CpuData[15]);
  int cstime = stof(CpuData[16]);
  int starttime = stof(CpuData[21]);

  // Get hertz
  long Hertz = sysconf(_SC_CLK_TCK);

  // Calculattion
  long total_time = utime + stime + cutime + cstime;

  long seconds = uptime - (starttime / Hertz);

  cpuUtilization = (float)total_time / Hertz / seconds;

  return cpuUtilization;
}

// Done: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid); }

// Done: Return this process's memory utilization
string Process::Ram() {
  ram = stof(LinuxParser::Ram(pid)) / 1024;
  return to_string(ram);
}

// Done: Return the user (name) that generated this process
string Process::User() {
  string userName = LinuxParser::User(pid);
  // Some username is too long, resize the string.
  if (userName.size() > 6) {
    userName.resize(6);
  }

  return userName;
}

// Done: Return the age of this process (in seconds)
long int Process::UpTime() {
  long starttime = LinuxParser::UpTime(pid);

  // Get hertz
  long Hertz = sysconf(_SC_CLK_TCK);

  return starttime / Hertz;
}

// Done: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
  return cpuUtilization > a.cpuUtilization;
}