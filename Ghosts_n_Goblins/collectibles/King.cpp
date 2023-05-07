#include "pch.h"
#include "King.h"

King::King(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_KING, pos, true, pGameController}
{
    m_Score = 10000;
}
