#include "pch.h"
#include "Timer.h"

float Timer::s_AccuTime{};

Timer::Timer(float seconds)
    : m_TotalTime{seconds}
    , m_StartTime{s_AccuTime}
{
}

void Timer::Update(float elapsedSec)
{
    s_AccuTime += elapsedSec;
}

bool Timer::IsFinished() const
{
    return s_AccuTime - m_StartTime >= m_TotalTime;
}
