#include "pch.h"
#include "Magician.h"
#include "engine/SoundManager.h"
#include "Player.h"
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
    if (m_Health == 0)
    {
       m_pGameController->m_pPlayer->AddScore(m_Score); 
    }
}

void Magician::Shoot(float elapsedSec)
{
    IEnemy::Shoot(elapsedSec);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_MAGICIAN);
}
