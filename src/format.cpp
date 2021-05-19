#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function

string Format::ElapsedTime(long seconds) 
{
    int minutes = seconds/60; 
    int hours = minutes/60;

    string strSec, strMin, strHour;

    if(hours < 10)
        strHour = "0" + std::to_string(hours);
    else    
        strHour = std::to_string(hours);
    
    if(minutes%60 < 10)
        strMin = "0" + std::to_string(minutes%60);
    else    
        strMin = std::to_string(minutes%60);
    
    if(seconds%60 < 10)
        strSec = "0" + std::to_string(seconds%60);
    else    
        strSec = std::to_string(seconds%60);
    
    return strHour + ":" + strMin + ":" + strSec;
         
}

