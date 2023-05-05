#include "pch.h"
#include "FlyingKnight.h"
#include "engine/SoundManager.h"
#include "Player.h"

FlyingKnight::FlyingKnight(const Point2f& pos, Player* pPlayer, SpriteFactory* pSpriteFactory, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_FLYING_KNIGHT, pos, pPlayer, pSpriteFactory, pSoundManager}
{
    m_Score = 100;
}

void FlyingKnight::Draw() const
{
    GameObject::Draw();
}

void FlyingKnight::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
}

void FlyingKnight::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    if (m_Health == 0)
    {
        m_pPlayer->AddScore(m_Score);
    }
}

void FlyingKnight::Fly(float elapsedSec)
{
    IEnemy::Fly(elapsedSec);
    m_pSoundManager->PlayEffect(Game::Label::E_FLYING_KNIGHT);
}
