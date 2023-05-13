#pragma once
#include "ICollider.h"

class CheckpointCollider final : public ICollider
{
public:
    explicit CheckpointCollider(const Rectf& shape, GameController* pGameController);
    virtual ~CheckpointCollider() override = default;
    CheckpointCollider(const CheckpointCollider& other) = delete;
    CheckpointCollider(CheckpointCollider&& other) noexcept = delete;
    CheckpointCollider& operator=(const CheckpointCollider& other) = delete;
    CheckpointCollider& operator=(CheckpointCollider&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
private:
    const Point2f m_Pos;
};
