#include "pch.h"
#include "BigMan.h"

#include "Player.h"
#include "engine/SoundManager.h"

BigMan::BigMan(Sprite* pSprite, const Point2f& pos, Player* pPlayer, Sprite* pFX,SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_BIG_MAN, pSprite, pos, pPlayer, pFX, pSoundManager}
{
    m_Score = 2000;
}

void BigMan::Draw() const
{
    GameObject::Draw();
}

void BigMan::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void BigMan::HandleCollision(GameObject* other)
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

void BigMan::Wait(float elapsedSec)
{
    IEnemy::Wait(elapsedSec);
}

void BigMan::Walk(float elapsedSec)
{
    IEnemy::Walk(elapsedSec);
    m_pSoundManager->PlayEffect(Game::Label::E_BIG_ENEMY_WALK);
}

void BigMan::Jump(float elapsedSec)
{
    IEnemy::Jump(elapsedSec);
}

void BigMan::Shoot(float elapsedSec)
{
    IEnemy::Shoot(elapsedSec);
}
