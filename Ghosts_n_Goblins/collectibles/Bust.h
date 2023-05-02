#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Bust : public GameObject, public ICollectible
{
public:
    Bust(Sprite* pSprite, const Point2f& pos);
    virtual ~Bust() override = default;
    Bust(const Bust& other) = delete;
    Bust(Bust&& other) noexcept = delete;
    Bust& operator=(const Bust& other) = delete;
    Bust& operator=(Bust&& other) noexcept = delete;
};
