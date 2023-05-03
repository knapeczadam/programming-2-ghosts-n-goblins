#include "pch.h"
#include "Necklace.h"

Necklace::Necklace(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_NECKLACE, pSprite, pos}
{
    m_Score = 200;
}
