#pragma once
#include "IEnemy.h"
#include "game/GameObject.h"

class FlyingKnight : public GameObject, public IEnemy
{
public:
   FlyingKnight(Sprite* pSprite, const Point2f& pos);
   virtual ~FlyingKnight() override = default;
   FlyingKnight(const FlyingKnight& other) = delete;
   FlyingKnight(FlyingKnight&& other) noexcept = delete;
   FlyingKnight& operator=(const FlyingKnight& other) = delete;
   FlyingKnight& operator=(FlyingKnight&& other) noexcept = delete;

   virtual void Draw() const override;
   virtual void Update(float elapsedSec) override;
   virtual void HandleCollision(GameObject* player) override;
};
