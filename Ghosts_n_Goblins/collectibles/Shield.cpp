#include "pch.h"
#include "Shield.h"

Shield::Shield(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject{Game::Label::O_SHIELD, pos, true, pSpriteFactory}
{
}
