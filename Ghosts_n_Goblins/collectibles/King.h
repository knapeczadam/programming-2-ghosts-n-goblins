#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class King : public GameObject, public ICollectible
{
public:
    explicit King(const Point2f& pos, GameController* pGameController);
    virtual ~King() override = default;
    King(const King& other) = delete;
    King(King&& other) noexcept = delete;
    King& operator=(const King& other) = delete;
    King& operator=(King&& other) noexcept = delete;
};
