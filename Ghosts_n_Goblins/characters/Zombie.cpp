#include "pch.h"
#include "Zombie.h"
#include "engine/SoundManager.h"

Zombie::Zombie(Sprite* pSprite, const Point2f& pos, Player* pPlayer, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_ZOMBIE, pSprite, pos, pPlayer, pSoundManager}
{
    m_Score = 200;
}

void Zombie::Draw() const
{
    GameObject::Draw();
}

void Zombie::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void Zombie::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    if (m_Health == 0)
    {
        
    }
}

void Zombie::Walk()
{
    IEnemy::Walk();
}

void Zombie::Spawn()
{
    m_pSoundManager->PlayEffect(Game::Label::E_ZOMBIE_SPAWN);
}
