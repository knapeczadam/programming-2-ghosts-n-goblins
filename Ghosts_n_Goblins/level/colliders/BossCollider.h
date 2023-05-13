#pragma once
#include "ICollider.h"

class BossCollider final : public ICollider
{
public:
    explicit BossCollider(const Rectf& shape, GameController* pGameController);
    virtual ~BossCollider() override = default;
    BossCollider(const BossCollider& other) = delete;
    BossCollider(BossCollider&& other) noexcept = delete;
    BossCollider& operator=(const BossCollider& other) = delete;
    BossCollider& operator=(BossCollider&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
};
