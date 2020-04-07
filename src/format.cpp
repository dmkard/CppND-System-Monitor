#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
  std::string elapsedTime;
  int eHour, eMinute, eSecond;
  eHour = static_cast<int>(seconds/3600);
  eMinute = static_cast<int>((seconds - eHour*3600)/60);
  eSecond = static_cast<int>(seconds - eHour*3600 - eMinute*60);
  
  elapsedTime +=  (eHour < 10)? "0": "";
  elapsedTime +=  std::to_string(eHour) + ":";
  
  elapsedTime +=  (eMinute < 10)? "0": "";
  elapsedTime +=  std::to_string(eMinute) + ":";
  
  elapsedTime +=  (eSecond < 10)? "0": "";
  elapsedTime +=  std::to_string(eSecond);
  return elapsedTime; 
}