#include "pch.h"
#include "Key.h"

Key::Key(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject{Game::Label::O_KEY, pos, true, pSpriteFactory}
{
    m_Score = 1000;
}
