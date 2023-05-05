#include "pch.h"
#include "GreenMonster.h"
#include "engine/SoundManager.h"
#include "Player.h"
#include "weapons/Eyeball.h"

GreenMonster::GreenMonster(const Point2f& pos, Player* pPlayer, SpriteFactory* pSpriteFactory, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_GREEN_MONSTER,  pos, pPlayer, pSpriteFactory, pSoundManager}
    // , m_Enemies{std::move(enemies)}
{
    m_Score = 100;
    
}

void GreenMonster::Draw() const
{
    GameObject::Draw();
}

void GreenMonster::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
    if (not m_Awake)
    {
        Wait(elapsedSec);
    }
    else
    {
       Shoot(elapsedSec);
        m_Flipped = IsFlipped();
    }
}

void GreenMonster::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    if (m_Health == 0)
    {
        m_pPlayer->AddScore(m_Score);
    }
}

void GreenMonster::Wait(float elapsedSec)
{
    IEnemy::Wait(elapsedSec);
}

void GreenMonster::Shoot(float elapsedSec)
{
    const int randInterval{std::rand() % 2 + 1}; 
    StartTimer(randInterval);
    if (IsTimerFinished())
    {
        // m_Enemies.push_back(new Eyeball)
    }
    
}
