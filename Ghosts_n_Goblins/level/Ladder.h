#pragma once
#include "IClimable.h"
#include "game/GameObject.h"

class Ladder final : public GameObject, public IClimable
{
public:
    explicit Ladder(const Rectf& shape, GameController* pGameController);
    virtual ~Ladder() override = default;
    Ladder(const Ladder& other) = delete;
    Ladder(Ladder&& other) noexcept = delete;
    Ladder& operator=(const Ladder& other) = delete;
    Ladder& operator=(Ladder&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
};
