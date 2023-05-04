#include "pch.h"
#include "WoodyPig.h"
#include "engine/SoundManager.h"
#include "Player.h"

WoodyPig::WoodyPig(Sprite* pSprite, const Point2f& pos, Player* pPlayer, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_WOODY_PIG, pSprite, pos, pPlayer, pSoundManager}
{
    m_Score = 100;
}

void WoodyPig::Draw() const
{
    GameObject::Draw();
}

void WoodyPig::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void WoodyPig::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    if (m_Health == 0)
    {
       m_pPlayer->AddScore(m_Score); 
    }
}

void WoodyPig::Shoot()
{
    IEnemy::Shoot();
}

void WoodyPig::Fly()
{
    IEnemy::Fly();
    m_pSoundManager->PlayEffect(Game::Label::E_WOODY_PIG);
}
