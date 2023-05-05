#include "pch.h"
#include "Statue.h"

Statue::Statue(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject{Game::Label::O_STATUE, pos, true, pSpriteFactory}
{
    m_Score = 200;
}
