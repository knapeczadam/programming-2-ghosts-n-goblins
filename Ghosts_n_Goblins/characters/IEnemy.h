#pragma once

class IEnemy
{
public:
    IEnemy();
    virtual ~IEnemy() = default;
    IEnemy(const IEnemy& other) = delete;
    IEnemy(IEnemy&& other) noexcept = delete;
    IEnemy& operator=(const IEnemy& other) = delete;
    IEnemy& operator=(IEnemy&& other) noexcept = delete;

    virtual void SetTarget(const Point2f& target) final;
protected:
    Point2f m_Target;
    int m_Score;
    int m_Health;
};
