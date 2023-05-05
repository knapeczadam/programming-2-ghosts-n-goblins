#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class MoneyBag : public GameObject, public ICollectible
{
public:
    MoneyBag(const Point2f& pos, SpriteFactory* pSpriteFactory);
    virtual ~MoneyBag() override = default;
    MoneyBag(const MoneyBag& other) = delete;
    MoneyBag(MoneyBag&& other) noexcept = delete;
    MoneyBag& operator=(const MoneyBag& other) = delete;
    MoneyBag& operator=(MoneyBag&& other) noexcept = delete;
};
