﻿#include "pch.h"
#include "FlyingKnightSpawner.h"

#include "characters/FlyingKnight.h"
#include "characters/IEnemy.h"
#include "characters/Player.h"
#include "engine/SoundManager.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"
#include "game/GameObject.h"
#include "game/PlayerManager.h"

FlyingKnightSpawner::FlyingKnightSpawner(const Rectf& shape, GameController* pGameController)
    : ISpawner{Game::Label::L_FLYING_KNIGHT, shape, pGameController}
    , m_HorOffset{290.0f}
    , m_VerOffset{224.0f}
    , m_CurrVerOffset{}
    , m_Range{50.0f}
    , m_KnightCount{0}
    , m_MaxKnights{3}
{
}

void FlyingKnightSpawner::Spawn()
{
    if (not IsPlayerBetweenBoundaries())return;

    for (GameObject* pEnemy : m_pGameController->m_pEnemyManager->GetFlyingKnights())
    {
        if (not pEnemy->IsActive())
        {
            StartTimer(Game::GetRandomFloat(1.0f, 2.0f));
            if (IsTimerFinished())
            {
                FlyingKnight* pKnight{static_cast<FlyingKnight*>(pEnemy)};
                if (++m_KnightCount % m_MaxKnights == 0)
                {
                    m_CurrVerOffset = Game::GetRandomFloat(m_Range, m_Range * 2.0f) - m_Range;
                }
                pKnight->SetCycleOffset(Game::GetRandomFloat(3.0f, 10.0f));
                Point2f pos;
                pos.x = m_pGameController->m_pPlayerManager->GetPlayer()->GetPosition<Point2f>().x + m_HorOffset;
                pos.y = m_VerOffset + m_CurrVerOffset;
                pKnight->SetPosition(Point2f{pos.x, 0.0f});
                pKnight->SetSpawnPosition(Point2f{0.0f, pos.y});
                pKnight->Reset();
                return;
            }
        }
    }
}