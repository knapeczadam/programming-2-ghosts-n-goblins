#include "pch.h"
#include "Eyeball.h"

Eyeball::Eyeball(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject(Game::Label::W_EYEBALL, pos, true, pSpriteFactory)
{
}
