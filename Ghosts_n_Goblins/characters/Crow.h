#pragma once
#include "IEnemy.h"
#include "game/GameObject.h"

class Crow : public GameObject, public IEnemy
{
public:
    Crow(Sprite* pSprite, const Point2f& pos);
    virtual ~Crow() override = default;
    Crow(const Crow& other) = delete;
    Crow(Crow&& other) noexcept = delete;
    Crow& operator=(const Crow& other) = delete;
    Crow& operator=(Crow&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* player) override;
};
