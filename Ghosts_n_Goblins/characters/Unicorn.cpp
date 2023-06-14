#include "pch.h"
#include "Unicorn.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "fx/FXManager.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"
#include "game/LevelManager.h"
#include "game/PlayerManager.h"
#include "throwables/Fireball.h"

#include <iostream>

Unicorn::Unicorn(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_UNICORN, pos, pGameController}
    , m_State{State::WAITING}
    , m_SnapshotPlayerPos{0.0f, 0.0f}
    , m_SnapshotPos{0.0f, 0.0f}
    , m_JumpHeight{100.0f}
    , m_OriginalHeight{pos.y}
    , m_SnapshotTaken{false}
    , m_SnapshotFlipped{false}
    , m_LeftOffsetCols{0}
{
    m_Score = 2000;
    m_HP = 10;
    m_AwakeDistance = 200.0f;
    m_HorVelocity = 100.0f;
    m_VerVelocity = 100.0f;
    m_Velocity = Vector2f{m_HorVelocity, m_VerVelocity};
}

void Unicorn::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
    m_Flipped = IsFlipped();

    switch (m_State)
    {
    case State::WALKING:
        Walk(elapsedSec);
        break;
    case State::JUMPING:
        Jump(elapsedSec);
        break;
    }
}

void Unicorn::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    if (m_State != State::WAITING or m_State != State::ANGRY)
    {
        --m_HP;
    }
    other->SetActive(false);
    other->SetVisible(false);
    m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_PROJECTILE_BLOCK_BOSS, GetContactPoint(other), false);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_BOSS_HIT);
    if (m_HP == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayerManager->GetPlayer()->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_FIRE_BOSS, GetColliderCenter(), other->IsFlipped());
        m_pGameController->m_pFXManager->
                           PlayEffect(Game::Label::F_SCORE, GetColliderCenter(), false, this);
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_BOSS_DEATH);
    }
}

void Unicorn::Awake(float elapsedSec)
{
    m_State = State::ANGRY;
}

void Unicorn::LateUpdate(float elapsedSec)
{
    UpdateState();
    UpdateSprite();
    IEnemy::LateUpdate(elapsedSec);
}

void Unicorn::Walk(float elapsedSec)
{
    StartTimer(Game::GetRandomFloat(0.5f, 2.0f));
    if (IsTimerFinished())
    {
        m_pSprite->ResetIterCount();
        Shoot(elapsedSec);
        m_State = State::SHOOTING;
    }
    if (not m_SnapshotTaken)
    {
        m_SnapshotPlayerPos = m_pGameController->m_pPlayerManager->GetPlayer()->GetPosition<Point2f>();
        m_SnapshotTaken = true;
        m_SnapshotFlipped = m_Flipped;
    }
    m_Shape.left += (m_SnapshotFlipped ? m_Velocity.x : -m_Velocity.x) * elapsedSec;
    const float offset{75.0f};
    const float left{m_Shape.left + (m_SnapshotFlipped ? offset : -offset)};
    if (m_SnapshotFlipped and left > m_SnapshotPlayerPos.x or not m_SnapshotFlipped and left < m_SnapshotPlayerPos.x)
    {
        m_State = State::WAITING;
        m_SnapshotTaken = false;
        ResetTimer();
    }
}

void Unicorn::Jump(float elapsedSec)
{
    if (not m_SnapshotTaken)
    {
        m_SnapshotPlayerPos = m_pGameController->m_pPlayerManager->GetPlayer()->GetPosition<Point2f>();
        m_SnapshotPos = GetPosition<Point2f>();
        m_SnapshotFlipped = m_Flipped;
        m_SnapshotTaken = true;
        m_LeftOffsetCols = Game::GetRandomBool();
    }
    const float distance{std::abs(m_SnapshotPlayerPos.x - m_SnapshotPos.x)};
    m_Shape.left += (m_SnapshotFlipped ? m_Velocity.x : -m_Velocity.x) * elapsedSec;
    m_Shape.bottom = m_OriginalHeight + CalculateJumpHeight(std::abs(m_Shape.left - m_SnapshotPos.x), distance);
    const float left{m_Shape.left};
    if (m_SnapshotFlipped and left >= m_SnapshotPlayerPos.x or not m_SnapshotFlipped and left <= m_SnapshotPlayerPos.x)
    {
        m_State = Game::GetRandomBool() ? State::WALKING : State::WAITING;
        m_SnapshotTaken = false;
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_BIG_ENEMY_WALK);
    }
}

