#include "pch.h"
#include "Fireball.h"

Fireball::Fireball(Game::Label label, const Point2f& pos, GameController* pGameController)
    : GameObject{label, pos, true, pGameController}
{
}
