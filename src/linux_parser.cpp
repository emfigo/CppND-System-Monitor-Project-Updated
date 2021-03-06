#include <dirent.h>
#include <unistd.h>
#include <math.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::stoi;
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
  string os, version, kernel;
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

string LinuxParser::GetValueKeyValueTypeFile(string const fileName, string keyName) {
  string line;
  string key, value;

  std::ifstream filestream(fileName);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == keyName) {
          return value;
        }
      }
    }
  }
  return value;
}

float LinuxParser::MemoryUtilization() { 
  string fileName = kProcDirectory + kMeminfoFilename;
  float totalMemory = stof(LinuxParser::GetValueKeyValueTypeFile(fileName, "MemTotal:"));

  fileName = kProcDirectory + kMeminfoFilename;
  float freeMemory = stof(LinuxParser::GetValueKeyValueTypeFile(fileName, "MemFree:"));

  return freeMemory / totalMemory; 
}

long LinuxParser::UpTime() { 
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

vector<string> LinuxParser::CpuUtilization() { 
  vector<string> output{};
  string key, time;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> key;
    if (key == "cpu") {
      while (linestream >> time) {
        output.push_back(time);
      }
    }
  }
  return output;
}

int LinuxParser::TotalProcesses() { 
  string fileName = kProcDirectory + kStatFilename;

  return stoi(LinuxParser::GetValueKeyValueTypeFile(fileName, "processes"));
}

int LinuxParser::RunningProcesses() { 
  string line;
  string firstKey, secKey;
  int value = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), '_', ' ');
      std::istringstream linestream(line);
      linestream >> firstKey >> secKey >> value;
      if ((firstKey == "procs") && (secKey == "running")){
        return value;
      }
    }
  }
  return value;
}

////////////////////////////////////////////
////// Associated with a process //////////
///////////////////////////////////////////

vector<int> LinuxParser::CpuUtilization(int pid) { 
  vector<int> output{};
  string time;
  string line;
  int counter = 1;
  std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> time) {
      if(((counter >= 14) && (counter <= 17)) || (counter == 22)){
        output.push_back(stoi(time));
      }
      counter++;
    }
  }
  return output;
}

string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
  }
  return line;
}

string LinuxParser::Ram(int pid) { 
  string fileName = kProcDirectory + "/" + to_string(pid) + kStatusFilename;

  return LinuxParser::GetValueKeyValueTypeFile(fileName, "VmSize:");
}

string LinuxParser::Uid(int pid) { 
  string fileName = kProcDirectory + "/" + to_string(pid) + kStatusFilename;

  return LinuxParser::GetValueKeyValueTypeFile(fileName, "Uid:");
}

string LinuxParser::User(int pid) { 
  string line;
  string uid = LinuxParser::Uid(pid);
  string userName, priv, userUid;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> userName >> priv >> userUid) {
        if (userUid == uid) {
          return userName;
        }
      }
    }
  }
  return userName;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
