#include "pch.h"
#include "RedArremer.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "fx/FXManager.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"
#include "throwables/Fireball.h"
#include "game/GameController.h"
#include "game/LevelManager.h"


RedArremer::RedArremer(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_RED_ARREMER, pos, pGameController}
    , m_State{State::MEDITATING}
    , m_PosSnapshot{0.0f, 0.0f}
    , m_AngleSnapshot{0.0f}
    , m_SnapshotTaken{false}
{
    m_Score = 1000;
    m_HP = 3;
    m_AwakeDistance = 200.0f;
    m_HorVelocity = 100.0f;
    m_VerVelocity = 100.0f;
    m_Velocity = Vector2f{m_HorVelocity, m_VerVelocity};
}

void RedArremer::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
    m_Flipped = IsFlipped();
    switch (m_State)
    {
    case State::WALKING:
        Walk(elapsedSec);
        break;
    case State::FLYING:
    case State::FLYING_UP:
    case State::FLYING_DOWN:
    case State::FLYING_SIDEWAYS:
        Fly(elapsedSec);
        break;
    }
}

void RedArremer::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    if (m_State == State::MEDITATING or m_State == State::WAKING_UP) return;
    --m_HP;
    other->SetActive(false);
    other->SetVisible(false);
    m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_PROJECTILE_BLOCK_ENEMY, GetContactPoint(other),
                                                other->IsFlipped());
    if (m_HP == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayerManager->GetPlayer()->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_FIRE_ENEMY, GetColliderCenter(), other->IsFlipped());
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_SCORE, GetColliderCenter(), false, this);
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
    }
}

void RedArremer::LateUpdate(float elapsedSec)
{
    UpdateState();
    UpdateSprite();
    IEnemy::LateUpdate(elapsedSec);
}

void RedArremer::Awake(float elapsedSec)
{
    m_State = State::WAKING_UP;
}

void RedArremer::Walk(float elapsedSec)
{
    std::uniform_real_distribution<float> time{4.0f, 6.0f};
    StartTimer(time(Game::GetRandomGenerator()));
    if (IsTimerFinished())
    {
        m_pSprite->ResetIterCount();
        Shoot(elapsedSec);
        m_State = State::WALKING_SHOOTING;
    }
    if (not m_SnapshotTaken)
    {
        m_PosSnapshot = m_pGameController->m_pPlayerManager->GetPlayer()->GetPosition<Point2f>();
        m_SnapshotTaken = true;
    }
    m_Shape.left += (m_Flipped ? m_Velocity.x : -m_Velocity.x) * elapsedSec;
    const float offset{75.0f};
    const float left{m_Shape.left + (m_Flipped ? offset : -offset)};
    if (m_Flipped and left > m_PosSnapshot.x or not m_Flipped and left < m_PosSnapshot.x)
    {
        m_State = Game::GetRandomBool() ? State::FLYING : State::WALKING;
        m_SnapshotTaken = false;
    }
}

void RedArremer::Shoot(float elapsedSec)
{
    const Vector2f direction{m_pGameController->m_pPlayerManager->GetPlayer()->GetShapeCenter() - GetShapeCenter()};
    for (GameObject* pThrowable : m_pGameController->m_pEnemyManager->GetThrowables())
    {
        if (pThrowable->GetLabel() == Game::Label::T_FIREBALL_RED_ARREMER and not pThrowable->IsActive())
        {
            Fireball* pFireball{static_cast<Fireball*>(pThrowable)};
            pFireball->Reset();
            pFireball->SetPosition(GetShapeCenter());
            pFireball->SetDirection(direction.Normalized());
            return;
        }
    }
    m_pGameController->m_pEnemyManager->GetThrowables().push_back(new Fireball{
        Game::Label::T_FIREBALL_RED_ARREMER, GetShapeCenter(), direction.Normalized(), m_pGameController
    });
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_RED_ARREMER_ATTACK);
}

