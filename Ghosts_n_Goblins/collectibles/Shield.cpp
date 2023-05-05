#include "pch.h"
#include "Shield.h"

Shield::Shield(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_SHIELD, pos, true, pGameController}
{
}
