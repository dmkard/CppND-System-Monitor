#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{ 
  std::vector<std::string> cpuUtilization = LinuxParser::CpuUtilization();
  int userTime = std::stoi(cpuUtilization[LinuxParser::CPUStates::kUser_]) - 
  					std::stoi(cpuUtilization[LinuxParser::CPUStates::kGuest_]);
  int niceTime = std::stoi(cpuUtilization[LinuxParser::CPUStates::kNice_]) - 
  					std::stoi(cpuUtilization[LinuxParser::CPUStates::kGuestNice_]);
  int idleAllTime = std::stoi(cpuUtilization[LinuxParser::CPUStates::kIdle_]) + 
  					std::stoi(cpuUtilization[LinuxParser::CPUStates::kIOwait_]);
  int systemAllTime = std::stoi(cpuUtilization[LinuxParser::CPUStates::kSystem_]) + 
  					std::stoi(cpuUtilization[LinuxParser::CPUStates::kIRQ_]) +
    				std::stoi(cpuUtilization[LinuxParser::CPUStates::kSoftIRQ_]);
  int notIdleAllTime = userTime + niceTime + systemAllTime +
    					std::stoi(cpuUtilization[LinuxParser::CPUStates::kSteal_]);
 
  int totalTime = notIdleAllTime + idleAllTime;
  int totalTimeCurrent = totalTime - prevTotal;
  int idleTimeCurrent = idleAllTime - prevIdle;
  prevTotal = totalTime;
  prevIdle = idleAllTime;

 return (totalTimeCurrent - idleTimeCurrent)/(totalTimeCurrent*1.);
}