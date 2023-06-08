#pragma once
#include "Vector2f.h"

class IThrowable
{
public:
    explicit IThrowable();
    virtual ~IThrowable() = default;
    IThrowable(const IThrowable& other) = delete;
    IThrowable(IThrowable&& other) noexcept = delete;
    IThrowable& operator=(const IThrowable& other) = delete;
    IThrowable& operator=(IThrowable&& other) noexcept = delete;

    virtual void SetDirection(const Vector2f& direction) final;

protected:
    Point2f m_OriginalPos;
    Vector2f m_Direction;
    Vector2f m_Speed;
    float m_Angle;
    float m_AccuTime;
};
