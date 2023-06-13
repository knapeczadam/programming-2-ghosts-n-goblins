#include "pch.h"
#include "Magician.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "fx/FXManager.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"
#include "throwables/Spell.h"

Magician::Magician(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_MAGICIAN, pos, pGameController}
    , m_CanShoot{false}
{
    m_Score = 2000;
    m_AwakeDistance = std::numeric_limits<float>::max();
}

void Magician::Draw() const
{
    GameObject::Draw();
}

// TODO: sometimes it stuck in the second frame 
void Magician::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
    if (m_Awake)
    {
        Awake(elapsedSec);
    }
    else if (m_CanShoot)
    {
        Shoot(elapsedSec);
    }
    else
    {
        Disappear();
    }
}

void Magician::Awake(float elapsedSec)
{
    m_Flipped = IsFlipped();
    if (m_pSprite->GetIterCount() == 4 and m_pSprite->IsLastFrame())
    {
        m_CanShoot = true;
        m_Awake = false;
        m_pSprite->SetLeftOffsetCols(2);
        m_pSprite->SetSubCols(1);
        m_pSprite->SetCurrRowsCols();
        m_pSprite->UpdateSourceRect();
    }
}


void Magician::Shoot(float elapsedSec)
{
    StartTimer(0.5f);
    if (IsTimerFinished())
    {
        m_CanShoot = false;
        m_pSprite->SetLeftOffsetCols(0);
        m_pSprite->SetSubCols(2);
        m_pSprite->SetCurrRowsCols();
        m_pSprite->ResetCurrFrame();
        m_pSprite->ResetIterCount();

        const Vector2f direction{m_pGameController->m_pPlayerManager->GetPlayer()->GetShapeCenter() - GetShapeCenter()};
        for (GameObject* pThrowable : m_pGameController->m_pEnemyManager->GetThrowables())
        {
            if (pThrowable->GetLabel() == Game::Label::T_SPELL and not pThrowable->IsActive())
            {
                Spell* pSpell{static_cast<Spell*>(pThrowable)};
                pSpell->Reset();
                pSpell->SetPosition(GetColliderCenter());
                pSpell->SetDirection(direction.Normalized());
                return;
            }
        }
        m_pGameController->m_pEnemyManager->GetThrowables().push_back(new Spell{GetColliderCenter(), direction.Normalized(), m_pGameController});
    }
}

void Magician::Disappear()
{
    if (m_pSprite->GetIterCount() == 4 and m_pSprite->IsLastFrame())
    {
        Reset();
    }
}

void Magician::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    if (not m_CanShoot) return;
    --m_HP;
    other->SetActive(false);
    other->SetVisible(false);
    other->SetAwake(false);
    if (m_HP == 0)
    {
        Reset();
        m_pGameController->m_pPlayerManager->GetPlayer()->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_PROJECTILE_DEATH, GetContactPoint(other), other->IsFlipped());
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_SCORE, GetContactPoint(other), false, this);
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
    }
}

void Magician::Reset()
{
    IEnemy::Reset();
    ResetTimer();
    m_Active = false;
    m_Visible = false;
    m_CanShoot = false;
    m_pSprite->ResetIterCount();
    m_pSprite->ResetCurrFrame();
}
