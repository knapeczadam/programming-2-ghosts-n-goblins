#include "pch.h"
#include "IEnemy.h"
#include "engine/SoundManager.h"
#include "Player.h"

IEnemy::IEnemy(Game::Label label, Sprite* pSprite, const Point2f& pos, Player* pPlayer, SoundManager* pSoundManager)
    : GameObject{label, pSprite, pos}
      , m_pPlayer{pPlayer}
      , m_pSoundManager{pSoundManager}
      , m_Score{}
      , m_Health{1}
{
}

void IEnemy::Wait()
{
}

void IEnemy::Walk()
{
}

void IEnemy::Jump()
{
}

void IEnemy::Shoot()
{
}

void IEnemy::Fly()
{
}

void IEnemy::Spawn()
{
}

bool IEnemy::IsFlipped() const
{
    if (m_pPlayer->GetPosition<Point2f>().x < GetPosition<Point2f>().x)
    {
        return true;
    }
    return false;
}

float IEnemy::GetAngle() const
{
    const float dx{m_pPlayer->GetPosition<Point2f>().x - GetPosition<Point2f>().x};
    const float dy{m_pPlayer->GetPosition<Point2f>().y - GetPosition<Point2f>().y};
    return std::atan2f(dy, dx);
}
