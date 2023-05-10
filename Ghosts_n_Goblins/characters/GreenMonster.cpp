#include "pch.h"
#include "GreenMonster.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "fx/FXManager.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"
#include "throwables/Eyeball.h"

GreenMonster::GreenMonster(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_GREEN_MONSTER,  pos, pGameController}
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
    --m_HP;

    other->SetActive(false);
    other->SetVisible(false);
    if (m_HP == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayerManager->GetPlayer()->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_FIRE_ENEMY, GetCollisionBoxCenter(), other->IsFlipped());
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
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
        const Vector2f direction{m_pGameController->m_pPlayerManager->GetPlayer()->GetShapeCenter() - GetShapeCenter()};
        for (GameObject* pThrowable : m_pGameController->m_pEnemyManager->GetThrowables())
        {
            if (pThrowable->GetLabel() == Game::Label::T_EYEBALL and not pThrowable->IsActive())
            {
                Eyeball* pEyeball{dynamic_cast<Eyeball*>(pThrowable)};
                pEyeball->SetActive(true);
                pEyeball->SetVisible(true);
                pEyeball->SetPosition(GetShapeCenter());
                pEyeball->SetDirection(direction.Normalized());
                return;
            }
        }
        m_pGameController->m_pEnemyManager->GetThrowables().push_back(new Eyeball{GetShapeCenter(),direction.Normalized(), m_pGameController});
    }
    
}
