#pragma once
#include "game/GameObject.h"

class Water : public GameObject
{
public:
    Water(const Point2f& pos, SpriteFactory* pSpriteFactory);
    Water(const Point2f& pos, float clipWidth, SpriteFactory* pSpriteFactory);
    virtual ~Water() override = default;
    Water(const Water& other) = delete;
    Water(Water&& other) noexcept = delete;
    Water& operator=(const Water& other) = delete;
    Water& operator=(Water&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
};
