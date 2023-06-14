#pragma once
#include "game/GameObject.h"

class Water final : public GameObject
{
public:
    explicit Water(const Point2f& pos, GameController* pGameController);
    explicit Water(const Point2f& pos, float clipWidth, GameController* pGameController);
    virtual ~Water() override = default;
    Water(const Water& other) = delete;
    Water(Water&& other) noexcept = delete;
    Water& operator=(const Water& other) = delete;
    Water& operator=(Water&& other) noexcept = delete;
};
