#include "processor.h"
#include "linux_parser.h"
#include <sstream>
#include <vector>
#include <string>

using std::string;
using std::vector;


float Processor::Utilization() { 
    vector<string> cpuInfo = LinuxParser::CpuUtilization();
    
    float user = stof(cpuInfo[1]);    
    float nice = stof(cpuInfo[2]);   
    float system = stof(cpuInfo[3]);  
    float idle = stof(cpuInfo[4]);      
    float iowait = stof(cpuInfo[5]); 
    float irq = stof(cpuInfo[6]);   
    float softirq = stof(cpuInfo[7]);  
    float steal = stof(cpuInfo[8]);  
    float guest = stof(cpuInfo[9]);  
    float guest_nice = stof(cpuInfo[10]);

    float PrevIdle = previdle + previowait;
    float Idle = idle + iowait;

    float PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
    float NonIdle = user + nice + system + irq + softirq + steal;

    float PrevTotal = PrevIdle + PrevNonIdle;
    float Total = Idle + NonIdle;

    // differentiate: actual value minus the previous one
    float totald = Total - PrevTotal;
    float idled = Idle - PrevIdle;

    prevuser = user;
    prevnice = nice;
    prevsystem = system;
    previdle = idle;
    previowait = iowait;
    previrq = irq;
    prevsoftirq = softirq;
    prevsteal = steal;
    prevguest = guest;
    prevguest_nice = guest_nice;

    return (totald - idled)/totald;
 }