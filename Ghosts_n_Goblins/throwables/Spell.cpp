#include "pch.h"
#include "Spell.h"

Spell::Spell(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::T_SPELL, pos, true, pGameController}
{
}
