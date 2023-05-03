#include "pch.h"
#include "Ladder.h"

Ladder::Ladder(const Rectf& shape)
    : GameObject(Game::Label::L_LADDER, shape, true)
{
}
