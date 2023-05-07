#include "pch.h"
#include "GameObject.h"
#include <cassert>
#include <iostream>

#include "GameController.h"
#include "game/Macros.h"

#include "utils.h"
#include "engine/Sprite.h"
#include "engine/Clock.h"
#include "engine/SpriteFactory.h"
#include "characters/IEnemy.h"

GameObject::GameObject()
    : m_Label{Game::Label::D_DUMMY}
      , m_HasSprite{false}
      , m_pGameController{nullptr}
      , m_pSprite{nullptr}
      , m_Shape{0.0f, 0.0f, 0.0f, 0.0f}
      , m_CollisionBox{0.0f, 0.0f, 0.0f, 0.0f}
      , m_OriginalCollisionBox{m_CollisionBox}
      , m_CollisionEnabled{false}
      , m_Active{true}
      , m_Visible{true}
      , m_Flipped{false}
      , m_CollisionBoxColor{0.5f, 0.5f, 0.5f, 1.0f}
{
}

GameObject::GameObject(Game::Label label, GameController* pGameController)
    : m_Label{label}
      , m_HasSprite{true}
      , m_pGameController{pGameController}
      , m_pSprite{
          m_HasSprite and m_pGameController ? m_pGameController->m_pSpriteFactory->CreateSprite(label) : nullptr
      }
      , m_Shape{0.0f, 0.0f, 0.0f, 0.0f}
      , m_CollisionBox{0.0f, 0.0f, 0.0f, 0.0f}
      , m_OriginalCollisionBox{m_CollisionBox}
      , m_CollisionEnabled{false}
      , m_Active{true}
      , m_Visible{true}
      , m_Flipped{false}
      , m_CollisionBoxColor{0.5f, 0.5f, 0.5f, 1.0f}
{
    InitShape();
    if (m_CollisionEnabled)
    {
        InitCollisionBox();
    }
}

GameObject::GameObject(Game::Label label, const Rectf& shape, bool collisionEnabled, bool hasSprite,
                       const Color4f& color,
                       GameController* pGameController)
    : m_Label{label}
      , m_HasSprite{hasSprite}
      , m_pGameController{pGameController}
      , m_pSprite{
          m_HasSprite and m_pGameController ? m_pGameController->m_pSpriteFactory->CreateSprite(label) : nullptr
      }
      , m_Shape{shape}
      , m_CollisionBox{shape}
      , m_OriginalCollisionBox{m_CollisionBox}
      , m_CollisionEnabled{collisionEnabled}
      , m_Active{true}
      , m_Visible{true}
      , m_Flipped{false}
      , m_CollisionBoxColor{color}
{
}

GameObject::GameObject(Game::Label label, const Point2f& pos, bool collisionEnabled, GameController* pGameController)
    : m_Label{label}
      , m_HasSprite{true}
      , m_pGameController{pGameController}
      , m_pSprite{
          m_HasSprite and m_pGameController ? m_pGameController->m_pSpriteFactory->CreateSprite(label) : nullptr
      }
      , m_Shape{0.0f, 0.0f, 0.0f, 0.0f}
      , m_CollisionBox{0.0f, 0.0f, 0.0f, 0.0f}
      , m_OriginalCollisionBox{m_CollisionBox}
      , m_CollisionEnabled{collisionEnabled}
      , m_Active{true}
      , m_Visible{true}
      , m_Flipped{false}
      , m_CollisionBoxColor{0.5f, 0.5f, 0.5f, 1.0f}
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
        if (m_Flipped)
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
        utils::SetColor(m_CollisionBoxColor);
        utils::DrawRect(m_CollisionBox);
    }
#endif
}

void GameObject::Update(float elapsedSec)
{
    if (m_CollisionEnabled)
    {
        UpdateCollisionBox();
    }
}

void GameObject::LateUpdate(float elapsedSec)
{
    if (m_pSprite)
    {
        m_pSprite->SetPosition(GetPosition<Point2f>());
        m_pSprite->Update(elapsedSec);
    }
}

