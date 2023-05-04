#include "pch.h"
#include "Magician.h"
#include "engine/SoundManager.h"
#include "Player.h"

Magician::Magician(Sprite* pSprite, const Point2f& pos, Player* pPlayer, Sprite* pFX, SoundManager* pSoundManager)
    : IEnemy{Game::Label::E_MAGICIAN, pSprite, pos, pPlayer, pFX, pSoundManager}
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
       m_pPlayer->AddScore(m_Score); 
    }
}

void Magician::Shoot(float elapsedSec)
{
    IEnemy::Shoot(elapsedSec);
    m_pSoundManager->PlayEffect(Game::Label::E_MAGICIAN);
}
