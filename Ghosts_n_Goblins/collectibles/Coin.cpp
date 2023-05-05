#include "pch.h"
#include "Coin.h"

Coin::Coin(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject{Game::Label::O_COIN, pos, true, pSpriteFactory}
{
    m_Score = 200;
}
