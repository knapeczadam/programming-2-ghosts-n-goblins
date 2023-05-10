#include "pch.h"
#include "WoodyPig.h"

#include "Player.h"
#include "engine/SoundManager.h"
#include "fx/FXManager.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"

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
    UpdateCollisionBox();
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
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_FIRE_ENEMY, GetCollisionBoxCenter(), other->IsFlipped());
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ENEMY_DEATH);
    }
}

void WoodyPig::Shoot(float elapsedSec)
{
    IEnemy::Shoot(elapsedSec);
}

void WoodyPig::Fly(float elapsedSec)
{
    IEnemy::Fly(elapsedSec);
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_WOODY_PIG);
}
