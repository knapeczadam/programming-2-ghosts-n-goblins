#pragma once
#include "ICollider.h"

class BonusCollider final : public ICollider
{
public:
    BonusCollider(const Rectf& shape, GameController* pGameController);
    virtual ~BonusCollider() override = default;
    BonusCollider(const BonusCollider& other) = delete;
    BonusCollider(BonusCollider&& other) noexcept = delete;
    BonusCollider& operator=(const BonusCollider& other) = delete;
    BonusCollider& operator=(BonusCollider&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;

private:
    const int m_Bonus;
};
