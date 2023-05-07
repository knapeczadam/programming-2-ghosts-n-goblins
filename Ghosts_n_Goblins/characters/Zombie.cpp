#include "pch.h"
#include "Zombie.h"
#include "engine/SoundManager.h"
#include "Player.h"
#include "engine/Sprite.h"
#include "game/GameController.h"
#include "fx/FXManager.h"

#include <numeric>

Zombie::Zombie(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_ZOMBIE, pos, pGameController}
      , m_MinWalingTime{2.0f}
      , m_MaxWalingTime{8.0f}
      , m_WalkingTime{0.66f}
      , m_SpawnTime{0.8f}
      , m_CanWalk{false}
      , m_Dir{}
{
    m_Score = 200;
    m_HorVelocity = 50.0f;
    m_FixedDirection = true;
    m_AwakeDistance = std::numeric_limits<float>::max();
}

void Zombie::Draw() const
{
    GameObject::Draw();
}

void Zombie::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
    if (m_Awake)
    {
        Spawn(elapsedSec);
    }
    else if (m_CanWalk)
    {
        Walk(elapsedSec);
    }
    else
    {
        Sleep(elapsedSec);
    }
    UpdateCollisionBox();
}

void Zombie::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    --m_HP;
    other->SetActive(false);
    other->SetVisible(false);
    if (m_HP == 0)
    {
        m_Active = false;
        m_Visible = false;
        m_pGameController->m_pPlayer->AddScore(m_Score);
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_PROJECTILE_DEATH, GetContactPoint(other),
                                                    other->IsFlipped());
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
    }
}

void Zombie::Walk(float elapsedSec)
{
    m_Shape.left += m_HorVelocity * elapsedSec * m_Dir;
    StartTimer(m_WalkingTime);
    if (IsTimerFinished())
    {
        m_pSprite->ResetCurrFrame();
        m_pSprite->SetLeftOffsetCols(9);
        m_pSprite->SetSubCols(7);
        m_pSprite->SetCurrRowsCols();
        m_CanWalk = false;
    }
}

void Zombie::Spawn(float elapsedSec)
{
    m_Shape.left += m_HorVelocity * elapsedSec * m_Dir;
    StartTimer(m_SpawnTime);
    if (IsTimerFinished())
    {
        m_pSprite->SetLeftOffsetCols(7);
        m_pSprite->SetSubCols(2);
        m_pSprite->SetCurrRowsCols();
        m_pSprite->ResetCurrFrame();
        m_CanWalk = true;
        m_Awake = false;
        const int min{int(m_MinWalingTime * 10)};
        const int max{int(m_MaxWalingTime * 10)};
        m_WalkingTime = float(rand() % (max - min + 1) + min) / 10.0f;
    }
}

void Zombie::Awake(float elapsedSec)
{
    m_Flipped = IsFlipped();
    m_Dir = m_Flipped ? 1 : -1;
    m_pSprite->SetLeftOffsetCols(0);
    m_pSprite->ResetCurrFrame();
}

void Zombie::Sleep(float elapsedSec)
{
    m_Shape.left += m_HorVelocity * elapsedSec * m_Dir;
    StartTimer(m_SpawnTime);
    if (IsTimerFinished())
    {
        m_AwakeFired = false;
        m_Active = false;
        m_Visible = false;
    }
}
