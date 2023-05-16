#pragma once
#include "ICollider.h"
#include "game/GameObject.h"

class KillZone final : public ICollider
{
public:
    explicit KillZone(const Rectf& shape, GameController* pGameController);
    virtual ~KillZone() override = default;
    KillZone(const KillZone& other) = delete;
    KillZone(KillZone&& other) noexcept = delete;
    KillZone& operator=(const KillZone& other) = delete;
    KillZone& operator=(KillZone&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
};
