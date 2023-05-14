#include "pch.h"
#include "Fireball.h"

#include "engine/Sprite.h"

Fireball::Fireball(Game::Label label, const Point2f& pos, const Vector2f& direction, GameController* pGameController)
    : GameObject{label, pos, true, pGameController}
{
    m_Direction = direction;
    m_Speed = label == Game::Label::T_FIREBALL_RED_ARREMER ? 300.0f : 200.0f;
    m_AwakeDistance = std::numeric_limits<float>::max();
    m_Shape.left = pos.x;
    m_Shape.bottom = pos.y;
}

void Fireball::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
    if (m_Label == Game::Label::T_FIREBALL_RED_ARREMER)
    {
        m_Shape.left += m_Direction.x * m_Speed * elapsedSec;
        m_Shape.bottom += m_Direction.y * m_Speed * elapsedSec;
    }
    else
    {
        m_Shape.left += (m_Direction.x < 0 ? -1 : 1) * m_Speed * elapsedSec;
    }
}

void Fireball::Awake(float elapsedSec)
{
    m_Shape.left -= m_pSprite->GetScaledClipWidth() / 2;
    m_Shape.bottom -= m_pSprite->GetScaledClipHeight() / 2;
}