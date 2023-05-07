#include "pch.h"
#include "Spawner.h"

#include "GameController.h"
#include "characters/Player.h"

Spawner::Spawner(const Rectf& boundaries, GameController* pGameController)
    : m_SpawnBoundaries{boundaries}
      , m_SpawnPos{0, 0}
      , m_pGameController{pGameController}
{
}

bool Spawner::IsPlayerBetwwenBoundaries() const
{
    const float playerCollisionLeft{m_pGameController->m_pPlayer->GetCollisionBox().left};
    const float playerCollisionWidth{m_pGameController->m_pPlayer->GetCollisionBox().width};
    return playerCollisionLeft > m_SpawnBoundaries.left and
        playerCollisionLeft + playerCollisionWidth < m_SpawnBoundaries.left + m_SpawnBoundaries.width;
}
