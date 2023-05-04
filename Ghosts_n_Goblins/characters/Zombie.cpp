﻿#include "pch.h"
#include "Zombie.h"
#include "engine/SoundManager.h"
#include "Player.h"

Zombie::Zombie(Sprite* pSprite, const Point2f& pos, Player* pPlayer, Sprite* pFX, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_ZOMBIE, pSprite, pos, pPlayer, pFX, pSoundManager}
{
    m_Score = 200;
}

void Zombie::Draw() const
{
    GameObject::Draw();
}

void Zombie::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
}

void Zombie::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    if (m_Health == 0)
    {
       m_pPlayer->AddScore(m_Score); 
    }
}

void Zombie::Walk(float elapsedSec)
{
    IEnemy::Walk(elapsedSec);
}

void Zombie::Spawn()
{
    m_pSoundManager->PlayEffect(Game::Label::E_ZOMBIE_SPAWN);
}