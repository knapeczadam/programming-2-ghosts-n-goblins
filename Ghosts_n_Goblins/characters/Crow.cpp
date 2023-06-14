#include "pch.h"
#include "Crow.h"

#include "Player.h"
#include "engine/Clock.h"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "fx/FXManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"

Crow::Crow(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_CROW, pos, pGameController}
    , m_Amplitude{15.0f}
{
    m_Score = 100;
    m_AwakeDistance = 240.0f;
    m_HorVelocity = 100.0f;
    m_VerVelocity = 20.0f;
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
}

void Crow::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_HP;
    other->SetActive(false);
    other->SetVisible(false);
    if (m_HP == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayerManager->GetPlayer()->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_PROJECTILE_DEATH, GetContactPoint(other), other->IsFlipped());
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
    }
}

void Crow::Awake(float elapsedSec)
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

    Switch(Game::GetRandomFloat(1.0f, 2.0f));

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
        m_Shape.bottom = m_SpawnPosition.y + std::sin(Clock::GetAccuTime() * m_VerVelocity) * m_Amplitude;
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
