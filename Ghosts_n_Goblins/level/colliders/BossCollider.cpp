#include "pch.h"
#include "BossCollider.h"

BossCollider::BossCollider(const Rectf& shape, GameController* pGameController)
    : ICollider{Game::Label::L_BOSS, shape, pGameController}
{
}

void BossCollider::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    m_Active = false;
}
