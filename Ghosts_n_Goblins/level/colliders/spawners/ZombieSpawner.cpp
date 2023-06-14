﻿#include "pch.h"
#include "ZombieSpawner.h"

#include "game/GameObject.h"
#include "game/GameController.h"
#include "characters/Player.h"
#include "engine/SoundManager.h"
#include "game/EnemyManager.h"
#include "game/LevelManager.h"
#include "game/PlayerManager.h"

ZombieSpawner::ZombieSpawner(const Rectf& shape, GameController* pGameController)
    : ISpawner{Game::Label::L_ZOMBIE, shape, pGameController}
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
            StartTimer(Game::GetRandomFloat(0.0f, 2.0f));
            if (IsTimerFinished())
            {
                Player* pPlayer{m_pGameController->m_pPlayerManager->GetPlayer()};
                const Point2f playerCenter{pPlayer->GetColliderCenter()};
                const int flip{Game::GetRandomBool() ? -1 : 1};
                RandomizePosition(pEnemy);
                pEnemy->Reset();
                m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ZOMBIE_SPAWN);
                return;
            }
        }
    }
}

void ZombieSpawner::RandomizePosition(GameObject* pEnemy) const
{
    Player* pPlayer{m_pGameController->m_pPlayerManager->GetPlayer()};
    const Point2f playerCenter{pPlayer->GetColliderCenter()};
    const int flip{Game::GetRandomBool() ? -1 : 1};
    Point2f pos;
    const int offsetMultiplier{3};
    if (pPlayer->IsOnHill())
    {
        pos.x = playerCenter.x + Game::GetRandomFloat(m_MinRange, m_MaxRange) * flip;
        const float hillStart{LevelManager::GetHillStart() + pEnemy->GetCollider().width * offsetMultiplier};
        const float hillEnd{LevelManager::GetHillEnd() - pEnemy->GetCollider().width * offsetMultiplier};
        if (pos.x < hillStart)
        {
            pos.x = hillStart;
        }
        else if (pos.x + pEnemy->GetCollider().width > hillEnd)
        {
            pos.x = hillEnd;
        }
        pos.y = LevelManager::GetHillHeight();
    }
    else
    {
        pos.x = playerCenter.x + Game::GetRandomFloat(m_MinRange, m_MaxRange) * flip;
        pos.y = LevelManager::GetGroundHeight();
    }
    pEnemy->SetPosition(pos);
}
