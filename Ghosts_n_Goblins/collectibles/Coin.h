#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Coin : public GameObject, public ICollectible
{
public:
    Coin(Sprite* pSprite, const Point2f& pos);
    virtual ~Coin() override = default;
    Coin(const Coin& other) = delete;
    Coin(Coin&& other) noexcept = delete;
    Coin& operator=(const Coin& other) = delete;
    Coin& operator=(Coin&& other) noexcept = delete;
};
