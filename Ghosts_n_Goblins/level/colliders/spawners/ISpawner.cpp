#include "pch.h"
#include "ISpawner.h"

#include "characters/Player.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"

ISpawner::ISpawner(Game::Label label, const Rectf& shape, GameController* pGameController)
    : ICollider(label, shape, pGameController)
{
}

bool ISpawner::IsPlayerBetweenBoundaries() const
{
    const float colliderLeft{m_pGameController->m_pPlayerManager->GetPlayer()->GetCollider().left};
    const float colliderWidth{m_pGameController->m_pPlayerManager->GetPlayer()->GetCollider().width};
    return colliderLeft > m_Shape.left and colliderLeft + colliderWidth < m_Shape.left + m_Shape.width;
}
