#include "pch.h"
#include "WoodyPigSpawner.h"

#include "characters/IEnemy.h"
#include "characters/Player.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"
#include "game/GameObject.h"
#include "game/LevelManager.h"
#include "game/PlayerManager.h"

WoodyPigSpawner::WoodyPigSpawner(const Rectf& shape, GameController* pGameController)
    : ISpawner{Game::Label::L_WOODY_PIG, shape, pGameController}
    , m_MinRange{66.0f}
    , m_MaxRange{208.0f}
{
}

void WoodyPigSpawner::Spawn()
{
    if (not IsPlayerBetweenBoundaries()) return;
    if (m_pGameController->m_pEnemyManager->GetUnicorn()->IsAwake()) return;

    for (GameObject* pGameObject : m_pGameController->m_pEnemyManager->GetWoodyPigs())
    {
        if (not pGameObject->IsActive())
        {
            IEnemy* pEnemy{static_cast<IEnemy*>(pGameObject)};
            StartTimer(Game::GetRandomFloat(0.0f, 2.0f));
            if (IsTimerFinished())
            {
                Player* pPlayer{m_pGameController->m_pPlayerManager->GetPlayer()};
                const Point2f playerCenter{pPlayer->GetColliderCenter()};
                const int flip{Game::GetRandomBool() ? -1 : 1};
                const float offset{30.0f};
                Point2f pos;
                pos.x = playerCenter.x + Game::GetRandomFloat(m_MinRange, m_MaxRange) * flip;
                pos.y = Game::GetRandomFloat(LevelManager::GetGroundHeight() + offset, LevelManager::GetHillHeight());
                pEnemy->SetSpawnPosition(pos);
                pEnemy->SetPosition(pos);
                pEnemy->Reset();
                return;
            }
        }
    }
}
