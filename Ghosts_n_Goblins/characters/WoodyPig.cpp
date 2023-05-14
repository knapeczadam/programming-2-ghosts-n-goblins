#include "pch.h"
#include "WoodyPig.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "fx/FXManager.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"
#include "throwables/Spear.h"

WoodyPig::WoodyPig(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_WOODY_PIG, pos, pGameController}
{
    m_Score = 100;
}

void WoodyPig::Draw() const
{
    GameObject::Draw();
}

void WoodyPig::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
    UpdateCollider();
}

void WoodyPig::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_HP;
    other->SetActive(false);
    other->SetVisible(false);
    if (m_HP == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayerManager->GetPlayer()->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_FIRE_ENEMY, GetColliderCenter(), other->IsFlipped());
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
    }
}

void WoodyPig::Shoot(float elapsedSec)
{
    const int randInterval{std::rand() % 2 + 1}; 
    StartTimer(randInterval);
    if (IsTimerFinished())
    {
        const Vector2f direction{m_pGameController->m_pPlayerManager->GetPlayer()->GetShapeCenter() - GetShapeCenter()};
        for (GameObject* pThrowable : m_pGameController->m_pEnemyManager->GetThrowables())
        {
            if (pThrowable->GetLabel() == Game::Label::T_SPEAR and not pThrowable->IsActive())
            {
                Spear* pSpear{static_cast<Spear*>(pThrowable)};
                pSpear->Reset();
                pSpear->SetPosition(GetShapeCenter());
                pSpear->SetDirection(direction.Normalized());
                return;
            }
        }
        m_pGameController->m_pEnemyManager->GetThrowables().push_back(new Spear{GetShapeCenter(),direction.Normalized(), m_pGameController});
    }
}

void WoodyPig::Fly(float elapsedSec)
{
    IEnemy::Fly(elapsedSec);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_WOODY_PIG);
}
