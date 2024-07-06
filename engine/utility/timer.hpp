#pragma once
#include <chrono>

class Timer
{
  public:
    void start();
    void end();
    float getDuration();
    float getElapsedTime();

  private:
    bool m_hasTimerStoped = false;
    std::chrono::duration<float> m_duration;
    std::chrono::system_clock::time_point m_start;
    std::chrono::system_clock::time_point m_end;
};
