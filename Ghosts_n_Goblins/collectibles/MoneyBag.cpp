#include "pch.h"
#include "MoneyBag.h"

MoneyBag::MoneyBag(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_MONEY_BAG, pSprite, pos}
{
    m_Score = 500;
}
