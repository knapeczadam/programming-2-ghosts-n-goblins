#include "pch.h"
#include "Doll.h"

Doll::Doll(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_DOLL, pos, true, pGameController}
{
    m_Score = 200;
}
