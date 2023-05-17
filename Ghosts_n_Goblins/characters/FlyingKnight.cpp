#include "pch.h"
#include "FlyingKnight.h"

#include "Player.h"
#include "engine/Clock.h"
#include "engine/SoundManager.h"
#include "fx/FXManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"

 bool FlyingKnight::s_EffectPlaying{false};
int FlyingKnight::s_IdPlayingEffect{-1};

FlyingKnight::FlyingKnight(const Point2f& pos, GameController* pGameController)
    : IEnemy{Game::Label::C_FLYING_KNIGHT, pos, pGameController}
    , m_Amplitude{150.0f}
    , m_CycleOffset{0.0f}
{
    m_Score = 100;
    m_FixedDirection = true;
    m_HorVelocity = 120.0f;
    m_VerVelocity = 2.0f;
    
}

void FlyingKnight::Draw() const
{
    GameObject::Draw();
}

void FlyingKnight::Update(float elapsedSec)
{
    IEnemy::Update(elapsedSec);
    IPotter::Update(elapsedSec);
    Fly(elapsedSec);
    ShowPot();
}

void FlyingKnight::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    if (other->IsFlipped())
    {
        ActivatePot();
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

void FlyingKnight::SetCycleOffset(float offset)
{
    m_CycleOffset = offset;
}

void FlyingKnight::Fly(float elapsedSec)
{
    m_Shape.left -= m_HorVelocity * elapsedSec;
    m_Shape.bottom = m_SpawnPosition.y + std::sin((Clock::GetAccuTime() + m_CycleOffset) * m_VerVelocity) * m_Amplitude;
    PlayEffect();
}

void FlyingKnight::PlayEffect()
{
    if (not s_EffectPlaying)
    {
       s_IdPlayingEffect = m_Id;
        s_EffectPlaying = true;
    }
    if (s_IdPlayingEffect == m_Id)
    {
        StartTimer(1.0f);
        if (IsTimerFinished())
        {
            s_EffectPlaying = m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_FLYING_KNIGHT);
        }
    }
}
