#include "pch.h"
#include "ICollider.h"

ICollider::ICollider(Game::Label label, const Rectf& shape, GameController* pGameController)
    : GameObject{label, shape, true, false, Color4f{0.0f, 1.0f, 1.0f, 1.0f}, pGameController}
{
}
