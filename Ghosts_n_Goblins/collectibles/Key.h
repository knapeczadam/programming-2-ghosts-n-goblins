#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Key : public GameObject, public ICollectible
{
public:
    explicit Key(const Point2f& pos, GameController* pGameController);
    virtual ~Key() override = default;
    Key(const Key& other) = delete;
    Key(Key&& other) noexcept = delete;
    Key& operator=(const Key& other) = delete;
    Key& operator=(Key&& other) noexcept = delete;
};
