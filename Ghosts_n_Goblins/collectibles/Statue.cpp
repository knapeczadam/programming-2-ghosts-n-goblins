#include "pch.h"
#include "Statue.h"

Statue::Statue(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_STATUE, pSprite, pos}
{
    m_Score = 200;
}
