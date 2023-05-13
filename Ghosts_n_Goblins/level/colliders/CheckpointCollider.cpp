#include "pch.h"
#include "CheckpointCollider.h"

CheckpointCollider::CheckpointCollider(const Rectf& shape, GameController* pGameController)
    : ICollider{Game::Label::L_CHECKPOINT, shape, pGameController}
    , m_Pos{shape.left, shape.bottom}
{
}

void CheckpointCollider::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    m_Active = false;
}
