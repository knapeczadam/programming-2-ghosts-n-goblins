#include "pch.h"
#include "Tombstone.h"
#include "weapons/IThrowable.h"
#include "utils.h"
#include "engine/SoundManager.h"
#include <iostream>

Tombstone::Tombstone(const Rectf& shape, SoundManager* pSoundManager)
    : GameObject{Game::Label::L_TOMBSTONE, shape}
      , m_HitCount{0}
      , m_MaxHitCount{15}
      , m_pSoundManager{pSoundManager}
{
}

void Tombstone::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    m_pSoundManager->PlayEffect(Game::Label::E_PROJECTILE_BLOCK);
    m_HitCount++;
    std::cout << "Tombstone::HandleCollision() - HitCount: " << m_HitCount << std::endl;
    other->SetActive(false);
    other->SetVisible(false);
}
