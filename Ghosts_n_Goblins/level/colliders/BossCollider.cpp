#include "pch.h"
#include "BossCollider.h"

BossCollider::BossCollider(const Rectf& shape, GameController* pGameController)
    : ICollider{Game::Label::L_BOSS, shape, pGameController}
{
    m_ColliderColor = Color4f{0.83f, 0.0f, 0.32f, 1.0f};
}

void BossCollider::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    m_Active = false;
}
