// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "TimerHR.hpp"

TimerHR::TimerHR() {
    // Initialize so we always get a valid read
    TimerHR::Start();
    m_mark = m_start;
}

void TimerHR::Start() {
    m_start = std::chrono::high_resolution_clock::now();
}

float TimerHR::StartMS() {
    float retVal = MarkMS();

    m_start = m_mark;

    return retVal;
}

void TimerHR::Mark() {
    m_mark = std::chrono::high_resolution_clock::now();
}

long long TimerHR::MarkUS() {
    Mark();

    return std::chrono::duration_cast<std::chrono::microseconds>(m_mark - m_start).count();
}

float TimerHR::MarkMS() {
    Mark();

    return std::chrono::duration<float, std::milli>(m_mark - m_start).count();
}

long long TimerHR::US() const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(m_mark - m_start).count();
}

float TimerHR::MS() const
{
    return std::chrono::duration<float, std::milli>(m_mark - m_start).count();
}