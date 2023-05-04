﻿#include "pch.h"
#include "GreenMonster.h"
#include "engine/SoundManager.h"
#include "Player.h"

GreenMonster::GreenMonster(Sprite* pSprite, const Point2f& pos, Player* pPlayer,Sprite* pFX, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_GREEN_MONSTER, pSprite, pos, pPlayer, pFX, pSoundManager}
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
}

void GreenMonster::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    if (m_Health == 0)
    {
        m_pPlayer->AddScore(m_Score);
    }
}

void GreenMonster::Wait(float elapsedSec)
{
    IEnemy::Wait(elapsedSec);
}

void GreenMonster::Shoot(float elapsedSec)
{
    IEnemy::Shoot(elapsedSec);
}