void RedArremer::Fly(float elapsedSec)
{
    std::uniform_real_distribution<float> time{4.0f, 6.0f};
    StartTimer(time(Game::GetRandomGenerator()));
    if (IsTimerFinished())
    {
        m_pSprite->ResetIterCount();
        Shoot(elapsedSec);
        m_State = State::FLYING_SHOOTING;
    }
    if (m_State == State::FLYING)
    {
        m_State = State::FLYING_UP;
    }
    else if (m_State == State::FLYING_UP)
    {
        if (m_Shape.bottom <= LevelManager::GetHillHeight())
        {
            m_Shape.bottom += m_Velocity.y * elapsedSec;
        }
        else if (m_Shape.bottom > LevelManager::GetHillHeight())
        {
            m_State = Game::GetRandomBool() ? State::FLYING_SIDEWAYS : State::FLYING_DOWN;
        }
    }
    else if (m_State == State::FLYING_DOWN)
    {
        if (m_Shape.bottom >= LevelManager::GetGroundHeight())
        {
            m_Shape.bottom -= m_Velocity.y * elapsedSec;
            if (not m_SnapshotTaken)
            {
                m_AngleSnapshot = GetAngle();
                m_SnapshotTaken = true;
            }
            m_Shape.left += std::cos(m_AngleSnapshot) * m_Velocity.x * elapsedSec;
        }
        else if (m_Shape.bottom < LevelManager::GetGroundHeight())
        {
            m_State = Game::GetRandomBool() ? State::WALKING : State::FLYING;
            m_SnapshotTaken = false;
        }
    }
    else if (m_State == State::FLYING_SIDEWAYS)
    {
        const float offset{75.0f};
        m_Shape.left += (m_Flipped ? m_Velocity.x : -m_Velocity.x) * elapsedSec;
        const float left{m_Shape.left + (m_Flipped ? offset : -offset)};
        const float playerLeft{m_pGameController->m_pPlayerManager->GetPlayer()->GetPosition<Point2f>().x};
        if (m_Flipped and left > playerLeft or not m_Flipped and left < playerLeft)
        {
            m_State = Game::GetRandomBool() ? State::FLYING_SIDEWAYS : State::FLYING_DOWN;
        }
    }
}

void RedArremer::UpdateState()
{
    if (m_State == State::WAKING_UP and m_pSprite->GetIterCount() == 1)
    {
        m_pSprite->ResetIterCount();
        m_State = State::FLYING;
    }
    else if (m_State == State::FLYING_SHOOTING and m_pSprite->GetIterCount() == 1)
    {
        m_pSprite->ResetIterCount();
        m_State = State::FLYING;
    }
    else if (m_State == State::WALKING_SHOOTING and m_pSprite->GetIterCount() == 1)
    {
        m_pSprite->ResetIterCount();
        m_State = State::WALKING;
    }
}

void RedArremer::UpdateSprite()
{
    switch (m_State)
    {
    case State::MEDITATING:
        m_pSprite->SetTopOffsetRows(0);
        m_pSprite->SetSubCols(1);
        break;
    case State::WAKING_UP:
        m_pSprite->SetTopOffsetRows(1);
        m_pSprite->SetSubCols(3);
        break;
    case State::WALKING:
        m_pSprite->SetTopOffsetRows(2);
        m_pSprite->SetSubCols(2);
        break;
    case State::WALKING_SHOOTING:
        m_pSprite->SetTopOffsetRows(4);
        m_pSprite->SetSubCols(2);
        break;
    case State::FLYING:
        m_pSprite->SetTopOffsetRows(3);
        m_pSprite->SetSubCols(2);
        break;
    case State::FLYING_SHOOTING:
        m_pSprite->SetTopOffsetRows(5);
        m_pSprite->SetSubCols(2);
        break;
    }
    m_pSprite->SetSubRows(1);
    m_pSprite->SetCurrRowsCols();
    m_pSprite->CalculateFrameTime();
    m_pSprite->UpdateSourceRect();
}

void RedArremer::RandomizeState()
{
    std::uniform_real_distribution<float> time{4.0f, 6.0f};
    StartTimer(time(Game::GetRandomGenerator()));
    if (IsTimerFinished())
    {
        std::uniform_int_distribution<int> randomState{1, 3};
        m_State = static_cast<State>(randomState(Game::GetRandomGenerator()));
    }
}
