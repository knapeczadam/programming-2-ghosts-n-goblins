#include "pch.h"
#include "Clock.h"
#include <iostream>

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

float Clock::GetRemainingTime() const
{
    return m_TotalTime - (s_AccuTime - m_StartTime);
}
