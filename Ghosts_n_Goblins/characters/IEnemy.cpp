#include "pch.h"
#include "IEnemy.h"
#include "engine/SoundManager.h"
#include "Player.h"

IEnemy::IEnemy(Game::Label label, Sprite* pSprite, const Point2f& pos, Player* pPlayer, Sprite* pFX,
               SoundManager* pSoundManager)
    : GameObject{label, pSprite, pos, true, pSoundManager}
      , m_pPlayer{pPlayer}
      , m_pFX{pFX}
      , m_SpawnPos{pos}
      , m_Score{0}
      , m_Health{1}
      , m_Awake{false}
      , m_AwakeFired{false}
      , m_AwakeDistance{200.0f}
      , m_HorVelocity{0.0f}
      , m_VerVelocity{0.0f}
{
}

void IEnemy::Update(float elapsedSec)
{
    if (not m_AwakeFired)
    {
        if (utils::GetDistance(GetShapeCenter(), m_pPlayer->GetShapeCenter()) < m_AwakeDistance)
        {
            m_Awake = true;
        }
    }

    if (m_Awake)
    {
        if (not m_AwakeFired)
        {
            Awake();
            m_AwakeFired = true;
        }
    }
}

bool IEnemy::IsAwake() const
{
    return m_Awake;
}

void IEnemy::Awake()
{
}

void IEnemy::Wait(float elapsedSec)
{
}

void IEnemy::Walk(float elapsedSec)
{
}

void IEnemy::Jump(float elapsedSec)
{
}

void IEnemy::Shoot(float elapsedSec)
{
}

void IEnemy::Fly(float elapsedSec)
{
}

void IEnemy::Spawn()
{
}

// Enemy looks to the left by default
bool IEnemy::IsFlipped() const
{
    if (GetPosition<Point2f>().x < m_pPlayer->GetPosition<Point2f>().x)
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
