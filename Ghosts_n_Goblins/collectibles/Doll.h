#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Doll final : public GameObject, public ICollectible
{
public:
    explicit Doll(const Point2f& pos, GameController* pGameController);
    virtual ~Doll() override = default;
    Doll(const Doll& other) = delete;
    Doll(Doll&& other) noexcept = delete;
    Doll& operator=(const Doll& other) = delete;
    Doll& operator=(Doll&& other) noexcept = delete;
};
