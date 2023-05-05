#include "pch.h"
#include "Tombstone.h"
#include "throwables/IThrowable.h"
#include "utils.h"
#include "engine/SoundManager.h"
#include <iostream>

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
    m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_PROJECTILE_BLOCK);
    m_HitCount++;
    std::cout << "Tombstone::HandleCollision() - HitCount: " << m_HitCount << std::endl;
    other->SetActive(false);
    // other->SetVisible(false);
}
