#pragma once
#include "CollisionBox.h"
#include "game/GameController.h"

class ArmorCollisionBox final: public CollisionBox
{
public:
    explicit ArmorCollisionBox(const Rectf& shape, GameController* pGameController);
    virtual ~ArmorCollisionBox() override = default;
    ArmorCollisionBox(const ArmorCollisionBox& other) = delete;
    ArmorCollisionBox(ArmorCollisionBox&& other) noexcept = delete;
    ArmorCollisionBox& operator=(const ArmorCollisionBox& other) = delete;
    ArmorCollisionBox& operator=(ArmorCollisionBox&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
private:
    const Point2f m_PotPos;
};
