#pragma once
#include "ICollider.h"

class LadderCollider final : public ICollider
{
public:
    explicit LadderCollider(const Rectf& shape, GameController* pGameController);
    virtual ~LadderCollider() override = default;
    LadderCollider(const LadderCollider& other) = delete;
    LadderCollider(LadderCollider&& other) noexcept = delete;
    LadderCollider& operator=(const LadderCollider& other) = delete;

    virtual void HandleCollision(GameObject* other) override;
};
