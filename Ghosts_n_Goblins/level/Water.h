#pragma once
#include "game/GameObject.h"

class Water : public GameObject
{
public:
    Water(Sprite* pSprite, const Point2f& pos);
    Water(Sprite* pSprite, const Point2f& pos, float clipWidth);
    virtual ~Water() override = default;
    Water(const Water& other) = delete;
    Water(Water&& other) noexcept = delete;
    Water& operator=(const Water& other) = delete;
    Water& operator=(Water&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
};
