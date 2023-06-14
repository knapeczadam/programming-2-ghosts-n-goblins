#pragma once
#include "level/colliders/ICollider.h"

class YashichiCollider final : public ICollider
{
public:
    explicit YashichiCollider(const Rectf& shape, GameController* pGameController);
    virtual ~YashichiCollider() override = default;
    YashichiCollider(const YashichiCollider& other) = delete;
    YashichiCollider(YashichiCollider&& other) noexcept = delete;
    YashichiCollider& operator=(const YashichiCollider& other) = delete;
    YashichiCollider& operator=(YashichiCollider&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;

private:
    const Point2f m_PotPos;
};
