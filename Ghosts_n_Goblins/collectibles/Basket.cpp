#include "pch.h"
#include "Basket.h"

Basket::Basket(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_BASKET, pSprite, pos}
{
    m_Score = 500;
}
