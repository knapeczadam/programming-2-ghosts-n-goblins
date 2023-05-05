#include "pch.h"
#include "Spell.h"

Spell::Spell(Sprite* pSprite, const Point2f& pos)
    : GameObject(Game::Label::W_SPELL, pSprite, pos)
{
}
