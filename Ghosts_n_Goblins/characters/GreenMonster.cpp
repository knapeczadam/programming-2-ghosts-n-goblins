﻿#include "pch.h"
#include "GreenMonster.h"
#include "engine/SoundManager.h"
#include "Player.h"
#include "throwables/Eyeball.h"

GreenMonster::GreenMonster(const Point2f& pos, Player* pPlayer,std::vector<GameObject*>& enemies, SpriteFactory* pSpriteFactory, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_GREEN_MONSTER,  pos, pPlayer, pSpriteFactory, pSoundManager}
    , m_EnemyThrowables{enemies}
{
    m_Score = 100;
    
}

void GreenMonster::Draw() const
{
    GameObject::Draw();
}

void GreenMonster::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
    if (not m_Awake)
    {
        Wait(elapsedSec);
    }
    else
    {
       Shoot(elapsedSec);
        m_Flipped = IsFlipped();
    }
}

void GreenMonster::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    
    if (m_Health == 0)
    {
        m_pPlayer->AddScore(m_Score);
        m_Active = false;
        m_Visible = false;
    }
}

void GreenMonster::Wait(float elapsedSec)
{
    IEnemy::Wait(elapsedSec);
}

void GreenMonster::Shoot(float elapsedSec)
{
    const int randInterval{std::rand() % 2 + 1}; 
    StartTimer(randInterval);
    if (IsTimerFinished())
    {
        const Vector2f direction{m_pPlayer->GetShapeCenter() - GetShapeCenter()};
        for (GameObject* pThrowable : m_EnemyThrowables)
        {
            if (pThrowable->GetLabel() == Game::Label::T_EYEBALL and not pThrowable->IsActive())
            {
                Eyeball* pEyeball{dynamic_cast<Eyeball*>(pThrowable)};
                pEyeball->SetActive(true);
                pEyeball->SetPosition(GetShapeCenter());
                pEyeball->SetDirection(direction.Normalized());
                return;
            }
        }
        m_EnemyThrowables.push_back(new Eyeball{GetShapeCenter(),direction.Normalized(), m_pSpriteFactory});
    }
    
}
