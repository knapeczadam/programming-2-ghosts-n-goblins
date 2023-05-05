#include "pch.h"
#include "Necklace.h"

Necklace::Necklace(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_NECKLACE, pos, true, pGameController}
{
    m_Score = 200;
}
