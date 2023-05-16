#include "pch.h"
#include "LadderActivator.h"

#include "characters/Player.h"

LadderActivator::LadderActivator(const Rectf& shape, GameController* pGameController)
    : ICollider{Game::Label::L_LADDER_ACTIVATOR, shape, pGameController}
{
    m_ColliderColor = Color4f{0.69f, 0.38f, 0.26f, 1.0f};
}

void LadderActivator::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    Player* pPlayer{static_cast<Player*>(other)};
    pPlayer->CanClimb(true);
}
