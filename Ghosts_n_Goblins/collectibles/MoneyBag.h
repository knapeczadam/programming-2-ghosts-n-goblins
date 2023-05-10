#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class MoneyBag final : public GameObject, public ICollectible
{
public:
    explicit MoneyBag(const Point2f& pos, GameController* pGameController);
    virtual ~MoneyBag() override = default;
    MoneyBag(const MoneyBag& other) = delete;
    MoneyBag(MoneyBag&& other) noexcept = delete;
    MoneyBag& operator=(const MoneyBag& other) = delete;
    MoneyBag& operator=(MoneyBag&& other) noexcept = delete;
};
