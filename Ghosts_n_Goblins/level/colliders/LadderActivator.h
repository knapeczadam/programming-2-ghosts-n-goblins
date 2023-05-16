#pragma once
#include "ICollider.h"

class LadderActivator final : public ICollider
{
public:
    explicit LadderActivator(const Rectf& shape, GameController* pGameController);
    virtual ~LadderActivator() override = default;
    LadderActivator(const LadderActivator& other) = delete;
    LadderActivator(LadderActivator&& other) noexcept = delete;
    LadderActivator& operator=(const LadderActivator& other) = delete;
    LadderActivator& operator=(LadderActivator&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
};
