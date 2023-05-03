#include "pch.h"
#include "Star.h"

Star::Star(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_STAR, pSprite, pos}
{
    m_Score = 10000;
}
