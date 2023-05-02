#include "pch.h"
#include "Timer.h"
#include "Clock.h"

Timer::Timer()
    : m_pClock{}
{
}

Timer::~Timer()
{
    delete m_pClock;
}

void Timer::StartTimer(float seconds)
{
    if (m_pClock) return;
    m_pClock = new Clock{seconds};
}

bool Timer::IsTimerFinished()
{
    if (not m_pClock) return true;
    if (m_pClock->IsFinished())
    {
        delete m_pClock;
        m_pClock = nullptr;
        return true;
    }
    return false;
}

int Timer::GetSeconds() const
{
    if (not m_pClock) return 0;
    return int(m_pClock->GetRemainingTime()) % 60;
}

int Timer::GetMinutes() const
{
    if (not m_pClock) return 0;
    return m_pClock->GetRemainingTime() / 60;
}
