#include "pch.h"
#include "MoneyBag.h"

MoneyBag::MoneyBag(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject{Game::Label::O_MONEY_BAG, pos, true, pSpriteFactory}
{
    m_Score = 500;
}
