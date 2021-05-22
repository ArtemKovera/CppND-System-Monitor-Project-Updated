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

// TODO: Read and return the system memory utilization
// returns 0 if file is unable to open
float LinuxParser::MemoryUtilization()
{
    std::ifstream file(kProcDirectory + kMeminfoFilename);

    
    if(file.is_open()) 
    {   
        float totalMemory;
        float freeMemory;
        float value;
        string line;
        string key;
        
        while (std::getline(file, line)) 
        {
            std::istringstream lineStream(line);
            while(lineStream >> key >> value) 
            {
                if(key == "MemTotal:") 
                {
                    totalMemory = value;
                }
                else if(key == "MemFree:") 
                {
                    freeMemory = value;
                }
            }
        }

        file.close();
        return (totalMemory - freeMemory) / totalMemory;     
    }
    else
    {
        return 0;
    }
    
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime()
{ 

    std::ifstream file (kProcDirectory + kUptimeFilename);
    if(file.is_open())
    {
        string line;
        std::getline(file, line);

        if(line == "")
            return 0;
        
        return stol(line);
    }
    
    return 0;
} 

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
// returns 0 if the file is unable to open or information is not found 
int LinuxParser::TotalProcesses() 
{ 
    std::ifstream file(kProcDirectory + kStatFilename);

    if(file.is_open())
    {
        int totalProcesses;
        string line;
        bool found = false;

        while(std::getline(file, line) && !found)
        {
            if(line.find("processes") != string::npos)
            {   
                found = true;
                const char * str = line.c_str();
                totalProcesses = atoi(str+10); 
                return totalProcesses;
            }
        }

    }
    else
    {
        return 0;
    }
    return 0;
}

// TODO: Read and return the number of running processes
// returns 0 if the file is unable to open or information is not found 
int LinuxParser::RunningProcesses() 
{ 
    std::ifstream file(kProcDirectory + kStatFilename);

    if(file.is_open())
    {
        int runningProcesses;
        string line;
        bool found = false;

        while(std::getline(file, line) && !found)
        {
            if(line.find("procs_running") != string::npos)
            {   
                found = true;
                const char * str = line.c_str();
                runningProcesses = atoi(str+14); 
                return runningProcesses;
            }
        }

    }
    else
    {
        return 0;
    }
    return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid)
{ 
    std::ifstream file(kProcDirectory + to_string(pid) + kCmdlineFilename);
    if(file.is_open())
    {
        std::string line;
        std::getline(file, line);
        file.close();
        return line; 
    }
    else
    {
        return "";
    } 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) 
{ 

    std::ifstream file(kProcDirectory + to_string(pid) + kStatusFilename);
    if(file.is_open())
    {
        std::string key, line, value, uid;
        bool found = false;
        while(std::getline(file, line) && !found)
        {
            std::istringstream stream(line);
            while(stream >> key >> value)
            {
                if(key == "Uid:")
                {
                    uid = value;
                    found = true;
                }
                   
            }
        }

        return uid;
    }
    else
    {
        return "";
    }
    
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid)
{ 
    std::ifstream file(kPasswordPath);
    if(file.is_open())
    {
        string line, key, x, value, user; 
        bool found = false;
        string uid = Uid(pid);
        while(std::getline(file, line) && !found)
        {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream stream(line);
            while(stream >> key >> x >> value)
            if(value == uid)
            {
                user = key;
                found = true;
            }
        }

        return user;
    }
    else
    {
        return "";
    }
    
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) 
{ 
    std::ifstream file(kProcDirectory + std::to_string(pid) + kUptimeFilename);
    if(file.is_open())
    {
        string line; 
        std::getline(file, line);
        if(line == "")
            return 0;
        
        return stol(line);
    }
    
    return 0;
}
