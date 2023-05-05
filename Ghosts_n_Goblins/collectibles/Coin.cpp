#include "pch.h"
#include "Coin.h"

Coin::Coin(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_COIN, pos, true, pGameController}
{
    m_Score = 200;
}
