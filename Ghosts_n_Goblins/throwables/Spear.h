#pragma once
#include "IThrowable.h"
#include "game/GameObject.h"

class Spear final : public GameObject, public IThrowable
{
public:
    explicit Spear(const Point2f& pos, GameController* pGameController);
    virtual ~Spear() override = default;
    Spear(const Spear& other) = delete;
    Spear(Spear&& other) noexcept = delete;
    Spear& operator=(const Spear& other) = delete;
    Spear& operator=(Spear&& other) noexcept = delete;
};
