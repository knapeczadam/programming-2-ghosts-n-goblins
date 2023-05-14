#pragma once
#include "ICollider.h"

class DoorCollider final : public ICollider
{
public:
    explicit DoorCollider(const Rectf& shape, GameController* pGameController);
    virtual ~DoorCollider() override = default;
    DoorCollider(const DoorCollider& other) = delete;
    DoorCollider(DoorCollider&& other) noexcept = delete;
    DoorCollider& operator=(const DoorCollider& other) = delete;
    DoorCollider& operator=(DoorCollider&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
};
