#include "pch.h"
#include "WoodyPig.h"
#include "engine/SoundManager.h"
#include "Player.h"
#include "game/GameController.h"
#include "fx/FXManager.h"

WoodyPig::WoodyPig(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_WOODY_PIG, pos, pGameController}
{
    m_Score = 100;
}

void WoodyPig::Draw() const
{
    GameObject::Draw();
}

void WoodyPig::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
}

void WoodyPig::HandleCollision(GameObject* other)
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
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_FIRE_ENEMY, GetContactPoint(other), other->IsFlipped());
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
    }
}

void WoodyPig::Shoot(float elapsedSec)
{
    IEnemy::Shoot(elapsedSec);
}

void WoodyPig::Fly(float elapsedSec)
{
    IEnemy::Fly(elapsedSec);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_WOODY_PIG);
}
