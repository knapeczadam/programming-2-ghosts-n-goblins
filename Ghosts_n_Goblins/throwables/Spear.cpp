#include "pch.h"
#include "Spear.h"

Spear::Spear(const Point2f& pos, GameController* pGameController)
    : GameObject(Game::Label::T_SPEAR, pos, true, pGameController)
{
}
