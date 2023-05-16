#pragma once
#include "ICollider.h"
#include "game/GameObject.h"

class TombstoneCollider final : public ICollider
{
public:
    explicit TombstoneCollider(const Rectf& shape, GameController* pGameController);
    virtual ~TombstoneCollider() override = default;
    TombstoneCollider(const TombstoneCollider& other) = delete;
    TombstoneCollider(TombstoneCollider&& other) noexcept = delete;
    TombstoneCollider& operator=(const TombstoneCollider& other) = delete;
    TombstoneCollider& operator=(TombstoneCollider&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
private:
    int m_HitCount;
    const int m_MaxHitCount;
};
