#include "pch.h"
#include "CollisionBox.h"

CollisionBox::CollisionBox(Game::Label label, const Rectf& shape, const Color4f& color)
    : GameObject{label, shape, true, false, color}
{
}
