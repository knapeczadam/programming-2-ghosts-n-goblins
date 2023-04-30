// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Platform.h"
#include "Texture.h"
#include "utils.h"
#include "engine/Sprite.h"
#include "characters/Player.h"

#include <iostream>

Platform::Platform(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::PLATFORM, pSprite, pos}
      , m_AccuSec{0.0f}
      , m_OriginalPos{pos}
      , m_Speed{2.0f}
      , m_MaxAmplitude{238.0f}
      , m_ShortAmplitude{100.0f}
      , m_CurrAmplitude{m_MaxAmplitude}
      , m_IsShortened{false}
      , m_Flip{true}
{
    InitVertices();
}

void Platform::Draw() const
{
    GameObject::Draw();
}

void Platform::Move()
{
    const float normalizedWave{(std::sin(m_AccuSec * m_Speed) + 1) / 2};

    const float epsilon{0.001f};
    const bool leftReached{std::abs(m_Shape.left - m_OriginalPos.x) < epsilon};
    const bool rightReached{std::abs(m_Shape.left - (m_OriginalPos.x + m_MaxAmplitude)) < epsilon};
    const bool midReached{std::abs(m_Shape.left - (m_OriginalPos.x + m_MaxAmplitude -  m_ShortAmplitude)) < epsilon};
    if (m_IsShortened)
    {
        m_Shape.left = m_OriginalPos.x + (m_MaxAmplitude - m_ShortAmplitude) + normalizedWave * m_CurrAmplitude;
        if (m_Flip and rightReached)
        {
            m_Flip = false;
            m_IsShortened = false;
            m_CurrAmplitude = m_MaxAmplitude;
        }
        else if (midReached)
        {
            m_Flip = true;
        }
    }
    else
    {
        m_Shape.left = m_OriginalPos.x + normalizedWave * m_CurrAmplitude;
        if (m_Flip and rightReached)
        {
            m_IsShortened = true;
            m_CurrAmplitude = m_ShortAmplitude;
            m_Flip = false;
        }
        else if (leftReached)
        {
            m_Flip = true;
        }
    }
}

void Platform::Update(float elapsedSec)
{
    m_AccuSec += elapsedSec;
    Move();
    UpdateVertices();
    m_pSprite->SetPosition(GetPosition<Point2f>());
    UpdateCollisionBox();
}

/*
Handles collision with this platform only when the actor is moving downwards.
 */
void Platform::HandleCollision(GameObject* other)
{
    const Point2f p1{other->GetCollisionBoxCenter()};
    const Point2f p2{p1.x, other->GetCollisionBox().bottom};
    utils::HitInfo hit;
    const bool isHit{utils::Raycast(m_Vertices, p1, p2, hit)};
    // Swamp effect
    // if (isHit)
    // {
    //    if (actorVelocity.y < 0.0f and hit.intersectPoint.y < actorShape.bottom)
    //    {
    //        actorShape.bottom = hit.intersectPoint.y;
    //        actorVelocity.y = 0.0f;
    //    } 
    // }
    Player* pPlayer{static_cast<Player*>(other)};
    if (isHit and pPlayer->GetVelocity().y < 0)
    {
        other->SetBottom(hit.intersectPoint.y);
        Vector2f playerVelocity{pPlayer->GetVelocity()};
        playerVelocity.y = 0.f;
        pPlayer->SetVelocity(playerVelocity);
    }
}

/*
Returns true when the given actor is not going upwards and is on the
platform’s top.
 */
bool Platform::IsOnGround(GameObject* pGameObject) const
{
    const float epsilon{1.0f};
    const Point2f p1{pGameObject->GetCollisionBoxCenter()};
    const Point2f p2{p1.x, pGameObject->GetCollisionBox().bottom - epsilon};
    Player* pPlayer{static_cast<Player*>(pGameObject)};
    if (pPlayer->GetVelocity().y <= 0.0f && utils::IsOverlapping(p1, p2, m_Shape))
    {
        pPlayer->SetIsOnPlatform(true);

        return true;
    }
    pPlayer->SetIsOnPlatform(false);
    return false;
}

void Platform::InitVertices()
{
    m_Vertices.insert(m_Vertices.end(), {
                          Point2f{m_Shape.left, m_Shape.bottom},
                          Point2f{m_Shape.left + m_Shape.width, m_Shape.bottom},
                          Point2f{m_Shape.left + m_Shape.width, m_Shape.bottom + m_Shape.height},
                          Point2f{m_Shape.left, m_Shape.bottom + m_Shape.height},
                          Point2f{m_Shape.left, m_Shape.bottom}
                      });
}

void Platform::UpdateVertices()
{
    m_Vertices[0].x = m_Shape.left;
    m_Vertices[0].y = m_Shape.bottom;
    m_Vertices[1].x = m_Shape.left + m_Shape.width;
    m_Vertices[1].y = m_Shape.bottom;
    m_Vertices[2].x = m_Shape.left + m_Shape.width;
    m_Vertices[2].y = m_Shape.bottom + m_Shape.height;
    m_Vertices[3].x = m_Shape.left;
    m_Vertices[3].y = m_Shape.bottom + m_Shape.height;
    m_Vertices[4].x = m_Shape.left;
    m_Vertices[4].y = m_Shape.bottom;
}
