#include "pch.h"
#include "FlyingKnight.h"
#include "engine/SoundManager.h"
#include "Player.h"
#include "game/GameController.h"

FlyingKnight::FlyingKnight(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_FLYING_KNIGHT, pos, pGameController}
{
    m_Score = 100;
}

void FlyingKnight::Draw() const
{
    GameObject::Draw();
}

void FlyingKnight::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
}

void FlyingKnight::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    if (m_Health == 0)
    {
        m_pGameController->m_pPlayer->AddScore(m_Score);
    }
}

void FlyingKnight::Fly(float elapsedSec)
{
    IEnemy::Fly(elapsedSec);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_FLYING_KNIGHT);
}
