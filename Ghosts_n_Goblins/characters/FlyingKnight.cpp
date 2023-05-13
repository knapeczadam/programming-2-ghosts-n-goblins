#include "pch.h"
#include "FlyingKnight.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "fx/FXManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"

FlyingKnight::FlyingKnight(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_FLYING_KNIGHT, pos, pGameController}
{
    m_Score = 100;
    m_FixedDirection = true;
}

void FlyingKnight::Draw() const
{
    GameObject::Draw();
}

void FlyingKnight::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
    UpdateCollider();
}

void FlyingKnight::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    if (other->IsFlipped())
    {
        --m_HP;
    }
    else
    {
       m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_PROJECTILE_BLOCK_ENEMY, GetContactPoint(other), false); 
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_PROJECTILE_BLOCK);
    }
    other->SetActive(false);
    other->SetVisible(false);
    if (m_HP == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayerManager->GetPlayer()->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_FIRE_ENEMY, GetColliderCenter(),
                                                    other->IsFlipped());
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
    }
}

void FlyingKnight::Fly(float elapsedSec)
{
    IEnemy::Fly(elapsedSec);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_FLYING_KNIGHT);
}
