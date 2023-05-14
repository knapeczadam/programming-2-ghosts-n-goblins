#include "pch.h"
#include "Spell.h"

#include "engine/Sprite.h"

Spell::Spell(const Point2f& pos, const Vector2f& direction, GameController* pGameController)
    : GameObject{Game::Label::T_SPELL, pos, true, pGameController}
{
    m_Direction = direction;
    m_Speed = 200.0f;
    m_AwakeDistance = std::numeric_limits<float>::max();
    m_Shape.left = pos.x;
    m_Shape.bottom = pos.y;
}

void Spell::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
    m_Shape.left += (m_Direction.x < 0 ? -1 : 1) * m_Speed * elapsedSec;
}

void Spell::Awake(float elapsedSec)
{
    m_Shape.left -= m_pSprite->GetScaledClipWidth() / 2;
    m_Shape.bottom -= m_pSprite->GetScaledClipHeight() / 2;
}