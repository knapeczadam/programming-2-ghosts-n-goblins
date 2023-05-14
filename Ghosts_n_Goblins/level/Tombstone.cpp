#include "pch.h"
#include "Tombstone.h"

#include "engine/SoundManager.h"
#include "fx/FXManager.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"

Tombstone::Tombstone(const Rectf& shape, GameController* pGameController)
    : GameObject{Game::Label::L_TOMBSTONE, shape, true, false, Color4f{0.0f, 0.0f, 1.0f, 0.5f}, pGameController}
      , m_HitCount{0}
      , m_MaxHitCount{15}
{
    m_HasSprite = false;
}

void Tombstone::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    m_HitCount++;
    other->SetActive(false);
    other->SetVisible(false);
    m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_PROJECTILE_BLOCK_ENEMY, GetContactPoint(other), other->IsFlipped());
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_PROJECTILE_BLOCK);
    if (m_HitCount == m_MaxHitCount)
    {
        GameObject* pMagician{m_pGameController->m_pEnemyManager->GetMagician()};
        pMagician->SetActive(true);
        pMagician->SetVisible(true);
        pMagician->SetAwake(true);
        const float x { m_Shape.left + m_Shape.width / 2.0f - pMagician->GetShape().width / 2.0f};
        const float y{m_Shape.bottom + m_Shape.height};
        pMagician->SetPosition(Point2f{x, y});
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_MAGICIAN);
        }
    }
