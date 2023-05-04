#include "pch.h"
#include "FlyingKnight.h"
#include "engine/SoundManager.h"

FlyingKnight::FlyingKnight(Sprite* pSprite, const Point2f& pos, Player* pPlayer, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_FLYING_KNIGHT, pSprite, pos, pPlayer, pSoundManager}
{
    m_Score = 100;
}

void FlyingKnight::Draw() const
{
    GameObject::Draw();
}

void FlyingKnight::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void FlyingKnight::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    if (m_Health == 0)
    {
        
    }
}

void FlyingKnight::Fly()
{
    IEnemy::Fly();
    m_pSoundManager->PlayEffect(Game::Label::E_FLYING_KNIGHT);
}
