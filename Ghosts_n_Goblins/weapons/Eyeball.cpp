#include "pch.h"
#include "Eyeball.h"

Eyeball::Eyeball(Sprite* pSprite, const Point2f& pos)
    : GameObject(Game::Label::W_EYEBALL, pSprite, pos)
{
}
