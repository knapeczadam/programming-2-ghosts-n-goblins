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
    m_pClock = nullptr;
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

/**
 * \return Remaining time in seconds
 */
float ITimer::GetRemainingTime() const
{
    if (not m_pClock) return std::numeric_limits<float>::max();
    return m_pClock->GetRemainingTime();
}

/**
 * \param time in seconds
 * \return Time struct ex: 1:59 -> {firstDigit: 9, secondDigit: 5, thirdDigit: 1}
 */
Time ITimer::GetRemainingTimeDigits(int time)
{
    StartTimer(time);
    const int seconds{GetSeconds()};
    const int minutes{GetMinutes()};

    int firstDigit, secondDigit, thirdDigit;
    thirdDigit = minutes;
    if (seconds > 9)
    {
        secondDigit = seconds / 10;
        firstDigit = seconds % 10;
    }
    else
    {
        secondDigit = 0;
        firstDigit = seconds;
    }
    return Time{firstDigit, secondDigit, thirdDigit};
}
