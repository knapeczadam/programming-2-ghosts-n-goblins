#include "pch.h"
#include "ISpawner.h"

#include "characters/Player.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"

ISpawner::ISpawner(const Rectf& boundaries, GameController* pGameController)
    : m_SpawnBoundaries{boundaries}
      , m_SpawnPos{0, 0}
      , m_pGameController{pGameController}
{
}

bool ISpawner::IsPlayerBetweenBoundaries() const
{
    const float colliderLeft{m_pGameController->m_pPlayerManager->GetPlayer()->GetCollider().left};
    const float colliderWidth{m_pGameController->m_pPlayerManager->GetPlayer()->GetCollider().width};
    return colliderLeft > m_SpawnBoundaries.left and colliderLeft + colliderWidth < m_SpawnBoundaries.left + m_SpawnBoundaries.width;
}
