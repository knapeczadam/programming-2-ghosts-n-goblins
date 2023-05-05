#include "pch.h"
#include "Spell.h"

Spell::Spell(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject(Game::Label::W_SPELL, pos, true, pSpriteFactory)
{
}
