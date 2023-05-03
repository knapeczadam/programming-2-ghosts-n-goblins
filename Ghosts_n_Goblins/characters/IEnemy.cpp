#include "pch.h"
#include "IEnemy.h"

IEnemy::IEnemy()
    : m_Target{}
    , m_Score{}
    , m_Health{}
{
}

void IEnemy::SetTarget(const Point2f& target)
{
    m_Target = target;
}
