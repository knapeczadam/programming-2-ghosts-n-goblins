// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Level.h"

#include "Platform.h"
#include "SVGParser.h"
#include "utils.h"
#include "characters/Player.h"
#include "engine/Sprite.h"
#include "game/GameController.h"
#include "game/LevelManager.h"
#include "game/Macros.h"

Level::Level(GameController* pGameController)
    : GameObject{Game::Label::L_LEVEL, pGameController}
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
#if DEBUG_LEVEL
    utils::SetColor(Color4f{1, 0, 1, 1});
    for (const std::vector<Point2f>& collider : m_Vertices)
    {
        utils::DrawPolygon(collider);
    }
#endif
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
    m_pGameController->m_pLevelManager->GetPlatform()->HandleCollision(other);

    const float epsilon{0.0f};
    utils::HitInfo hit;

    // DOWN
    const Point2f playerCenter{other->GetColliderCenter()};
    Point2f down;
    down.x = playerCenter.x;
    down.y = other->GetCollider().bottom - epsilon;

    // RIGHT
    Point2f right;
    right.x = other->GetCollider().left + other->GetCollider().width + epsilon;
    right.y = playerCenter.y;

    // LEFT
    Point2f left;
    left.x = other->GetCollider().left - epsilon;
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
            other->SetLeft(hit.intersectPoint.x - other->GetCollider().width);
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
    const float epsilon{0.0f};
    utils::HitInfo hit;
    const Point2f p1{pGameObject->GetColliderCenter()};
    Point2f p2;
    p2.x = p1.x;
    p2.y = pGameObject->GetCollider().bottom - epsilon;
    bool isHit{};
    std::ranges::for_each(m_Vertices, [&](const std::vector<Point2f>& vertices)
    {
        if (utils::Raycast(vertices, p1, p2, hit))
        {
            isHit = true;
        }
    });
    return isHit or m_pGameController->m_pLevelManager->GetPlatform()->IsOnGround(pGameObject);
}

void Level::SetVertices()
{
    SVGParser::GetVerticesFromSvgFile("images/level/level.svg", m_Vertices);
}

Rectf Level::GetBoundaries() const
{
    return m_Boundaries;
}

// TODO: egy bizonyos idő után már nem lehet visszamenni
void Level::SetBoundaries(const Rectf& boundaries)
{
    m_Boundaries = boundaries;
}

bool Level::HasReachedEnd(const Rectf& collider) const
{
    const Point2f playerCenter{
        collider.left + collider.width / 2.0f, collider.bottom + collider.height / 2.0f
    };
    const Point2f endSignCenter{};
    const float distance{utils::GetDistance(playerCenter, endSignCenter)};
    const float epsilon{50.0f};
    return distance <= epsilon;
}
