#include "pch.h"
#include "WoodyPig.h"
#include "engine/SoundManager.h"
#include "Player.h"

WoodyPig::WoodyPig(const Point2f& pos, Player* pPlayer, SpriteFactory* pSpriteFactory, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_WOODY_PIG, pos, pPlayer, pSpriteFactory, pSoundManager}
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
    if (m_Health == 0)
    {
       m_pPlayer->AddScore(m_Score); 
    }
}

void WoodyPig::Shoot(float elapsedSec)
{
    IEnemy::Shoot(elapsedSec);
}

void WoodyPig::Fly(float elapsedSec)
{
    IEnemy::Fly(elapsedSec);
    m_pSoundManager->PlayEffect(Game::Label::E_WOODY_PIG);
}
