#include "pch.h"
#include "IEnemy.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"

IEnemy::IEnemy(Game::Label label, const Point2f& pos, GameController* pGameController)
    : GameObject{label, pos, true, pGameController}
      , m_SpawnPos{pos}
      , m_Score{0}
      , m_HP{1}
      , m_OriginalHP{m_HP}
      , m_Awake{false}
      , m_AwakeFired{false}
      , m_AwakeDistance{200.0f}
      , m_HorVelocity{0.0f}
      , m_VerVelocity{0.0f}
      , m_Ping{true}
      , m_FixedDirection{false}
{
}

void IEnemy::Update(float elapsedSec)
{
    if (not m_AwakeFired)
    {
        if (utils::GetDistance(GetShapeCenter(), m_pGameController->m_pPlayerManager->GetPlayer()->GetShapeCenter()) < m_AwakeDistance)
        {
            m_Awake = true;
        }
    }

    if (m_Awake)
    {
        if (not m_AwakeFired)
        {
            Awake(elapsedSec);
            m_AwakeFired = true;
        }
    }
}

bool IEnemy::IsAwake() const
{
    return m_Awake;
}

void IEnemy::SetAwake(bool awake)
{
    m_Awake = awake;
    if (not m_Awake)
    {
        m_AwakeFired = false;
    }
}

int IEnemy::GetScore() const
{
    return m_Score;
}

void IEnemy::Reset(const Point2f& pos)
{
    
}

void IEnemy::Awake(float elapsedSec)
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

void IEnemy::Spawn(float elapsedSec)
{
}

/**
 * \brief Enemy looks to the left by default
 * \return true if enemy looks to the right
 */
bool IEnemy::IsFlipped() const
{
    if (GetPosition<Point2f>().x < m_pGameController->m_pPlayerManager->GetPlayer()->GetPosition<Point2f>().x)
    {
        return true;
    }
    return false;
}

void IEnemy::Switch(float interval)
{
    StartTimer(interval);
    if (IsTimerFinished())
    {
        m_Ping = not m_Ping;
    }
    if (m_Ping)
    {
        Ping();
    }
    else
    {
        Pong();
    }
}

void IEnemy::Ping()
{
}

void IEnemy::Pong()
{
}

void IEnemy::ResetHP()
{
    m_HP = m_OriginalHP;
}

bool IEnemy::IsFixedDirection() const
{
    return m_FixedDirection;
}

float IEnemy::GetAngle() const
{
    const float dx{m_pGameController->m_pPlayerManager->GetPlayer()->GetPosition<Point2f>().x - GetPosition<Point2f>().x};
    const float dy{m_pGameController->m_pPlayerManager->GetPlayer()->GetPosition<Point2f>().y - GetPosition<Point2f>().y};
    return std::atan2f(dy, dx);
}
