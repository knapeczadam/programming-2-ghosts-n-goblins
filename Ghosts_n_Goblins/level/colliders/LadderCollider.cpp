#include "pch.h"
#include "LadderCollider.h"

#include "characters/Player.h"

LadderCollider::LadderCollider(const Rectf& shape, GameController* pGameController)
    : ICollider{Game::Label::L_LADDER, shape, pGameController}
{
}

void LadderCollider::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    Player* pPlayer = static_cast<Player*>(other);
    if (pPlayer->IsClimbing())
    {
        pPlayer->SetOnLadder(true);
    }
}
