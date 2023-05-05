#include "pch.h"
#include "Eyeball.h"

Eyeball::Eyeball(const Point2f& pos, const Vector2f& direction, GameController* pGameController)
    : GameObject{Game::Label::T_EYEBALL, pos, true, pGameController}
    , m_Direction{direction}
    , m_Speed{100.0f}
{
}

void Eyeball::Update(float elapsedSec)
{
    m_Shape.left += m_Direction.x * m_Speed * elapsedSec;
    m_Shape.bottom += m_Direction.y * m_Speed * elapsedSec;
    GameObject::Update(elapsedSec);
}

void Eyeball::SetDirection(const Vector2f& direction)
{
    m_Direction = direction;
}
