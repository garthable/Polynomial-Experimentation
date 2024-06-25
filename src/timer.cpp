#include <chrono>
#include <iostream>
#include <vector>

#include "../inc/timer.hpp"

Timer::Timer(double& timeSum) :
    m_timeSum {timeSum}
{
    m_startTimePoint = std::chrono::high_resolution_clock::now();
}
Timer::~Timer()
{
    auto endTime = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();
    auto duration = end - start;
    double ms = duration * 0.001;
    m_timeSum += ms;
}