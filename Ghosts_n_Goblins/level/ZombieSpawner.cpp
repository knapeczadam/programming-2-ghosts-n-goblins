#include "pch.h"
#include "ZombieSpawner.h"

#include "game/GameObject.h"
#include "game/GameController.h"
#include "characters/Player.h"
#include "characters/IEnemy.h"
#include "game/EnemyManager.h"
#include "game/PlayerManager.h"

ZombieSpawner::ZombieSpawner(const Rectf& boundaries, GameController* pGameController)
    : ISpawner{boundaries, pGameController}
      , range{200}
{
}

void ZombieSpawner::Spawn()
{
    if (not IsPlayerBetweenBoundaries()) return;
    
    const Point2f playerCenter{m_pGameController->m_pPlayerManager->GetPlayer()->GetCollisionBoxCenter()};
    for (GameObject* pZombie : m_pGameController->m_pEnemyManager->GetZombies())
    {
        if (not pZombie->IsActive())
        {
            const int time{std::rand() % 2 + 1};
            StartTimer(time);
            if (IsTimerFinished())
            {
                const int offset{std::rand() % (range * 2 + 1) - range};
                pZombie->SetPosition(Point2f{playerCenter.x + offset, 62.0f});
                pZombie->SetActive(true);
                pZombie->SetVisible(true);
                IEnemy* pEnemy{static_cast<IEnemy*>(pZombie)};
                pEnemy->SetAwake(true);
                pEnemy->ResetHP();
                return;
            }
        }
    }
}
