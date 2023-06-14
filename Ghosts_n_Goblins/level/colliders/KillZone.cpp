#include "pch.h"
#include "KillZone.h"

#include "characters/Player.h"

KillZone::KillZone(const Rectf& shape, GameController* pGameController)
    : ICollider{Game::Label::L_KILLZONE, shape, pGameController}
{
    m_ColliderColor = Color4f{1.0f, 0.0f, 0.0f, 1.0f};
}

void KillZone::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    Player* pPlayer = static_cast<Player*>(other);
    pPlayer->Die();
    m_Active = false;
}
