#include "pch.h"
#include "Fireball.h"

Fireball::Fireball(Game::Label label, const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject(label, pos, true, pSpriteFactory)
{
}
