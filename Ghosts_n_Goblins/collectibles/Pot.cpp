#include "pch.h"
#include "Pot.h"

Pot::Pot(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_POT, pSprite, pos}
{
}
