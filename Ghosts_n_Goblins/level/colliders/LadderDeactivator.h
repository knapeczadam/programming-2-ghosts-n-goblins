#pragma once
#include "ICollider.h"

class LadderDeactivator final : public ICollider
{
public:
    explicit LadderDeactivator(const Rectf& shape, GameController* pGameController);
    virtual ~LadderDeactivator() override = default;
    LadderDeactivator(const LadderDeactivator& other) = delete;
    LadderDeactivator(LadderDeactivator&& other) noexcept = delete;
    LadderDeactivator& operator=(const LadderDeactivator& other) = delete;
    LadderDeactivator& operator=(LadderDeactivator&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
};
