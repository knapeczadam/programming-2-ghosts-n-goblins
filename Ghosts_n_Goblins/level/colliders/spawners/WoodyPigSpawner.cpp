#include "pch.h"
#include "WoodyPigSpawner.h"

#include "characters/IEnemy.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"
#include "game/GameObject.h"
#include "game/PlayerManager.h"

WoodyPigSpawner::WoodyPigSpawner(const Rectf& shape, GameController* pGameController)
    : ISpawner{Game::Label::L_WOODY_PIG, shape, pGameController}
{
}

void WoodyPigSpawner::Spawn()
{
    if (not IsPlayerBetweenBoundaries()) return;

    for (GameObject* pGameObject : m_pGameController->m_pEnemyManager->GetWoodyPigs())
    {
        if (not pGameObject->IsActive())
        {
            IEnemy* pEnemy{static_cast<IEnemy*>(pGameObject)};
            std::uniform_real_distribution<float> time{0.0f, 4.0f};
            StartTimer(time(Game::GetRandomGenerator()));
            if (IsTimerFinished())
            {
                Point2f pos;
                pEnemy->SetSpawnPosition(pos);
                pGameObject->Reset();
                return;
            }
        }
    }
}
