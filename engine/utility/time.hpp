#pragma once
#include <chrono>

struct Time
{
    unsigned short nanosecond = 0;
    unsigned short millisecond = 0;
    unsigned char second = 0;
    unsigned char minute = 0;
    unsigned char hour = 0;
    unsigned char day = 0;
    unsigned char month = 0;
    unsigned short year = 0;
};

// Time getCurrentTime()
// {
// }

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