void GameObject::HandleCollision(GameObject* other)
{
}

Game::Label GameObject::GetLabel() const
{
    return m_Label;
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

bool GameObject::IsFlipped() const
{
    return m_Flipped;
}

Rectf GameObject::GetShape() const
{
    return m_Shape;
}

bool GameObject::IsActive() const
{
    return m_Active;
}

void GameObject::SetActive(bool isActive)
{
    m_Active = isActive;
}

bool GameObject::IsVisible() const
{
    return m_Visible;
}

void GameObject::SetVisible(bool isVisible)
{
    m_Visible = isVisible;
}

bool GameObject::IsOverlapping(GameObject* other) const
{
    return utils::IsOverlapping(m_CollisionBox, other->GetCollisionBox());
}

void GameObject::SetFlipped(bool flipped)
{
    m_Flipped = flipped;
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
    const int dir{m_Flipped ? -1 : 1};
    m_CollisionBox.left = m_Shape.left + horizontalOffset + m_pSprite->GetCollisionHorizontalOffset() * dir;
    m_CollisionBox.bottom = m_Shape.bottom + verticalOffset + m_pSprite->GetCollisionVerticalOffset() * dir;
    m_OriginalCollisionBox = m_CollisionBox;
}

void GameObject::UpdateCollisionBox()
{
    if (m_pSprite)
    {
        const float horizontalOffset{(m_Shape.width - m_pSprite->GetCollisionWidth()) / 2};
        const float verticalOffset{(m_Shape.height - m_pSprite->GetCollisionHeight()) / 2};
        const int dir{m_Flipped ? -1 : 1};
        m_CollisionBox.left = m_Shape.left + horizontalOffset + m_pSprite->GetCollisionHorizontalOffset() * dir;
        m_CollisionBox.bottom = m_Shape.bottom + verticalOffset + m_pSprite->GetCollisionVerticalOffset() * dir;
    }
    else
    {
        m_CollisionBox = m_Shape;
    }
}

std::vector<Point2f> GameObject::GetCollisionBoxVertices() const
{
    std::vector<Point2f> vertices{
        Point2f{m_CollisionBox.left, m_CollisionBox.bottom},
        Point2f{m_CollisionBox.left + m_CollisionBox.width, m_CollisionBox.bottom},
        Point2f{m_CollisionBox.left + m_CollisionBox.width, m_CollisionBox.bottom + m_CollisionBox.height},
        Point2f{m_CollisionBox.left, m_CollisionBox.bottom + m_CollisionBox.height}
    };
    return vertices;
}

void GameObject::SetCollisionBoxHeight(float height)
{
    m_CollisionBox.height = height;
}

void GameObject::ResetCollisionBox()
{
    m_CollisionBox = m_OriginalCollisionBox;
}

Point2f GameObject::GetContactPoint(const GameObject* other) const
{
    Point2f contactPoint;
    contactPoint.y = other->GetCollisionBoxCenter().y;
    if (other->IsFlipped())
    {
        contactPoint.x = other->GetCollisionBox().left;
    }
    else
    {
        contactPoint.x = other->GetCollisionBox().left + other->GetCollisionBox().width;
    }
    return contactPoint;
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
    if (not m_pSprite)
    {
        std::cerr << "GameObject::InitShape() > No sprite attached - label: " << static_cast<int>(m_Label) << '\n';
        std::abort();
    }
    m_Shape.width = m_pSprite->GetScaledClipWidth();
    m_Shape.height = m_pSprite->GetScaledClipHeight();
}

void GameObject::InitShape(const Point2f& pos)
{
    if (not m_pSprite)
    {
        std::cerr << "GameObject::InitShape(const Point2f&) > No sprite attached - label: " << static_cast<int>(m_Label)
            << '\n';
        std::abort();
    }
    m_Shape.left = pos.x;
    m_Shape.bottom = pos.y;
    m_Shape.width = m_pSprite->GetScaledClipWidth();
    m_Shape.height = m_pSprite->GetScaledClipHeight();
}
