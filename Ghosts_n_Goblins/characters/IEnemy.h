#pragma once

class IEnemy
{
public:
    IEnemy() = default;
    virtual ~IEnemy() = default;
    IEnemy(const IEnemy& other) = delete;
    IEnemy(IEnemy&& other) noexcept = delete;
    IEnemy& operator=(const IEnemy& other) = delete;
    IEnemy& operator=(IEnemy&& other) noexcept = delete;

    inline void SetTarget(const Point2f& target) { m_Target = target; }
protected:
    Point2f m_Target;
};
