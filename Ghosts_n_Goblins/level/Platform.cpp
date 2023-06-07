// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Platform.h"

#include "Texture.h"
#include "utils.h"
#include "characters/Player.h"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"

Platform::Platform(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::L_PLATFORM, pos, true, pGameController}
    , m_AccuSec{0.0f}
    , m_OriginalPos{pos}
    , m_Speed{2.0f}
    , m_MaxAmplitude{221.0f}
    , m_ShortAmplitude{100.0f}
    , m_CurrAmplitude{m_MaxAmplitude}
    , m_Shortened{false}
    , m_Flip{true}
{
}

void Platform::Move()
{
    const float normalizedWave{(std::sin(m_AccuSec * m_Speed) + 1) / 2};

    const float epsilon{0.001f};
    const bool leftReached{std::abs(m_Shape.left - m_OriginalPos.x) < epsilon};
    const bool rightReached{std::abs(m_Shape.left - (m_OriginalPos.x + m_MaxAmplitude)) < epsilon};
    const bool midReached{std::abs(m_Shape.left - (m_OriginalPos.x + m_MaxAmplitude - m_ShortAmplitude)) < epsilon};
    if (m_Shortened)
    {
        m_Shape.left = m_OriginalPos.x + (m_MaxAmplitude - m_ShortAmplitude) + normalizedWave * m_CurrAmplitude;
        if (m_Flip and rightReached)
        {
            m_Flip = false;
            m_Shortened = false;
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
            m_Shortened = true;
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
    m_pSprite->SetPosition(GetPosition<Point2f>());
    UpdateCollider();
}

/*
Handles collision with this platform only when the actor is moving downwards.
 */
void Platform::HandleCollision(GameObject* other)
{
    const Point2f p1{other->GetColliderCenter()};
    const Point2f p2{p1.x, other->GetCollider().bottom};
    utils::HitInfo hit;
    const bool isHit{utils::Raycast(GetColliderVertices(), p1, p2, hit)};
    if (isHit)
    {
        Player* pPlayer{static_cast<Player*>(other)};
        other->SetBottom(hit.intersectPoint.y);
        Vector2f playerVelocity{pPlayer->GetVelocity()};
        playerVelocity.y = 0.f;
        pPlayer->SetVelocity(playerVelocity);
    }
    // Swamp effect
    // if (isHit)
    // {
    //    if (actorVelocity.y < 0.0f and hit.intersectPoint.y < actorShape.bottom)
    //    {
    //        actorShape.bottom = hit.intersectPoint.y;
    //        actorVelocity.y = 0.0f;
    //    } 
    // }
    return; // TODO: review this
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
    const float epsilon{0.0f};
    utils::HitInfo hit;
    const Point2f p1{pGameObject->GetColliderCenter()};
    const Point2f p2{p1.x, pGameObject->GetCollider().bottom - epsilon};
    Player* pPlayer{static_cast<Player*>(pGameObject)};
    if (utils::Raycast(GetColliderVertices(), p1, p2, hit))
    {
        pPlayer->SetIsOnPlatform(true);
        return true;
    }
    pPlayer->SetIsOnPlatform(false);
    return false;
    if (pPlayer->GetVelocity().y <= 0.0f && utils::IsOverlapping(p1, p2, m_Shape))
    {
        pPlayer->SetIsOnPlatform(true);

        return true;
    }
    pPlayer->SetIsOnPlatform(false);
    return false;
}
