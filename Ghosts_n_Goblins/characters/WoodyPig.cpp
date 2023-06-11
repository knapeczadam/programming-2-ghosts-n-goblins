#include "pch.h"
#include "WoodyPig.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "fx/FXManager.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"
#include "throwables/Spear.h"

WoodyPig::WoodyPig(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_WOODY_PIG, pos, pGameController}
      , m_State{State::SPAWNING}
      , m_SnapshotPos{0.0f, 0.0f}
      , m_SnapshotOffset{0.0f}
      , m_SnapshotAngle{0.0f}
      , m_SnapshotTaken{false}
      , m_SnapshotFlipped{false}
      , m_AccuTime{0.0f}
{
    m_Score = 100;
    m_AwakeDistance = std::numeric_limits<float>::max();
    m_HorVelocity = 100.0f;
    m_VerVelocity = 100.0f;
    m_Velocity = Vector2f{m_HorVelocity, m_VerVelocity};
}

void WoodyPig::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
    m_Flipped = IsFlipped();
    m_AccuTime += elapsedSec;

    switch (m_State)
    {
    case State::FLYING:
        Fly(elapsedSec);
        break;
    case State::TURNING:
        Turn(elapsedSec);
        break;
    }
}

void WoodyPig::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    if (m_State == State::SPAWNING) return;
    --m_HP;
    other->SetActive(false);
    other->SetVisible(false);
    if (m_HP == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayerManager->GetPlayer()->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_FIRE_ENEMY, GetColliderCenter(), other->IsFlipped());
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
    }
}

void WoodyPig::Awake(float elapsedSec)
{
    // m_State = State::SPAWNING;
}

void WoodyPig::LateUpdate(float elapsedSec)
{
    UpdateState();
    UpdateSprite();
    IEnemy::LateUpdate(elapsedSec);
}

void WoodyPig::Reset()
{
    IEnemy::Reset();
    m_pSprite->ResetIterCount();
    ResetTimer();
    m_State = State::SPAWNING;
}

WoodyPig::State WoodyPig::GetState() const
{
    return m_State;
}

void WoodyPig::Shoot(float elapsedSec)
{
    const bool down{Game::GetRandomBool()};
    const Vector2f direction{m_pGameController->m_pPlayerManager->GetPlayer()->GetShapeCenter() - GetShapeCenter()};
    for (GameObject* pThrowable : m_pGameController->m_pEnemyManager->GetThrowables())
    {
        if ((pThrowable->GetLabel() == Game::Label::T_SPEAR_X or pThrowable->GetLabel() == Game::Label::T_SPEAR_Y) and
            not pThrowable->IsActive())
        {
            if (down and pThrowable->GetLabel() == Game::Label::T_SPEAR_Y)
            {
                Spear* pSpear{static_cast<Spear*>(pThrowable)};
                pSpear->Reset();
                pSpear->SetPosition(GetShapeCenter());
                pSpear->SetDirection(direction.Normalized());
                return;
            }
            else if (not down and pThrowable->GetLabel() == Game::Label::T_SPEAR_X)
            {
                Spear* pSpear{static_cast<Spear*>(pThrowable)};
                pSpear->Reset();
                pSpear->SetPosition(GetShapeCenter());
                pSpear->SetDirection(direction.Normalized());
                return;
            }
        }
    }
    m_pGameController->m_pEnemyManager->GetThrowables().push_back(
        new Spear{GetShapeCenter(), direction.Normalized(), down, m_pGameController}
    );
}

void WoodyPig::Fly(float elapsedSec)
{
    // StartTimer(Game::GetRandomFloat(4.0f, 6.0f));
    StartTimer(Game::GetRandomFloat(1.0f, 2.0f));
    if (IsTimerFinished())
    {
        Shoot(elapsedSec);
        m_State = State::SHOOTING;
        m_pSprite->ResetIterCount();
    }
    m_Shape.left += m_Velocity.x * elapsedSec;

    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_WOODY_PIG);
}

void WoodyPig::Turn(float elapsedSec)
{
    if (not m_SnapshotTaken)
    {
        m_SnapshotPos = GetPosition<Point2f>();
        m_SnapshotFlipped = m_Flipped;
        const float up{Game::GetRandomFloat(30.0f, 50.0f)};
        const float down{Game::GetRandomFloat(30.0f, 50.0f) * -1};
        m_SnapshotOffset = Game::GetRandomBool() ? up : down;
        m_SnapshotTaken = true;
        m_SnapshotAngle = m_SnapshotOffset > 0 ? 270 : 90;
        m_AccuTime = 0.0f;
    }
    const float radius{std::abs(m_SnapshotOffset / 2)};
    Point2f center;
    center.x = m_SnapshotPos.x;
    float angle;
    if (m_SnapshotOffset > 0)
    {
        center.y = m_SnapshotPos.y + radius;;
        if (m_SnapshotFlipped)
        {
            angle = m_SnapshotAngle + 180 * (m_AccuTime / 4.0f);
        }
        else
        {
            angle = m_SnapshotAngle - 180 * (m_AccuTime / 4.0f);
        }
    }
    else
    {
        center.y = m_SnapshotPos.y - radius;
        if (m_SnapshotFlipped)
        {
            angle = m_SnapshotAngle - 180 * (m_AccuTime / 4.0f);
        }
        else
        {
            angle = m_SnapshotAngle + 180 * (m_AccuTime / 4.0f);
        }
    }
    angle *= utils::g_Pi / 180.0f;
    m_Shape.left = std::cos(angle) * radius + center.x;
    m_Shape.bottom = std::sin(angle) * radius + center.y;
    if (std::abs(m_Shape.bottom - m_SnapshotOffset) < 0.01f)
    {
        m_SnapshotTaken = false;
        m_State = State::FLYING;
    }
}

void WoodyPig::UpdateState()
{
    if (m_State == State::SPAWNING and m_pSprite->GetIterCount() == 1)
    {
        m_State = State::FLYING;
    }
    else if (m_State == State::SHOOTING)
    {
        StartTimer(0.3f);
        if (IsTimerFinished())
        {
            m_State = Game::GetRandomBool() ? State::FLYING : State::TURNING;
        }
    }
    else if (m_State == State::TURNING and m_pSprite->GetIterCount() == 1)
    {
        m_State = State::FLYING;
    }
}

void WoodyPig::UpdateSprite()
{
    switch (m_State)
    {
    case State::SPAWNING:
        m_pSprite->SetTopOffsetRows(0);
        m_pSprite->SetSubCols(4);
        break;
    case State::FLYING:
        m_pSprite->SetTopOffsetRows(1);
        m_pSprite->SetSubCols(2);
        break;
    case State::SHOOTING:
        m_pSprite->SetTopOffsetRows(3);
        m_pSprite->SetSubCols(1);
        break;
    case State::TURNING:
        m_pSprite->SetTopOffsetRows(2);
        m_pSprite->SetSubCols(2);
        break;
    }
    m_pSprite->SetSubRows(1);
    m_pSprite->SetCurrRowsCols();
    m_pSprite->CalculateFrameTime();
    m_pSprite->UpdateSourceRect();
}
