#ifndef TIMER
#define TIMER

#include <chrono>
#include <iostream>
#include <vector>

class Timer
{
public:
    Timer(double& timeSum);
    ~Timer();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
    double& m_timeSum;
};

#endif