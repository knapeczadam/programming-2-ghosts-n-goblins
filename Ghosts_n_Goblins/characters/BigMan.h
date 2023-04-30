#pragma once
#include "IEnemy.h"
#include "game/GameObject.h"

class BigMan : public GameObject, public IEnemy
{
public:
    BigMan(Sprite* pSprite, const Point2f& pos);
    virtual ~BigMan() override = default;
    BigMan(const BigMan& other) = delete;
    BigMan(BigMan&& other) noexcept = delete;
    BigMan& operator=(const BigMan& other) = delete;
    BigMan& operator=(BigMan&& other) noexcept = delete;
    
    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;

private:
};
