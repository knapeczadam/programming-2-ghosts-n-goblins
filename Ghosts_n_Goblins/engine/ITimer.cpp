#include "pch.h"
#include "ITimer.h"

#include "Clock.h"

#include <numeric>

ITimer::ITimer()
    : m_pClock{nullptr}
{
}

ITimer::~ITimer()
{
    delete m_pClock;
}

void ITimer::StartTimer(float seconds)
{
    if (m_pClock) return;
    m_pClock = new Clock{seconds};
}

void ITimer::ResetTimer()
{
    delete m_pClock;
}

bool ITimer::IsTimerFinished()
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

int ITimer::GetSeconds() const
{
    if (not m_pClock) return 0;
    return int(m_pClock->GetRemainingTime()) % 60;
}

int ITimer::GetMinutes() const
{
    if (not m_pClock) return 0;
    return m_pClock->GetRemainingTime() / 60;
}

float ITimer::GetRemainingTime() const
{
    if (not m_pClock) return std::numeric_limits<float>::max();
    return m_pClock->GetRemainingTime();
}
