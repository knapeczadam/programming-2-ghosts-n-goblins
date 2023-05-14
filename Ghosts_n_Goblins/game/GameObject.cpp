#include "pch.h"
#include "GameObject.h"

#include "GameController.h"
#include "utils.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/Macros.h"

#include <iostream>

#include "PlayerManager.h"
#include "characters/Player.h"

GameObject::GameObject(GameController* pGameController)
    : m_Label{Game::Label::D_DUMMY}
      , m_HasSprite{false}
      , m_pGameController{pGameController}
      , m_pSprite{nullptr}
      , m_Shape{0.0f, 0.0f, 0.0f, 0.0f}
      , m_Collider{0.0f, 0.0f, 0.0f, 0.0f}
      , m_OriginalCollider{m_Collider}
      , m_CollisionEnabled{false}
      , m_Active{true}
      , m_Visible{true}
        , m_Awake{false}
      , m_AwakeFired{false}
      , m_AwakeDistance{0.0f}
      , m_Flipped{false}
      , m_ColliderColor{0.5f, 0.5f, 0.5f, 1.0f}
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
      , m_Collider{0.0f, 0.0f, 0.0f, 0.0f}
      , m_OriginalCollider{m_Collider}
      , m_CollisionEnabled{false}
      , m_Active{true}
      , m_Visible{true}
        , m_Awake{false}
      , m_AwakeFired{false}
      , m_AwakeDistance{0.0f}
      , m_Flipped{false}
      , m_ColliderColor{0.5f, 0.5f, 0.5f, 1.0f}
{
    InitShape();
    if (m_CollisionEnabled)
    {
        InitCollider();
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
      , m_Collider{shape}
      , m_OriginalCollider{m_Collider}
      , m_CollisionEnabled{collisionEnabled}
      , m_Active{true}
      , m_Visible{true}
        , m_Awake{false}
      , m_AwakeFired{false}
      , m_AwakeDistance{0.0f}
      , m_Flipped{false}
      , m_ColliderColor{color}
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
      , m_Collider{0.0f, 0.0f, 0.0f, 0.0f}
      , m_OriginalCollider{m_Collider}
      , m_CollisionEnabled{collisionEnabled}
      , m_Active{true}
      , m_Visible{true}
        , m_Awake{false}
      , m_AwakeFired{false}
      , m_AwakeDistance{0.0f}
      , m_Flipped{false}
      , m_ColliderColor{0.5f, 0.5f, 0.5f, 1.0f}
{
    InitShape(pos);
    if (m_CollisionEnabled)
    {
        InitCollider();
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
#if DEBUG_COLLIDER
    if (m_CollisionEnabled)
    {
        utils::SetColor(m_ColliderColor);
        utils::DrawRect(m_Collider);
    }
#endif
}

void GameObject::Awake(float elapsedSec)
{
}

void GameObject::Update(float elapsedSec)
{
    if (m_CollisionEnabled)
    {
        UpdateCollider();
    }
    if (not m_AwakeFired)
    {
        if (utils::GetDistance(GetShapeCenter(), m_pGameController->m_pPlayerManager->GetPlayer()->GetShapeCenter()) < m_AwakeDistance)
        {
            m_Awake = true;
        }
    }

    if (m_Awake)
    {
        if (not m_AwakeFired)
        {
            Awake(elapsedSec);
            m_AwakeFired = true;
        }
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

bool GameObject::IsAwake() const
{
    return m_Awake;
}

void GameObject::SetAwake(bool awake)
{
    m_Awake = awake;
    if (not m_Awake)
    {
        m_AwakeFired = false;
    }
}

bool GameObject::IsOverlapping(GameObject* other) const
{
    return utils::IsOverlapping(m_Collider, other->GetCollider());
}

void GameObject::SetFlipped(bool flipped)
{
    m_Flipped = flipped;
}

Rectf GameObject::GetCollider() const
{
    return m_Collider;
}

Point2f GameObject::GetColliderCenter() const
{
    Point2f center;
    center.x = m_Collider.left + m_Collider.width / 2;
    center.y = m_Collider.bottom + m_Collider.height / 2;
    return center;
}

void GameObject::InitCollider()
{
    m_Collider.width = m_pSprite->GetColliderWidth();
    m_Collider.height = m_pSprite->GetColliderHeight();
    const float horizontalOffset{(m_Shape.width - m_pSprite->GetColliderWidth()) / 2};
    const float verticalOffset{(m_Shape.height - m_pSprite->GetColliderHeight()) / 2};
    const int dir{m_Flipped ? -1 : 1};
    m_Collider.left = m_Shape.left + horizontalOffset + m_pSprite->GetColliderHorizontalOffset() * dir;
    m_Collider.bottom = m_Shape.bottom + verticalOffset + m_pSprite->GetColliderVerticalOffset() * dir;
    m_OriginalCollider = m_Collider;
}

void GameObject::UpdateCollider()
{
    if (m_pSprite)
    {
        const float horizontalOffset{(m_Shape.width - m_pSprite->GetColliderWidth()) / 2};
        const float verticalOffset{(m_Shape.height - m_pSprite->GetColliderHeight()) / 2};
        const int dir{m_Flipped ? -1 : 1};
        m_Collider.left = m_Shape.left + horizontalOffset + m_pSprite->GetColliderHorizontalOffset() * dir;
        m_Collider.bottom = m_Shape.bottom + verticalOffset + m_pSprite->GetColliderVerticalOffset() * dir;
    }
    else
    {
        m_Collider = m_Shape;
    }
}

std::vector<Point2f> GameObject::GetColliderVertices() const
{
    std::vector<Point2f> vertices{
        Point2f{m_Collider.left, m_Collider.bottom},
        Point2f{m_Collider.left + m_Collider.width, m_Collider.bottom},
        Point2f{m_Collider.left + m_Collider.width, m_Collider.bottom + m_Collider.height},
        Point2f{m_Collider.left, m_Collider.bottom + m_Collider.height}
    };
    return vertices;
}

void GameObject::SetColliderHeight(float height)
{
    m_Collider.height = height;
}

void GameObject::ResetCollider()
{
    m_Collider = m_OriginalCollider;
}

void GameObject::Reset()
{
    m_Active = true;
    m_Visible = true;
    m_Awake = false;
    m_AwakeFired = false;
}

Point2f GameObject::GetContactPoint(const GameObject* other) const
{
    Point2f contactPoint;
    contactPoint.y = other->GetColliderCenter().y;
    if (other->IsFlipped())
    {
        contactPoint.x = other->GetCollider().left;
    }
    else
    {
        contactPoint.x = other->GetCollider().left + other->GetCollider().width;
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
    const float verticalOffset{(m_Shape.height - m_pSprite->GetColliderHeight()) / 2};
    m_Shape.bottom = bottom - verticalOffset;
}

void GameObject::SetLeft(float left)
{
    const float horizontalOffset{(m_Shape.width - m_pSprite->GetColliderWidth()) / 2};
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
