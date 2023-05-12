#include "pch.h"
#include "CheckpointCollisionBox.h"

CheckpointCollisionBox::CheckpointCollisionBox(const Rectf& shape, GameController* pGameController)
    : CollisionBox{Game::Label::L_CHECKPOINT, shape, pGameController}
    , m_Pos{shape.left, shape.bottom}
{
}

void CheckpointCollisionBox::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    m_Active = false;
}
