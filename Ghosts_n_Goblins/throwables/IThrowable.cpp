#include "pch.h"
#include "IThrowable.h"


IThrowable::IThrowable()
    : m_Direction{}
    , m_Speed{ 0.0f }
{
}

void IThrowable::SetDirection(const Vector2f& direction)
{
    m_Direction = direction;
}
