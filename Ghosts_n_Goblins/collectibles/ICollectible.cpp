#include "pch.h"
#include "ICollectible.h"

ICollectible::ICollectible()
    : m_Score{0}
{
}

int ICollectible::GetScore() const
{
    return m_Score;
}

void ICollectible::SetScore(int score)
{
    m_Score = score;
}
