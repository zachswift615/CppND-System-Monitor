#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using std::cout;
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
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
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
float LinuxParser::MemoryUtilization() {
  float mtotal;
  float mfree;
  std::ifstream memInfoFileStream(kProcDirectory + kMeminfoFilename);
  if (memInfoFileStream.is_open()) {
    string line;
    while (std::getline(memInfoFileStream, line)) {
      std::istringstream memFileLineStream(line);
      string k;
      string v;
      while (memFileLineStream >> k >> v) {
        
        if (k == "MemTotal:") {
          mtotal = stof(v);
        }

        if (k == "MemFree:") {
          mfree = stof(v);
          
        }
      }
    }
    if (mfree && mtotal) {
      return (mtotal - mfree) / mtotal;
    }
  }
  
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::ifstream inputFileStream(kProcDirectory + kUptimeFilename);
  if (inputFileStream.is_open()) {
    string line;
    while (std::getline(inputFileStream, line)) {
      std::istringstream inputFileLineStream(line);
      string totalTime;
      inputFileLineStream >> totalTime;
      return stol(totalTime);
    }
  }
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line;
  string value;
  vector<string> cpuInfo;
  std::ifstream procStatFilestream(kProcDirectory + kStatFilename);
  
  if (procStatFilestream.is_open()) {
    
    std::getline(procStatFilestream, line);
    std::istringstream procStatLinestream(line);
  
    while (procStatLinestream >> value) {
      if (value != "cpu"){
        cpuInfo.emplace_back(value);
      }
    }

  }
  return cpuInfo;
}

float LinuxParser::ParseKVFile(string fileName, string key) {
  std::ifstream inputFileStream(fileName);
  if (inputFileStream.is_open()) {
    string line;
    while (std::getline(inputFileStream, line)) {
      std::istringstream inputFileLineStream(line);
      string k;
      string v;
      while (inputFileLineStream >> k >> v) {
        
        if (k == key) {
          return stof(v);
        }

      }
    }
  }
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  return LinuxParser::ParseKVFile(kProcDirectory + kStatFilename, "processes");
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  return LinuxParser::ParseKVFile(kProcDirectory + kStatFilename, "procs_running");
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) { return string(); }

