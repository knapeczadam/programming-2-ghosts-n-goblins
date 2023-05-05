#include "pch.h"
#include "MoneyBag.h"

MoneyBag::MoneyBag(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_MONEY_BAG, pos, true, pGameController}
{
    m_Score = 500;
}
