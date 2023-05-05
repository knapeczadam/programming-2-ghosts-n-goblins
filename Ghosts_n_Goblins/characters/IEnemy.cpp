#include "pch.h"
#include "IEnemy.h"
#include "engine/SoundManager.h"
#include "Player.h"
#include "game/GameController.h"

IEnemy::IEnemy(Game::Label label, const Point2f& pos, GameController* pGameController)
    : GameObject{label, pos, true, pGameController}
      , m_SpawnPos{pos}
      , m_Score{0}
      , m_Health{1}
      , m_Awake{false}
      , m_AwakeFired{false}
      , m_AwakeDistance{200.0f}
      , m_HorVelocity{0.0f}
      , m_VerVelocity{0.0f}
      , m_Ping{true}
{
}

void IEnemy::Update(float elapsedSec)
{
    if (not m_AwakeFired)
    {
        if (utils::GetDistance(GetShapeCenter(), m_pGameController->m_pPlayer->GetShapeCenter()) < m_AwakeDistance)
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

void IEnemy::SetAwake(bool awake)
{
    m_Awake = awake;
    if (not m_Awake)
    {
        m_AwakeFired = false;
    }
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
    if (GetPosition<Point2f>().x < m_pGameController->m_pPlayer->GetPosition<Point2f>().x)
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

float IEnemy::GetAngle() const
{
    const float dx{m_pGameController->m_pPlayer->GetPosition<Point2f>().x - GetPosition<Point2f>().x};
    const float dy{m_pGameController->m_pPlayer->GetPosition<Point2f>().y - GetPosition<Point2f>().y};
    return std::atan2f(dy, dx);
}
