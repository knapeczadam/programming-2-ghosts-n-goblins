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
    const float playerCollisionLeft{m_pGameController->m_pPlayerManager->GetPlayer()->GetCollisionBox().left};
    const float playerCollisionWidth{m_pGameController->m_pPlayerManager->GetPlayer()->GetCollisionBox().width};
    return playerCollisionLeft > m_SpawnBoundaries.left and
        playerCollisionLeft + playerCollisionWidth < m_SpawnBoundaries.left + m_SpawnBoundaries.width;
}
