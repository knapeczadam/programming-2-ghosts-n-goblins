#include "pch.h"
#include "Magician.h"

Magician::Magician(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::E_MAGICIAN, pSprite, pos}
{
}
