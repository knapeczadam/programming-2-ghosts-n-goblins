#pragma once
#include "ICollider.h"

class EndCollider final : public ICollider
{
public:
    explicit EndCollider(const Rectf& shape, GameController* pGameController);
    virtual ~EndCollider() override = default;
    EndCollider(const EndCollider& other) = delete;
    EndCollider(EndCollider&& other) noexcept = delete;
    EndCollider& operator=(const EndCollider& other) = delete;
    EndCollider& operator=(EndCollider&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
};
