#pragma once

class Clock;

class Timer
{
public:
    explicit Timer();
    virtual ~Timer() = default;
    Timer(const Timer& other) = delete;
    Timer(Timer&& other) noexcept = delete;
    Timer& operator=(const Timer& other) = delete;
    Timer& operator=(Timer&& other) noexcept = delete;

protected:
    virtual void StartTimer(float seconds) final;
    virtual bool IsTimerFinished() final;
    virtual int GetSeconds() const final;
    virtual int GetMinutes() const final;
public:
private:
    Clock* m_pClock;
    
};
