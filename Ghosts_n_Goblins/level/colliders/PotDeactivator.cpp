#include "pch.h"
#include "PotDeactivator.h"

#include "game/CollectibleManager.h"
#include "game/GameController.h"

PotDeactivator::PotDeactivator(const Rectf& boundaries, GameController* pGameController)
    : ICollider{Game::Label::L_POT,  boundaries, pGameController }
{
}

void PotDeactivator::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    m_pGameController->m_pCollectibleManager->DeactivateContent();
}
