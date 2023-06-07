#include "pch.h"
#include "Armor.h"

Armor::Armor(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_ARMOR, pos, true, pGameController}
{
}
