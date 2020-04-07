#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid)
{
  this->pid = pid;
  command = LinuxParser::Command(pid);
  user = LinuxParser::User(pid);
  float totalTime = LinuxParser::ActiveJiffies(pid)/sysconf(_SC_CLK_TCK); 
  int seconds = LinuxParser::UpTime(pid);
  cpuUtil = totalTime/seconds;
}
// TODO: Return this process's ID
int Process::Pid() 
{ 
  return pid; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() 
{ 
  float totalTime = LinuxParser::ActiveJiffies(pid)/sysconf(_SC_CLK_TCK); 
  int seconds = LinuxParser::UpTime(pid);
  cpuUtil = totalTime/seconds;
  return cpuUtil;
}

// TODO: Return the command that generated this process
string Process::Command() 
{ 
  return command; 
}

// TODO: Return this process's memory utilization
string Process::Ram() 
{ 
  return LinuxParser::Ram(pid); 
}

// TODO: Return the user (name) that generated this process
string Process::User() 
{ 
  return user; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() 
{
  return LinuxParser::UpTime(pid); 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const 
{ 
  return cpuUtil > a.cpuUtil; 
}