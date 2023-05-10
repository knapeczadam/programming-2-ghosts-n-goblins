#pragma once
#include "CollisionBox.h"

class YashichiCollisionBox final : public CollisionBox
{
public:
    explicit YashichiCollisionBox(const Rectf& shape, GameController* pGameController);
    virtual ~YashichiCollisionBox() override = default;
    YashichiCollisionBox(const YashichiCollisionBox& other) = delete;
    YashichiCollisionBox(YashichiCollisionBox&& other) noexcept = delete;
    YashichiCollisionBox& operator=(const YashichiCollisionBox& other) = delete;


    virtual void HandleCollision(GameObject* other) override;
private:
    const Point2f m_PotPos;
};
