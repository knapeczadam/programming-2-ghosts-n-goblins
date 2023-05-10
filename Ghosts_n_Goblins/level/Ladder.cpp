#include "pch.h"
#include "Ladder.h"

#include "characters/Player.h"

Ladder::Ladder(const Rectf& shape)
    : GameObject{Game::Label::L_LADDER, shape}
{
    m_HasSprite = false;
}

void Ladder::HandleCollision(GameObject* other)
{
    const float epsilon{1.0f};

    // LEFT
    Point2f left1, left2;
    left1.x = other->GetCollisionBox().left;
    left1.y = other->GetCollisionBox().bottom;

    left2.x = left1.x;
    left2.y = left1.y - epsilon;

    // RIGHT
    Point2f right1, right2;
    right1.x = other->GetCollisionBox().left + other->GetCollisionBox().width;
    right1.y = other->GetCollisionBox().bottom;

    right2.x = right1.x;
    right2.y = right1.y - epsilon;

    utils::HitInfo hitLeft, hitRight;

    if (utils::Raycast(GetCollisionBoxVertices(), left1, left2, hitLeft)
        or utils::Raycast(GetCollisionBoxVertices(), right1, right2, hitRight))
    {
    }
}
