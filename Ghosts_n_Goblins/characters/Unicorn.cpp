#include "pch.h"
#include "Unicorn.h"

#include "Player.h"
#include "engine/SoundManager.h"

Unicorn::Unicorn(Sprite* pSprite, const Point2f& pos, Player* pPlayer, Sprite* pFX,SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_UNICORN, pSprite, pos, pPlayer, pFX, pSoundManager}
{
    m_Score = 2000;
}

void Unicorn::Draw() const
{
    GameObject::Draw();
}

void Unicorn::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void Unicorn::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    m_pSoundManager->PlayEffect(Game::Label::E_BOSS_HIT);
    --m_Health;
    if (m_Health == 0)
    {
        m_pSoundManager->PlayEffect(Game::Label::E_BOSS_DEATH);
        m_pPlayer->AddScore(m_Score);
    }
}

void Unicorn::Wait(float elapsedSec)
{
    IEnemy::Wait(elapsedSec);
}

void Unicorn::Walk(float elapsedSec)
{
    IEnemy::Walk(elapsedSec);
    m_pSoundManager->PlayEffect(Game::Label::E_BIG_ENEMY_WALK);
}

void Unicorn::Jump(float elapsedSec)
{
    IEnemy::Jump(elapsedSec);
}

void Unicorn::Shoot(float elapsedSec)
{
    IEnemy::Shoot(elapsedSec);
}
