#pragma once
#include "ICollider.h"

class KeyCollider final : public ICollider
{
public:
    explicit KeyCollider(const Rectf& shape, GameController* pGameController);
    virtual ~KeyCollider() override = default;
    KeyCollider(const KeyCollider& other) = delete;
    KeyCollider(KeyCollider&& other) noexcept = delete;
    KeyCollider& operator=(const KeyCollider& other) = delete;
    KeyCollider& operator=(KeyCollider&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
};
