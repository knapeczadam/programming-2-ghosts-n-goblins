#include "pch.h"
#include "Bust.h"

Bust::Bust(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_BUST, pSprite, pos}
{
}
