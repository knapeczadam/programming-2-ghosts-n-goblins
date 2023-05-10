#pragma once

class Clock;

class ITimer
{
public:
    explicit ITimer();
    virtual ~ITimer();
    ITimer(const ITimer& other) = delete;
    ITimer(ITimer&& other) noexcept = delete;
    ITimer& operator=(const ITimer& other) = delete;
    ITimer& operator=(ITimer&& other) noexcept = delete;

protected:
    virtual void StartTimer(float seconds) final;
    virtual void ResetTimer() final;
    virtual bool IsTimerFinished() final;
    virtual int GetSeconds() const final;
    virtual int GetMinutes() const final;
    virtual float GetRemainingTime() const final;
private:
    Clock* m_pClock;
};
