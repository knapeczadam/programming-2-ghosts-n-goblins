#include "pch.h"
#include "Pot.h"

Pot::Pot(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_POT, pos, true, pGameController}
{
}
