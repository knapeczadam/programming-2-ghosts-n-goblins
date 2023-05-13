#include "pch.h"
#include "ZombieSpawner.h"

#include "game/GameObject.h"
#include "game/GameController.h"
#include "characters/Player.h"
#include "characters/IEnemy.h"
#include "characters/Zombie.h"
#include "game/EnemyManager.h"
#include "game/PlayerManager.h"

ZombieSpawner::ZombieSpawner(const Rectf& boundaries, GameController* pGameController)
    : ISpawner{boundaries, pGameController}
      , m_MinRange{66.0f}
      , m_MaxRange{208.0f}
{
}

void ZombieSpawner::Spawn()
{
    if (not IsPlayerBetweenBoundaries()) return;

    for (GameObject* pEnemy : m_pGameController->m_pEnemyManager->GetZombies())
    {
        if (not pEnemy->IsActive())
        {
            // const int time{std::rand() % 4 + 1};
            std::uniform_real_distribution<float> time{0.0f, 5.0f};
            StartTimer(time(Game::mt));
            if (IsTimerFinished())
            {
            const Point2f playerCenter{m_pGameController->m_pPlayerManager->GetPlayer()->GetCollisionBoxCenter()};
                const int flip{std::rand() % 2 - 1};
                // const int offset{(std::rand() % (m_MaxRange - m_MinRange) + m_MinRange) * flip};
                std::uniform_real_distribution<float> offset{m_MinRange, m_MaxRange};
                const Point2f pos{Point2f{playerCenter.x + offset(Game::mt) * flip, 62.0f}};
                Zombie* pZombie{static_cast<Zombie*>(pEnemy)};
                pZombie->Reset(pos);
                return;
            }
        }
    }
}
