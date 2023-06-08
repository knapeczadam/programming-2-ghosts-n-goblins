#pragma once
#include "game/GameObject.h"

class Damage : public GameObject
{
public:
    explicit Damage(const Point2f& pos, bool flipped, GameController* pGameController);
    virtual ~Damage() override = default;
    Damage(const Damage& other) = delete;
    Damage(Damage&& other) noexcept = delete;
    Damage& operator=(const Damage& other) = delete;
    Damage& operator=(Damage&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
};
