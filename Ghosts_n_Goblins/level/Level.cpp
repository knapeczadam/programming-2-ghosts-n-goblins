// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Level.h"
#include "game/Macros.h"

#include "SVGParser.h"
#include "Texture.h"
#include "Platform.h"
#include "utils.h"
#include "ranges"
#include "algorithm"
#include "characters/Player.h"
#include "engine/Sprite.h"

Level::Level(Sprite* pSprite, Platform* pPlatform)
    : GameObject{Game::Label::LEVEL, pSprite}
      , m_pPlatform{pPlatform}
      , m_Vertices{}
      , topMargin{32.0f}
      , m_Boundaries{0, 0, m_pSprite->GetWidth(), m_pSprite->GetHeight() + topMargin}
      , m_pPlayer{}
{
    SetVertices();
}

/*
Draws the background texture
 */
void Level::Draw() const
{
    m_pSprite->Draw();
    m_pPlatform->Draw();
#if DEBUG_LEVEL
    utils::SetColor(Color4f{1, 0, 1, 1});
    for (const std::vector<Point2f>& collisionShapes : m_Vertices)
    {
        utils::DrawPolygon(collisionShapes);
    }
#endif
#if DEBUG_RAYCAST
    if (m_pPlayer)
    {
        const float epsilon{0.0f};
        Point2f playerCenter{m_pPlayer->GetCollisionBoxCenter()};
        // LEFT
        Point2f left;
        left.x = m_pPlayer->GetCollisionBox().left - epsilon;
        left.y = playerCenter.y;
        // RIGHT
        Point2f right;
        right.x = m_pPlayer->GetCollisionBox().left + m_pPlayer->GetCollisionBox().width + epsilon;
        right.y = playerCenter.y;
        // DOWN
        Point2f down;
        down.x = playerCenter.x;
        down.y = m_pPlayer->GetCollisionBox().bottom - epsilon;
        utils::SetColor(Color4f{0, 1, 0, 1});
        utils::DrawLine(playerCenter, left);
        utils::SetColor(Color4f{1, 0, 0, 1});
        utils::DrawLine(playerCenter, right);
        utils::SetColor(Color4f{1, 1, 0, 1});
        utils::DrawLine(playerCenter, down);
    }
#endif
}

void Level::Update(float elapsedSec)
{
    m_pPlatform->Update(elapsedSec);
}

/*
It handles the vertical collision of the given actor with the level using the
Raycast functionality.
It stops the actor when it penetrates the level:
- the bottom-position is changed to the y value of the intersection point
(actor should not penetrate the level) and
- the vertical part of the actor's velocity becomes 0.
Tip: use Raycast with a vertical ray (blue line) in the middle of the actor.
 */
void Level::HandleCollision(GameObject* other)
{
    m_pPlatform->HandleCollision(other);

    m_pPlayer = other;
    const float epsilon{0.0f};
    utils::HitInfo hit;

    // DOWN
    const Point2f playerCenter{other->GetCollisionBoxCenter()};
    Point2f down;
    down.x = playerCenter.x;
    down.y = other->GetCollisionBox().bottom - epsilon;

    // RIGHT
    Point2f right;
    right.x = other->GetCollisionBox().left + other->GetCollisionBox().width + epsilon;
    right.y = playerCenter.y;

    // LEFT
    Point2f left;
    left.x = other->GetCollisionBox().left - epsilon;
    left.y = playerCenter.y;
    std::ranges::for_each(m_Vertices, [&](const std::vector<Point2f>& vertices)
    {
        if (utils::Raycast(vertices, playerCenter, down, hit))
        {
            other->SetBottom(hit.intersectPoint.y);
            Player* pPlayer{static_cast<Player*>(other)};
            Vector2f playerVelocity{pPlayer->GetVelocity()};
            playerVelocity.y = 0.f;
            pPlayer->SetVelocity(playerVelocity);
        }
        if (utils::Raycast(vertices, playerCenter, right, hit))
        {
            other->SetLeft(hit.intersectPoint.x - other->GetCollisionBox().width);
            Player* pPlayer{static_cast<Player*>(other)};
            Vector2f playerVelocity{pPlayer->GetVelocity()};
            playerVelocity.x = 0.f;
            pPlayer->SetVelocity(playerVelocity);
        }
        if (utils::Raycast(vertices, playerCenter, left, hit))
        {
            other->SetLeft(hit.intersectPoint.x);
            Player* pPlayer{static_cast<Player*>(other)};
            Vector2f playerVelocity{pPlayer->GetVelocity()};
            playerVelocity.x = 0.f;
            pPlayer->SetVelocity(playerVelocity);
        }
    });
    // const bool isHit{utils::Raycast(m_Vertices[0], p1, p2, hit)};
    // if (isHit)
    // {
    //     actorShape.bottom = hit.intersectPoint.y;
    //     actorVelocity.y = 0.f;
    // }
}

/*
Returns true when the actor touches the level, otherwise false is returned.
Tip: use RayCast with a vertical ray in the middle of the actor and that is 1
pixel deeper than the bottom.
 */
bool Level::IsOnGround(GameObject* pGameObject) const
{
    const float epsilon{1.0f};
    utils::HitInfo hit;
    Point2f p1{pGameObject->GetCollisionBoxCenter()};
    Point2f p2;
    p2.x = p1.x;
    p2.y = pGameObject->GetCollisionBox().bottom - epsilon;
    bool isHit{};
    std::ranges::for_each(m_Vertices, [&](const std::vector<Point2f>& vertices)
    {
        if (utils::Raycast(vertices, p1, p2, hit))
        {
            isHit = true;
        }
    });
    return isHit or m_pPlatform->IsOnGround(pGameObject);
}

void Level::SetVertices()
{
    SVGParser::GetVerticesFromSvgFile("images/level/level.svg", m_Vertices);
}

Rectf Level::GetBoundaries() const
{
    return m_Boundaries;
}

bool Level::HasReachedEnd(const Rectf& collisionBox) const
{
    const Point2f playerCenter{
        collisionBox.left + collisionBox.width / 2.0f, collisionBox.bottom + collisionBox.height / 2.0f
    };
    const Point2f endSignCenter{};
    const float distance{utils::GetDistance(playerCenter, endSignCenter)};
    const float epsilon{50.0f};
    return distance <= epsilon;
}

Platform* Level::GetPlatform() const
{
    return m_pPlatform;
}
