#include "pch.h"
#include "Pot.h"

Pot::Pot(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject{Game::Label::O_POT, pos, true, pSpriteFactory}
{
}
