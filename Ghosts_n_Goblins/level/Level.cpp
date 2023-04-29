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
      , m_Boundaries{0, 0, m_pSprite->GetWidth(), m_pSprite->GetHeight()}
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
        Point2f p1{m_pPlayer->GetCenter()};
        Point2f p2;
        p2.x = p1.x;
        p2.y = m_pPlayer->GetShape().bottom - epsilon;
        utils::SetColor(Color4f{1, 0, 0, 1});
        utils::DrawLine(p1, p2);
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
void Level::HandleCollision(GameObject* pGameObject)
{
    m_pPlatform->HandleCollision(pGameObject);
    
    m_pPlayer = pGameObject;
    const float epsilon{0.0f};
    utils::HitInfo hit;
    Point2f p1{pGameObject->GetCenter()};
    Point2f p2;
    p2.x = p1.x;
    p2.y = pGameObject->GetShape().bottom - epsilon;
    std::ranges::for_each(m_Vertices, [&](const std::vector<Point2f>& vertices)
    {
        if (utils::Raycast(vertices, p1, p2, hit))
        {
            pGameObject->SetBottom(hit.intersectPoint.y);
            Player* pPlayer{static_cast<Player*>(pGameObject)};
            Vector2f playerVelocity{pPlayer->GetVelocity()};
            playerVelocity.y = 0.f;
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
    Point2f p1{pGameObject->GetCenter()};
    Point2f p2;
    p2.x = p1.x;
    p2.y = pGameObject->GetShape().bottom - epsilon;
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

bool Level::HasReachedEnd(const Rectf& actorShape) const
{
    const Point2f actorCenter{actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height / 2};
    const Point2f endSignCenter{};
    const float distance{utils::GetDistance(actorCenter, endSignCenter)};
    const float epsilon{50.0f};
    return distance <= epsilon;
}

Platform* Level::GetPlatform() const
{
    return m_pPlatform;
}
