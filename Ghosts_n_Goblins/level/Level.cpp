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

void Level::HandleCollision(GameObject* other)
{
    m_pGameController->m_pLevelManager->GetPlatform()->HandleCollision(other);

    const float epsilon{0.0f};
    utils::HitInfo hit;
    
    // DOWN
    const Point2f objectCenter{other->GetColliderCenter()};
    Point2f down;
    down.x = objectCenter.x;
    down.y = other->GetCollider().bottom - epsilon;

    // UP
    Point2f up;
    up.x = objectCenter.x;
    up.y = other->GetCollider().bottom + other->GetCollider().height * 2 + epsilon;

    // RIGHT
    Point2f right;
    right.x = other->GetCollider().left + other->GetCollider().width + epsilon;
    right.y = objectCenter.y;

    // LEFT
    Point2f left;
    left.x = other->GetCollider().left - epsilon;
    left.y = objectCenter.y;
    std::ranges::for_each(m_Vertices, [&](const std::vector<Point2f>& vertices)
    {
        // TODO: fix this
        // if (utils::Raycast(vertices, Point2f{up.x, down.y + 5.0f}, up, hit) and pPlayer->GetState() == Player::State::HIT) return;
        if (utils::Raycast(vertices, objectCenter, down, hit))
        {
            other->SetBottom(hit.intersectPoint.y);
            Player* pPlayer{dynamic_cast<Player*>(other)};
            if (pPlayer)
            {
                Vector2f playerVelocity{pPlayer->GetVelocity()};
                playerVelocity.y = 0.f;
                pPlayer->SetVelocity(playerVelocity);
            }
        }
        if (utils::Raycast(vertices, objectCenter, right, hit))
        {
            other->SetLeft(hit.intersectPoint.x - other->GetCollider().width);
            Player* pPlayer{dynamic_cast<Player*>(other)};
            if (pPlayer)
            {
                Vector2f playerVelocity{pPlayer->GetVelocity()};
                playerVelocity.x = 0.f;
                pPlayer->SetVelocity(playerVelocity);
            }
        }
        if (utils::Raycast(vertices, objectCenter, left, hit))
        {
            other->SetLeft(hit.intersectPoint.x);
            Player* pPlayer{dynamic_cast<Player*>(other)};
            if (pPlayer)
            {
                Vector2f playerVelocity{pPlayer->GetVelocity()};
                playerVelocity.x = 0.f;
                pPlayer->SetVelocity(playerVelocity);
            }
        }
    });
}

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
