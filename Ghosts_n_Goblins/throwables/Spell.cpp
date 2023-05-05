#include "pch.h"
#include "Spell.h"

Spell::Spell(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject(Game::Label::T_SPELL, pos, true, pSpriteFactory)
{
}
