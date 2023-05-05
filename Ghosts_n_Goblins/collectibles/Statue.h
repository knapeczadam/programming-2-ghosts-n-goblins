#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Statue : public GameObject, public ICollectible
{
public:
    Statue(const Point2f& pos, SpriteFactory* pSpriteFactory);
    virtual ~Statue() override = default;
    Statue(const Statue& other) = delete;
    Statue(Statue&& other) noexcept = delete;
    Statue& operator=(const Statue& other) = delete;
    Statue& operator=(Statue&& other) noexcept = delete;
};