void Unicorn::Shoot(float elapsedSec)
{
    const Vector2f direction{m_pGameController->m_pPlayerManager->GetPlayer()->GetShapeCenter() - GetShapeCenter()};
    for (GameObject* pThrowable : m_pGameController->m_pEnemyManager->GetThrowables())
    {
        if (pThrowable->GetLabel() == Game::Label::T_FIREBALL_UNICORN and not pThrowable->IsActive())
        {
            Fireball* pFireball{static_cast<Fireball*>(pThrowable)};
            pFireball->Reset();
            pFireball->SetPosition(GetShapeCenter());
            pFireball->SetDirection(direction.Normalized());
            return;
        }
    }
    m_pGameController->m_pEnemyManager->GetThrowables().push_back(
        new Fireball{Game::Label::T_FIREBALL_UNICORN, GetShapeCenter(), direction.Normalized(), m_pGameController}
    );
    // m_pGameController->m_pSoundManager->PlayEffect(Game::Label::F_FIRE_BOSS);
}

void Unicorn::UpdateState()
{
    if (m_Awake and m_State == State::WAITING)
    {
        StartTimer(0.3f);
        if (IsTimerFinished())
        {
            m_State = State::ANGRY;
        }
    }
    else if (m_State == State::ANGRY)
    {
        StartTimer(0.5f);
        if (IsTimerFinished())
        {
            m_State = Game::GetRandomBool() ? State::JUMPING : State::WALKING;
        }
    }
    else if (m_State == State::SHOOTING and m_pSprite->GetIterCount() == 1)
    {
        m_pSprite->ResetIterCount();
        m_State = Game::GetRandomBool() ? (Game::GetRandomBool() ? State::WAITING : State::JUMPING) : State::WALKING;
    }
}

void Unicorn::UpdateSprite()
{
    switch (m_State)
    {
    case State::WAITING:
        m_pSprite->SetTopOffsetRows(0);
        m_pSprite->SetLeftOffsetCols(0);
        m_pSprite->SetSubCols(1);
        break;
    case State::ANGRY:
        m_pSprite->SetTopOffsetRows(4);
        m_pSprite->SetLeftOffsetCols(0);
        m_pSprite->SetSubCols(1);
        break;
    case State::WALKING:
        m_pSprite->SetTopOffsetRows(1);
        m_pSprite->SetLeftOffsetCols(0);
        m_pSprite->SetSubCols(2);
        break;
    case State::JUMPING:
        m_pSprite->SetTopOffsetRows(3);
        m_pSprite->SetLeftOffsetCols(m_LeftOffsetCols);
        m_pSprite->SetSubCols(1);
        break;
    case State::SHOOTING:
        m_pSprite->SetTopOffsetRows(2);
        m_pSprite->SetLeftOffsetCols(0);
        m_pSprite->SetSubCols(3);
        break;
    }
    m_pSprite->SetSubRows(1);
    m_pSprite->SetCurrRowsCols();
    m_pSprite->CalculateFrameTime();
    m_pSprite->UpdateSourceRect();
}

float Unicorn::CalculateJumpHeight(float x, float distance) const
{
    const float a{-LevelManager::GetHillHeight() / std::powf(distance / 2, 2)};
    return a * std::powf(x - distance / 2, 2) + LevelManager::GetHillHeight();
}
