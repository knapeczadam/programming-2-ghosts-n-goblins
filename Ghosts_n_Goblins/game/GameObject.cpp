#include "pch.h"
#include "GameObject.h"
#include <cassert>

#include "utils.h"
#include "engine/Sprite.h"

GameObject::GameObject()
    : m_Label{Game::Label::DUMMY}
      , m_pSprite{}
      , m_Shape{}
      , m_IsActive{true}
      , m_IsFlipped{false}
{
}

GameObject::GameObject(Game::Label label)
    : m_Label{label}
      , m_pSprite{}
      , m_Shape{}
      , m_IsActive{true}
      , m_IsFlipped{false}
{
}

GameObject::GameObject(Game::Label label, Sprite* pSprite)
    : m_Label{label}
      , m_pSprite{pSprite}
      , m_Shape{}
      , m_IsActive{true}
      , m_IsFlipped{false}
{
    InitShape();
}

GameObject::GameObject(Game::Label label, const Rectf& shape)
    : m_Label{label}
      , m_pSprite{}
      , m_Shape{shape}
      , m_IsActive{true}
      , m_IsFlipped{false}
{
}

GameObject::GameObject(Game::Label label, Sprite* pSprite, const Point2f& pos)
    : m_Label{label}
      , m_pSprite{pSprite}
      , m_Shape{}
      , m_IsActive{true}
      , m_IsFlipped{false}
{
    InitShape(pos);
}

void GameObject::Draw() const
{
    if (m_IsFlipped)
    {
        m_pSprite->DrawFlipped();    
    }
    else
    {
        m_pSprite->Draw();
    }
}

void GameObject::Update(float elapsedSec)
{
    m_pSprite->SetPosition(GetPosition<Point2f>());
    m_pSprite->Update(elapsedSec);
}

void GameObject::HandleCollision(GameObject* other)
{
}

Game::Label GameObject::GetLabel() const
{
    return m_Label;
}

void GameObject::SetLabel(Game::Label label)
{
    m_Label = label;
}


void GameObject::SetPosition(const Point2f& position)
{
    m_Shape.left = position.x;
    m_Shape.bottom = position.y;
}

Sprite* GameObject::GetSprite() const
{
    return m_pSprite;
}

void GameObject::SetSprite(Sprite* pSprite)
{
    m_pSprite = pSprite;
}

Rectf GameObject::GetShape() const
{
    return m_Shape;
}

bool GameObject::IsActive() const
{
    return m_IsActive;
}

void GameObject::SetActive(bool isActive)
{
    m_IsActive = isActive;
}

bool GameObject::IsOverlapping(GameObject* other) const
{
    return utils::IsOverlapping(m_Shape, other->GetShape());
}

Point2f GameObject::GetCenter() const
{
    Point2f center;
    center.x = m_Shape.left + m_Shape.width / 2;
    center.y = m_Shape.bottom + m_Shape.height / 2;
    return center;
}

void GameObject::SetBottom(float bottom)
{
    m_Shape.bottom = bottom;
}

void GameObject::SetLeft(float left)
{
    m_Shape.left = left;
}

void GameObject::InitShape()
{
    assert(m_pSprite != nullptr && "GameObject::InitShape() - m_pSprite is null!");
    m_Shape.width = m_pSprite->GetClipWidth() * m_pSprite->GetScale();
    m_Shape.height = m_pSprite->GetClipHeight() * m_pSprite->GetScale();
}

void GameObject::InitShape(const Point2f& pos)
{
    assert(m_pSprite != nullptr && "GameObject::InitShape() - m_pSprite is null!");
    m_Shape.left = pos.x;
    m_Shape.bottom = pos.y;
    m_Shape.width = m_pSprite->GetClipWidth() * m_pSprite->GetScale();
    m_Shape.height = m_pSprite->GetClipHeight() * m_pSprite->GetScale();
}
