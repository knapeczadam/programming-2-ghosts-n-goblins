#include "pch.h"
#include "Coin.h"

Coin::Coin(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_COIN, pSprite, pos}
{
    m_Score = 200;
}
