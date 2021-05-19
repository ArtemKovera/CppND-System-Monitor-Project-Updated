#include "processor.h"
#include "linux_parser.h"
#include <unistd.h>
#include <fstream>
#include <sstream>
  
using namespace LinuxParser;

// TODO: Return the aggregate CPU utilization
//returns 0 if the file is unable to be open
float Processor::Utilization()
{   
    std::ifstream file(kProcDirectory + kStatFilename);

    if(file.is_open())
    {
        int total = 0;
        int jiffyComponent;
        int idle;
        int column = 0;
        float idleFruction;
        std::string line;

        std::getline(file, line);
        line.erase(0, 5);
        std::istringstream stream(line);
        
        
        while(stream >> jiffyComponent)
        {
            total += jiffyComponent;
            column++;
            if(column==4)
                idle = jiffyComponent;

        }
        
        idleFruction = (float)idle/total;

        return (1.0 - idleFruction);        
    }
    else
    {
        return 0.0;
    }
      
}