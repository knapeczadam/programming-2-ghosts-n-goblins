#include "pch.h"
#include "Unicorn.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "fx/FXManager.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"
#include "throwables/Fireball.h"

Unicorn::Unicorn(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_UNICORN, pos, pGameController}
{
    m_Score = 2000;
    m_HP = 10;
    m_AwakeDistance = 200.0f;
}

void Unicorn::Draw() const
{
    GameObject::Draw();
}

void Unicorn::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
}

void Unicorn::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_HP;
    other->SetActive(false);
    other->SetVisible(false);
    m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_PROJECTILE_BLOCK_BOSS, GetContactPoint(other), false);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_BOSS_HIT);
    if (m_HP == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayerManager->GetPlayer()->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_FIRE_BOSS, GetColliderCenter(), other->IsFlipped());
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_SCORE, GetColliderCenter(), other->IsFlipped(), this);
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_BOSS_DEATH);
    }
}

void Unicorn::Awake(float elapsedSec)
{
}

void Unicorn::Wait(float elapsedSec)
{
    IEnemy::Wait(elapsedSec);
}

void Unicorn::Walk(float elapsedSec)
{
    IEnemy::Walk(elapsedSec);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_BIG_ENEMY_WALK);
}

void Unicorn::Jump(float elapsedSec)
{
    IEnemy::Jump(elapsedSec);
}

void Unicorn::Shoot(float elapsedSec)
{
    const int randInterval{std::rand() % 2 + 1};
    StartTimer(randInterval);
    if (IsTimerFinished())
    {
        const Vector2f direction{m_pGameController->m_pPlayerManager->GetPlayer()->GetShapeCenter() - GetShapeCenter()};
        for (GameObject* pThrowable : m_pGameController->m_pEnemyManager->GetThrowables())
        {
            if (pThrowable->GetLabel() == Game::Label::T_FIREBALL_UNICORN and not pThrowable->IsActive())
            {
                Fireball* pFireball{static_cast<Fireball*>(pThrowable)};
                pFireball->Reset();
                pFireball->SetPosition(GetShapeCenter());
                pFireball->SetDirection(direction.Normalized());
                return;
            }
        }
        m_pGameController->m_pEnemyManager->GetThrowables().push_back(
            new Fireball{Game::Label::T_FIREBALL_UNICORN, GetShapeCenter(), direction.Normalized(), m_pGameController}
            );
    }
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::F_FIRE_BOSS);
}
