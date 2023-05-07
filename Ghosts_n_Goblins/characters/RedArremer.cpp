#include "pch.h"
#include "RedArremer.h"
#include "engine/SoundManager.h"
#include "Player.h"
#include "game/GameController.h"
#include "fx/FXManager.h"

RedArremer::RedArremer(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_RED_ARREMER, pos, pGameController}
{
    m_Score = 1000;
    m_Health = 3;
}

void RedArremer::Draw() const
{
    GameObject::Draw();
}

void RedArremer::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
}

void RedArremer::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    other->SetActive(false);
    other->SetVisible(false);
    m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_PROJECTILE_BLOCK_ENEMY, GetContactPoint(other), other->IsFlipped());
    if (m_Health == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayer->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_FIRE_ENEMY, GetCollisionBoxCenter(), other->IsFlipped());
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_SCORE, GetCollisionBoxCenter(), false, this);
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
    }
}

void RedArremer::Wait(float elapsedSec)
{
    IEnemy::Wait(elapsedSec);
}

void RedArremer::Walk(float elapsedSec)
{
    IEnemy::Walk(elapsedSec);
}

void RedArremer::Shoot(float elapsedSec)
{
    IEnemy::Shoot(elapsedSec);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_RED_ARREMER_ATTACK);
}

void RedArremer::Fly(float elapsedSec)
{
    IEnemy::Fly(elapsedSec);
}
