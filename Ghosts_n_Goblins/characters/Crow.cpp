#include "pch.h"
#include "Crow.h"
#include "engine/SoundManager.h"
#include "Player.h"

#include <iostream>

#include "engine/Clock.h"

Crow::Crow(const Point2f& pos, Player* pPlayer, SpriteFactory* pSpriteFactory, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_CROW, pos, pPlayer, pSpriteFactory, pSoundManager}
    , m_Amplitude{10.0f}
{
    m_Score = 100;
    m_AwakeDistance = 256.0f;
    m_HorVelocity = 100.0f;
    m_VerVelocity = 10.0f;
    
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
    other->SetVisible(false);
    if (m_Health == 0)
    {
        m_pPlayer->AddScore(m_Score);
        m_Active = false;
        m_Visible = false;
    }
}

void Crow::Awake()
{
    std::cout << "Crow::Awake()\n";
    m_pSoundManager->PlayEffect(Game::Label::E_CROW);
    m_Flipped = IsFlipped();
    StartTimer(0.5f);
}

void Crow::Wait(float elapsedSec)
{
    IEnemy::Wait(elapsedSec);
}

void Crow::Fly(float elapsedSec)
{
   if (IsTimerFinished())
   {
       m_Shape.left += m_HorVelocity * elapsedSec * (m_Flipped ? 1.0f : -1.0f);
       m_Shape.bottom =m_SpawnPos.y + std::sin(Clock::GetAccuTime() * m_VerVelocity) * m_Amplitude;
         
    }
}
