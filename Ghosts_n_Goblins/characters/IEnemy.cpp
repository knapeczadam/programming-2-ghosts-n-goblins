#include "pch.h"
#include "IEnemy.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"

IEnemy::IEnemy(Game::Label label, const Point2f& pos, GameController* pGameController)
    : GameObject{label, pos, true, pGameController}
    , m_SpawnPosition{pos}
    , m_Score{0}
    , m_HP{1}
    , m_OriginalHP{m_HP}
    , m_HorVelocity{0.0f}
    , m_VerVelocity{0.0f}
    , m_Velocity{0.0f, 0.0f}
    , m_Ping{true}
    , m_FixedDirection{false}
{
}

int IEnemy::GetScore() const
{
    return m_Score;
}

void IEnemy::Reset()
{
    GameObject::Reset();
    ResetHP();
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

/**
 * \brief Switches between Ping and Pong functions, works like a continuous switch
 * \param interval time between switching
 */
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

void IEnemy::SetSpawnPosition(const Point2f& position)
{
    m_SpawnPosition = position;
}

void IEnemy::ResetHP()
{
    m_HP = m_OriginalHP;
}

bool IEnemy::IsFixedDirection() const
{
    return m_FixedDirection;
}

/**
 * \brief angle between enemy and player
 * \return angle in radians
 */
float IEnemy::GetAngle() const
{
    const float dx{m_pGameController->m_pPlayerManager->GetPlayer()->GetPosition<Point2f>().x - GetPosition<Point2f>().x};
    const float dy{m_pGameController->m_pPlayerManager->GetPlayer()->GetPosition<Point2f>().y - GetPosition<Point2f>().y};
    return std::atan2f(dy, dx);
}
