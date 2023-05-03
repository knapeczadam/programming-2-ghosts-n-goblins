#pragma once
#include "IEnemy.h"
#include "game/GameObject.h"

class Zombie : public GameObject, public IEnemy
{
public:
    Zombie(Sprite* pSprite, const Point2f& pos);
    virtual ~Zombie() override = default;
    Zombie(const Zombie& other) = delete;
    Zombie(Zombie&& other) noexcept = delete;
    Zombie& operator=(const Zombie& other) = delete;
    Zombie& operator=(Zombie&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
};
