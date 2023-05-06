#include "pch.h"
#include "Zombie.h"
#include "engine/SoundManager.h"
#include "Player.h"
#include "game/GameController.h"
#include "fx/FXManager.h"

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
    other->SetActive(false);
    other->SetVisible(false);
    if (m_Health == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayer->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_PROJECTILE_DEATH, GetContactPoint(other), other->IsFlipped());
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
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
