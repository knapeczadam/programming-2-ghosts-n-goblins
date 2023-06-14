#include "pch.h"
#include "Eyeball.h"

#include "engine/Sprite.h"

Eyeball::Eyeball(const Point2f& pos, const Vector2f& direction, GameController* pGameController)
    : GameObject{Game::Label::T_EYEBALL, pos, true, pGameController}
{
    m_Direction = direction;
    m_Speed.x = 200.0f;
    m_Shape.left = pos.x;
    m_Shape.bottom = pos.y;
}

void Eyeball::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
    m_Shape.left += m_Direction.x * m_Speed.x * elapsedSec;
    m_Shape.bottom += m_Direction.y * m_Speed.x * elapsedSec;
}

void Eyeball::Awake(float elapsedSec)
{
    m_Shape.left -= m_pSprite->GetScaledClipWidth() / 2;
    m_Shape.bottom -= m_pSprite->GetScaledClipHeight() / 2;
}
