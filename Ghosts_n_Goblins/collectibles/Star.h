#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Star : public GameObject, public ICollectible
{
public:
    Star(Sprite* pSprite, const Point2f& pos);
    virtual ~Star() override = default;
    Star(const Star& other) = delete;
    Star(Star&& other) noexcept = delete;
    Star& operator=(const Star& other) = delete;
    Star& operator=(Star&& other) noexcept = delete;
};
