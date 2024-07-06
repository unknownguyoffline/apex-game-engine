#include "timer.hpp"

void Timer::start()
{
    m_start = std::chrono::high_resolution_clock::now();
}
void Timer::end()
{
    m_end = std::chrono::high_resolution_clock::now();
    m_duration = m_end - m_start;
}
float Timer::getDuration()
{
    return m_duration.count();
}

float Timer::getElapsedTime()
{
    std::chrono::duration<float> dur = std::chrono::high_resolution_clock::now() - m_start;
    return dur.count();
}
