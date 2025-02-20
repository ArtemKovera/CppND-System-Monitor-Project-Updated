#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"


using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() 
{   
    const vector<int>& pids = LinuxParser::Pids();
    processes_.clear(); 
    for (int pid : pids)
    {
        Process process(pid);
        processes_.push_back(process);
    }

    std::sort(processes_.begin(), processes_.end());
    
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() 
{ 
    return LinuxParser::Kernel();
}

// TODO: Return the system's memory utilization
// returns 0 if the file is unable to open or information is not found 
float System::MemoryUtilization() 
{ 
    return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem() 
{ 
    return LinuxParser::OperatingSystem(); 
}

// TODO: Return the number of processes actively running on the system
// returns 0 if the file is unable to open or information is not found 
int System::RunningProcesses() 
{  
    return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
// returns 0 if the file is unable to open 
int System::TotalProcesses() 
{ 
    return LinuxParser::TotalProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() 
{ 
    return LinuxParser::UpTime();    
}