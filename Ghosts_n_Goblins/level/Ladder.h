#pragma once
#include "IClimable.h"
#include "game/GameObject.h"

class Ladder : public GameObject, public IClimable
{
public:
    Ladder(const Rectf& shape);
    virtual ~Ladder() override = default;
    Ladder(const Ladder& other) = delete;
    Ladder(Ladder&& other) noexcept = delete;
    Ladder& operator=(const Ladder& other) = delete;
    Ladder& operator=(Ladder&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
};
