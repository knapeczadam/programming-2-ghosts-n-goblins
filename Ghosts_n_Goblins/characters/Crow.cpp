#include "pch.h"
#include "Crow.h"
#include "engine/SoundManager.h"
#include "Player.h"

#include <iostream>

#include "engine/Clock.h"
#include "engine/Sprite.h"
#include "game/GameController.h"

Crow::Crow(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_CROW, pos, pGameController}
      , m_Amplitude{15.0f}
{
    m_Score = 100;
    m_AwakeDistance = 100.0f; // 256.0f
    m_HorVelocity = 100.0f;
    m_VerVelocity = 20.0f;
}

void Crow::Draw() const
{
    GameObject::Draw();
}

void Crow::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
    if (not m_Awake)
    {
        Wait(elapsedSec);
    }
    else
    {
        Fly(elapsedSec);
    }
    UpdateCollisionBox();
}

void Crow::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    other->SetActive(false);
    // other->SetVisible(false);
    if (m_Health == 0)
    {
        m_pGameController->m_pPlayer->AddScore(m_Score);
        m_Active = false;
        m_Visible = false;
    }
}

void Crow::Awake()
{
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_CROW);
    m_Flipped = IsFlipped();
    m_pSprite->SetSubCols(4);
    m_pSprite->SetCurrRowsCols();
    m_pSprite->SetFramesPerSec(4);
    m_pSprite->CalculateFrameTime();
    StartTimer(0.5f);
}

void Crow::Wait(float elapsedSec)
{
    IEnemy::Wait(elapsedSec);
    m_pSprite->SetSubRows(1);

    const int randInterval{std::rand() % 2 + 1};
    Switch(randInterval);
    
    m_pSprite->CalculateFrameTime();
    m_pSprite->SetCurrRowsCols();
    m_pSprite->UpdateSourceRect();
}

void Crow::Fly(float elapsedSec)
{
    if (IsTimerFinished())
    {
        m_pSprite->SetTopOffsetRows(1);
        m_pSprite->SetCurrRowsCols();
        m_Shape.left += m_HorVelocity * elapsedSec * (m_Flipped ? 1.0f : -1.0f);
        m_Shape.bottom = m_SpawnPos.y + std::sin(Clock::GetAccuTime() * m_VerVelocity) * m_Amplitude;
    }
}

void Crow::Ping()
{
    m_pSprite->SetSubCols(1);
}

void Crow::Pong()
{
    m_pSprite->SetSubCols(3);
    m_pSprite->SetFramesPerSec(6.0f);
}
