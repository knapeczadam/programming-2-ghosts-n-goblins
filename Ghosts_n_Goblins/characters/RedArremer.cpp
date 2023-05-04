#include "pch.h"
#include "RedArremer.h"
#include "engine/SoundManager.h"
#include "Player.h"

RedArremer::RedArremer(Sprite* pSprite, const Point2f& pos, Player* pPlayer, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_RED_ARREMER, pSprite, pos, pPlayer, pSoundManager}
{
    m_Score = 1000;
}

void RedArremer::Draw() const
{
    GameObject::Draw();
}

void RedArremer::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void RedArremer::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    if (m_Health == 0)
    {
       m_pPlayer->AddScore(m_Score); 
    }
}

void RedArremer::Wait()
{
    IEnemy::Wait();
}

void RedArremer::Walk()
{
    IEnemy::Walk();
}

void RedArremer::Shoot()
{
    IEnemy::Shoot();
    m_pSoundManager->PlayEffect(Game::Label::E_RED_ARREMER_ATTACK);
}

void RedArremer::Fly()
{
    IEnemy::Fly();
}
