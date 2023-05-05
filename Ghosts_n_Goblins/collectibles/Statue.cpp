#include "pch.h"
#include "Statue.h"

Statue::Statue(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_STATUE, pos, true, pGameController}
{
    m_Score = 200;
}
