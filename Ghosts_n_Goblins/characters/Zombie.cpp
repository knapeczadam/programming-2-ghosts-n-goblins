#include "pch.h"
#include "Zombie.h"
#include "engine/SoundManager.h"
#include "Player.h"
#include "game/GameController.h"

Zombie::Zombie(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_ZOMBIE, pos, pGameController}
{
    m_Score = 200;
}

void Zombie::Draw() const
{
    GameObject::Draw();
}

void Zombie::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
}

void Zombie::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_Health;
    if (m_Health == 0)
    {
       m_pGameController->m_pPlayer->AddScore(m_Score); 
    }
}

void Zombie::Walk(float elapsedSec)
{
    IEnemy::Walk(elapsedSec);
}

void Zombie::Spawn()
{
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ZOMBIE_SPAWN);
}
