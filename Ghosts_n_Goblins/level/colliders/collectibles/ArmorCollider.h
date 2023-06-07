#pragma once
#include "level/colliders/ICollider.h"

class ArmorCollider final : public ICollider
{
public:
    explicit ArmorCollider(const Rectf& shape, GameController* pGameController);
    virtual ~ArmorCollider() override = default;
    ArmorCollider(const ArmorCollider& other) = delete;
    ArmorCollider(ArmorCollider&& other) noexcept = delete;
    ArmorCollider& operator=(const ArmorCollider& other) = delete;
    ArmorCollider& operator=(ArmorCollider&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;

private:
    const Point2f m_PotPos;
};
