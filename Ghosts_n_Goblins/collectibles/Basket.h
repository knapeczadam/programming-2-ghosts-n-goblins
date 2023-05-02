#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Basket : public GameObject, public ICollectible
{
public:
    Basket(Sprite* pSprite, const Point2f& pos);
    virtual ~Basket() override = default;
    Basket(const Basket& other) = delete;
    Basket(Basket&& other) noexcept = delete;
    Basket& operator=(const Basket& other) = delete;
    Basket& operator=(Basket&& other) noexcept = delete;
};
