#include "pch.h"
#include "LadderDeactivator.h"

#include "characters/Player.h"

LadderDeactivator::LadderDeactivator(const Rectf& shape, GameController* pGameController)
    : ICollider{Game::Label::L_LADDER_DEACTIVATOR, shape, pGameController}
{
}

void LadderDeactivator::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    Player* pPlayer{static_cast<Player*>(other)};
    pPlayer->CanClimb(false);
    pPlayer->SetOnLadder(false);
}
