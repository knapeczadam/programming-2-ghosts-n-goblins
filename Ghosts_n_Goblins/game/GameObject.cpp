#include "pch.h"
#include "GameObject.h"
#include <cassert>
#include "game/Macros.h"

#include "utils.h"
#include "engine/Sprite.h"
#include "engine/Clock.h"

GameObject::GameObject()
    : m_Label{Game::Label::DUMMY}
      , m_pSprite{}
      , m_Shape{}
      , m_CollisionBox{}
      , m_CollisionEnabled{false}
      , m_IsActive{true}
      , m_IsVisible{true}
      , m_IsFlipped{false}
{
}

GameObject::GameObject(Game::Label label, bool collisionEnabled)
    : m_Label{label}
      , m_pSprite{}
      , m_Shape{}
      , m_CollisionBox{}
      , m_CollisionEnabled{collisionEnabled}
      , m_IsActive{true}
      , m_IsVisible{true}
      , m_IsFlipped{false}
{
}

GameObject::GameObject(Game::Label label, Sprite* pSprite, bool collisionEnabled)
    : m_Label{label}
      , m_pSprite{pSprite}
      , m_Shape{}
      , m_CollisionBox{}
      , m_CollisionEnabled{collisionEnabled}
      , m_IsActive{true}
      , m_IsVisible{true}
      , m_IsFlipped{false}
{
    InitShape();
    if (m_CollisionEnabled)
    {
        InitCollisionBox();
    }
}

GameObject::GameObject(Game::Label label, const Rectf& shape, bool collisionEnabled)
    : m_Label{label}
      , m_pSprite{}
      , m_Shape{shape}
      , m_CollisionBox{shape}
      , m_CollisionEnabled{collisionEnabled}
      , m_IsActive{true}
      , m_IsVisible{true}
      , m_IsFlipped{false}
{
}

GameObject::GameObject(Game::Label label, Sprite* pSprite, const Point2f& pos, bool collisionEnabled)
    : m_Label{label}
      , m_pSprite{pSprite}
      , m_Shape{}
      , m_CollisionBox{}
      , m_CollisionEnabled{collisionEnabled}
      , m_IsActive{true}
      , m_IsVisible{true}
      , m_IsFlipped{false}
{
    InitShape(pos);
    if (m_CollisionEnabled)
    {
        InitCollisionBox();
    }
}

void GameObject::Draw() const
{
    if (m_pSprite)
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
#if DEBUG_COLLISION
    if (m_CollisionEnabled)
    {
        utils::SetColor(Color4f{0, 1, 1, 1});
        utils::DrawRect(m_CollisionBox);
    }
#endif
}

void GameObject::Update(float elapsedSec)
{
}

void GameObject::LateUpdate(float elapsedSec)
{
    if (m_pSprite)
    {
        m_pSprite->SetPosition(GetPosition<Point2f>());
        m_pSprite->Update(elapsedSec);
    }
    if (m_CollisionEnabled)
    {
        UpdateCollisionBox();
    }
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

bool GameObject::IsVisible() const
{
    return m_IsVisible;
}

void GameObject::SetVisible(bool isVisible)
{
    m_IsVisible = isVisible;
}

bool GameObject::IsOverlapping(GameObject* other) const
{
    return utils::IsOverlapping(m_CollisionBox, other->GetCollisionBox());
}

Rectf GameObject::GetCollisionBox() const
{
    return m_CollisionBox;
}

Point2f GameObject::GetCollisionBoxCenter() const
{
    Point2f center;
    center.x = m_CollisionBox.left + m_CollisionBox.width / 2;
    center.y = m_CollisionBox.bottom + m_CollisionBox.height / 2;
    return center;
}

void GameObject::InitCollisionBox()
{
    m_CollisionBox.width = m_pSprite->GetCollisionWidth();
    m_CollisionBox.height = m_pSprite->GetCollisionHeight();
    const float horizontalOffset{(m_Shape.width - m_pSprite->GetCollisionWidth()) / 2};
    const float verticalOffset{(m_Shape.height - m_pSprite->GetCollisionHeight()) / 2};
    m_CollisionBox.left = m_Shape.left + verticalOffset;
    m_CollisionBox.bottom = m_Shape.bottom + horizontalOffset;
}

void GameObject::UpdateCollisionBox()
{
    if (m_pSprite)
    {
        const float horizontalOffset{(m_Shape.width - m_pSprite->GetCollisionWidth()) / 2};
        const float verticalOffset{(m_Shape.height - m_pSprite->GetCollisionHeight()) / 2};
        m_CollisionBox.left = m_Shape.left + horizontalOffset;
        m_CollisionBox.bottom = m_Shape.bottom + verticalOffset;
    }
    else
    {
        m_CollisionBox = m_Shape;
    }
}

Point2f GameObject::GetShapeCenter() const
{
    Point2f center;
    center.x = m_Shape.left + m_Shape.width / 2;
    center.y = m_Shape.bottom + m_Shape.height / 2;
    return center;
}

void GameObject::SetBottom(float bottom)
{
    const float verticalOffset{(m_Shape.height - m_pSprite->GetCollisionHeight()) / 2};
    m_Shape.bottom = bottom - verticalOffset;
}

void GameObject::SetLeft(float left)
{
    const float horizontalOffset{(m_Shape.width - m_pSprite->GetCollisionWidth()) / 2};
    m_Shape.left = left - horizontalOffset;
}

void GameObject::InitShape()
{
    assert(m_pSprite != nullptr && "GameObject::InitShape() - m_pSprite is null!");
    m_Shape.width = m_pSprite->GetScaledClipWidth();
    m_Shape.height = m_pSprite->GetScaledClipHeight();
}

void GameObject::InitShape(const Point2f& pos)
{
    assert(m_pSprite != nullptr && "GameObject::InitShape() - m_pSprite is null!");
    m_Shape.left = pos.x;
    m_Shape.bottom = pos.y;
    m_Shape.width = m_pSprite->GetScaledClipWidth();
    m_Shape.height = m_pSprite->GetScaledClipHeight();
}
