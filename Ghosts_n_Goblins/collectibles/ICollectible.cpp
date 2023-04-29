#include "pch.h"
#include "ICollectible.h"

int ICollectible::GetScore() const
{
    return m_Score;
}

void ICollectible::SetScore(int score)
{
    score = m_Score;
}
