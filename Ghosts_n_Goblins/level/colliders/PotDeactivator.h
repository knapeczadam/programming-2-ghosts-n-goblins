#pragma once
#include "ICollider.h"

class PotDeactivator final : public ICollider
{
public:
    explicit PotDeactivator(const Rectf& boundaries, GameController* pGameController);
    virtual ~PotDeactivator() override = default;
    PotDeactivator(const PotDeactivator& other) = delete;
    PotDeactivator(PotDeactivator&& other) noexcept = delete;
    PotDeactivator& operator=(const PotDeactivator& other) = delete;
    PotDeactivator& operator=(PotDeactivator&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
};
