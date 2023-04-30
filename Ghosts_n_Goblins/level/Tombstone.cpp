#include "pch.h"
#include "Tombstone.h"
#include "weapons/IThrowable.h"
#include "utils.h"
#include <iostream>

Tombstone::Tombstone(const Rectf& shape)
    : GameObject{Game::Label::TOMBSTONE, shape}
      , m_HitCount{0}
      , m_MaxHitCount{15}
{
}

void Tombstone::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    m_HitCount++;
    std::cout << "Tombstone::HandleCollision() - HitCount: " << m_HitCount << std::endl;
    other->SetActive(false);
}
