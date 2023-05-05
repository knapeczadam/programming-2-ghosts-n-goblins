#include "pch.h"
#include "Necklace.h"

Necklace::Necklace(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject{Game::Label::O_NECKLACE, pos, true, pSpriteFactory}
{
    m_Score = 200;
}
