#pragma once
#include "game/GameObject.h"

class Door final : public GameObject
{
public:
    explicit Door(const Point2f& pos, GameController* pGameController);
    virtual ~Door() override = default;
    Door(const Door& other) = delete;
    Door(Door&& other) noexcept = delete;
    Door& operator=(const Door& other) = delete;
    Door& operator=(Door&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
};
