#include "pch.h"
#include "Spear.h"

#include "engine/Sprite.h"

Spear::Spear(const Point2f& pos, const Vector2f& direction, bool down, GameController* pGameController)
    : GameObject(down ? Game::Label::T_SPEAR_Y : Game::Label::T_SPEAR_X, pos, true, pGameController)
    , m_Down{down}
{
    m_Direction = direction;
    m_Speed.x = 100.0f;
    m_AwakeDistance = std::numeric_limits<float>::max();
    m_Shape.left = pos.x;
    m_Shape.bottom = pos.y;
}

void Spear::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
    if (m_Down)
    {
        m_Shape.bottom -= m_Speed.x * elapsedSec;
    }
    else
    {
        m_Shape.left += (m_Direction.x > 0 ? 1 : -1) * m_Speed.x * elapsedSec;
    }
}

void Spear::Awake(float elapsedSec)
{
    m_Shape.left -= m_pSprite->GetScaledClipWidth() / 2;
    m_Shape.bottom -= m_pSprite->GetScaledClipHeight() / 2;
    
}

void Spear::SetDown(bool down)
{
    m_Down = down;
}
