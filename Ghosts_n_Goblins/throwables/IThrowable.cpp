#include "pch.h"
#include "IThrowable.h"


IThrowable::IThrowable()
    : m_OriginalPos{0.0f, 0.0f}
    , m_Direction{0.0f, 0.0f}
    , m_Speed{ 0.0f, 0.0f }
    , m_Angle{0.0f}
    , m_AccuTime{0.0f}
{
}

void IThrowable::SetDirection(const Vector2f& direction)
{
    m_Direction = direction;
}
