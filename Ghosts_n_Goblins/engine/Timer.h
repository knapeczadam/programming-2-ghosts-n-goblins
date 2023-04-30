#pragma once

class Timer
{
public:
   explicit Timer(float seconds);
   ~Timer() = default;
   Timer(const Timer& other) = delete;
   Timer(Timer&& other) noexcept = delete;
   Timer& operator=(const Timer& other) = delete;
   Timer& operator=(Timer&& other) noexcept = delete;
   
   static void Update(float elapsedSec);
   bool IsFinished() const;
   
private:
   static float s_AccuTime; // accumulated time in seconds
   const float m_TotalTime; // total time in seconds
   const float m_StartTime; // time in seconds when the timer started
};
