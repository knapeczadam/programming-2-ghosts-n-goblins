#include "pch.h"
#include "Shield.h"

Shield::Shield(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_SHIELD, pSprite, pos}
{
}
