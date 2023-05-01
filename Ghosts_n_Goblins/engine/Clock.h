#pragma once

class Clock final
{
public:
   explicit Clock(float seconds);
   ~Clock() = default;
   Clock(const Clock& other) = delete;
   Clock(Clock&& other) noexcept = delete;
   Clock& operator=(const Clock& other) = delete;
   Clock& operator=(Clock&& other) noexcept = delete;
   
   static void Update(float elapsedSec);
   bool IsFinished() const;
   
private:
   static float s_AccuTime; // accumulated time in seconds
   const float m_TotalTime; // total time in seconds
   const float m_StartTime; // time in seconds when the timer started
};
