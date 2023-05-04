#include "pch.h"
#include "Crow.h"
#include "engine/SoundManager.h"

Crow::Crow(Sprite* pSprite, const Point2f& pos, Player* pPlayer, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_CROW, pSprite, pos, pPlayer, pSoundManager}
{
    m_Score = 100;
}

void Crow::Draw() const
{
    GameObject::Draw();
}

void Crow::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void Crow::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    if (m_Health == 0)
    {
        
    }
}

void Crow::Wait()
{
    IEnemy::Wait();
    m_pSoundManager->PlayEffect(Game::Label::E_CROW);
}

void Crow::Fly()
{
    IEnemy::Fly();
}
