#include "pch.h"
#include "Unicorn.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "game/GameController.h"

Unicorn::Unicorn(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_UNICORN, pos, pGameController}
{
    m_Score = 2000;
    m_Health = 10;
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
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_BOSS_HIT);
    --m_Health;
    if (m_Health == 0)
    {
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_BOSS_DEATH);
        m_pGameController->m_pPlayer->AddScore(m_Score);
    }
}

void Unicorn::Wait(float elapsedSec)
{
    IEnemy::Wait(elapsedSec);
}

void Unicorn::Walk(float elapsedSec)
{
    IEnemy::Walk(elapsedSec);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_BIG_ENEMY_WALK);
}

void Unicorn::Jump(float elapsedSec)
{
    IEnemy::Jump(elapsedSec);
}

void Unicorn::Shoot(float elapsedSec)
{
    IEnemy::Shoot(elapsedSec);
}
