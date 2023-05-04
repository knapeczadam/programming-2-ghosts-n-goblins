#pragma once
#include "IEnemy.h"

class FlyingKnight : public IEnemy
{
public:
   FlyingKnight(Sprite* pSprite, const Point2f& pos, Player* pPlayer, SoundManager* pSoundManager);
   virtual ~FlyingKnight() override = default;
   FlyingKnight(const FlyingKnight& other) = delete;
   FlyingKnight(FlyingKnight&& other) noexcept = delete;
   FlyingKnight& operator=(const FlyingKnight& other) = delete;
   FlyingKnight& operator=(FlyingKnight&& other) noexcept = delete;

   virtual void Draw() const override;
   virtual void Update(float elapsedSec) override;
   virtual void HandleCollision(GameObject* other) override;
protected:
   virtual void Fly() override;
};
