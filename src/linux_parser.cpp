#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ 
  int memoryTotal, memoryFree;
  string line, temp;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> temp >> memoryTotal;
    std::getline(stream, line);
    linestream.str(line);
    linestream >> temp >> memoryFree;
  }
  return (memoryTotal-memoryFree)/(memoryTotal*1.); 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{
  long upTime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> upTime;
  }
  return upTime; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) 
{ 
  long utime, stime, cutime, cstime;
  string line, temp ;
  std::ifstream stream(kProcDirectory + std::to_string(pid)+ kStatFilename);
  if (stream.is_open()) 
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(int i = 0; i < 13; i++)
      linestream >> temp;
    linestream >> utime >> stime >> cutime >> cstime;
    
  }
  return utime + stime + cutime + cstime; 
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{ 
  string line;
  vector<string> cpuUtilization;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    line = line.substr(5);
    std::istringstream linestream(line);
    while(std::getline(linestream, line, ' '))
      cpuUtilization.push_back(line);
  }
  return cpuUtilization; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{
  int totalProcesses;
  string line, temp;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line))
    {
      if(line.find("processes") != string::npos)
      {
        std::istringstream linestream(line);
        linestream >> temp >> totalProcesses;
      }
    }
  }
  return totalProcesses; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{ 
  int runningProcesses;
  string line, temp;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) 
  {
    while(std::getline(stream, line))
    {
      if(line.find("procs_running") != string::npos)
      {
        std::istringstream linestream(line);
    	linestream >> temp >> runningProcesses;
      }
    }
  }
  return runningProcesses; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) 
{ 
  string command;
  std::ifstream stream(kProcDirectory +std::to_string(pid)+ kCmdlineFilename);
  if (stream.is_open()) 
  {
    std::getline(stream, command);
  }
  return command; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) 
{ 
  int memoryUsage;
  string line, temp;
  std::ifstream stream(kProcDirectory +std::to_string(pid)+ kStatusFilename);
  if (stream.is_open()) {
    
    for(int i = 0; i < 18; i++)
    {
      std::getline(stream, line);
    }

    std::istringstream linestream(line);
    linestream >> temp >>  memoryUsage;
    memoryUsage /= 1024;
    
  }
  return std::to_string(memoryUsage);  
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) 
{ 
  string line, uid, temp;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) 
  {
    for(int i = 0; i < 9; i++)
    {
      std::getline(stream, line);
    }

    std::istringstream linestream(line);
    linestream >> temp >> uid;
    return uid;
   }
  return {};
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) 
{ 
  int uid = std::stoi(Uid(pid));
  int tempUid;
  string line, name, temp;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) 
  {
    while(std::getline(stream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> name >> temp >> tempUid;
      if(tempUid == uid)
        return name;
     }
   }
  return {};
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) 
{ 
  string line;
  long time;
  std::ifstream stream(kProcDirectory +std::to_string(pid)+ kStatFilename);
  if (stream.is_open()) 
  {
    for(int i = 0; i < 22; i++)
    {
      std::getline(stream, line, ' ');
    }
    
    std::istringstream linestream(line);
    linestream >>  time;
  }
  return LinuxParser::UpTime() - time/sysconf(_SC_CLK_TCK); 
}