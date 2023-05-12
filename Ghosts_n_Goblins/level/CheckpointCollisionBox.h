#pragma once
#include "CollisionBox.h"

class CheckpointCollisionBox final : public CollisionBox
{
public:
    explicit CheckpointCollisionBox(const Rectf& shape, GameController* pGameController);
    virtual ~CheckpointCollisionBox() override = default;
    CheckpointCollisionBox(const CheckpointCollisionBox& other) = delete;
    CheckpointCollisionBox(CheckpointCollisionBox&& other) noexcept = delete;
    CheckpointCollisionBox& operator=(const CheckpointCollisionBox& other) = delete;
    CheckpointCollisionBox& operator=(CheckpointCollisionBox&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
private:
    const Point2f m_Pos;
};
