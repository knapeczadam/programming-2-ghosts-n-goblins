#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Coin final : public GameObject, public ICollectible
{
public:
    explicit Coin(const Point2f& pos, GameController* pGameController);
    virtual ~Coin() override = default;
    Coin(const Coin& other) = delete;
    Coin(Coin&& other) noexcept = delete;
    Coin& operator=(const Coin& other) = delete;
    Coin& operator=(Coin&& other) noexcept = delete;
};
