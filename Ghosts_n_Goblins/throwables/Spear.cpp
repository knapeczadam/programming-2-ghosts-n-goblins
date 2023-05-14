#include "pch.h"
#include "Spear.h"

#include "engine/Sprite.h"

Spear::Spear(const Point2f& pos, const Vector2f& direction, GameController* pGameController)
    : GameObject(Game::Label::T_SPEAR, pos, true, pGameController)
{
    m_Direction = direction;
    m_Speed = 100.0f;
    m_AwakeDistance = std::numeric_limits<float>::max();
    m_Shape.left = pos.x;
    m_Shape.bottom = pos.y;
}

void Spear::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
    m_Shape.left += m_Direction.x * m_Speed * elapsedSec;
    m_Shape.bottom += m_Direction.y * m_Speed * elapsedSec;
}

void Spear::Awake(float elapsedSec)
{
    m_Shape.left -= m_pSprite->GetScaledClipWidth() / 2;
    m_Shape.bottom -= m_pSprite->GetScaledClipHeight() / 2;
}
