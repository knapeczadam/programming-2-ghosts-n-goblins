#include "pch.h"
#include "Magician.h"
#include "engine/SoundManager.h"
#include "Player.h"
#include "fx/FXManager.h"
#include "game/GameController.h"

Magician::Magician(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_MAGICIAN, pos, pGameController}
{
    m_Score = 2000;
}

void Magician::Draw() const
{
    GameObject::Draw();
}

void Magician::Update(float elapsedSec)
{
}

void Magician::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    other->SetActive(false);
    other->SetVisible(false);
    if (m_Health == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayer->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_PROJECTILE_DEATH, GetContactPoint(other), other->IsFlipped());
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
    }
}

void Magician::Shoot(float elapsedSec)
{
    IEnemy::Shoot(elapsedSec);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_MAGICIAN);
}
