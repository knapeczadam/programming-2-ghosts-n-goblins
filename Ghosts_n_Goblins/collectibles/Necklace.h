#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Necklace : public GameObject, public ICollectible
{
public:
    Necklace(Sprite* pSprite, const Point2f& pos);
    virtual ~Necklace() override = default;
    Necklace(const Necklace& other) = delete;
    Necklace(Necklace&& other) noexcept = delete;
    Necklace& operator=(const Necklace& other) = delete;
    Necklace& operator=(Necklace&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
};
