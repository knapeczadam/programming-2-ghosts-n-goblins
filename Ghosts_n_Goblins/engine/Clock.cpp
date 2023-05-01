#include "pch.h"
#include "Clock.h"

float Clock::s_AccuTime{};

Clock::Clock(float seconds)
    : m_TotalTime{seconds}
    , m_StartTime{s_AccuTime}
{
}

void Clock::Update(float elapsedSec)
{
    s_AccuTime += elapsedSec;
}

bool Clock::IsFinished() const
{
    return s_AccuTime - m_StartTime >= m_TotalTime;
}
