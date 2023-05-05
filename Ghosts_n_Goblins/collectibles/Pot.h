#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Pot : public GameObject, public ICollectible
{
public:
    explicit Pot(const Point2f& pos, GameController* pGameController);
    virtual ~Pot() override = default;
    Pot(const Pot& other) = delete;
    Pot(Pot&& other) noexcept = delete;
    Pot& operator=(const Pot& other) = delete;
    Pot& operator=(Pot&& other) noexcept = delete;
};
