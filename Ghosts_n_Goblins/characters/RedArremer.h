#pragma once
#include "IEnemy.h"

class RedArremer : public IEnemy
{
public:
   RedArremer(Sprite* pSprite, const Point2f& pos, Player* pPlayer, Sprite* pFX, SoundManager* pSoundManager);
   virtual ~RedArremer() override = default;
   RedArremer(const RedArremer& other) = delete;
   RedArremer(RedArremer&& other) noexcept = delete;
   RedArremer& operator=(const RedArremer& other) = delete;
   RedArremer& operator=(RedArremer&& other) noexcept = delete;

   virtual void Draw() const override;
   virtual void Update(float elapsedSec) override;
   virtual void HandleCollision(GameObject* other) override;
protected:
   virtual void Wait(float elapsedSec) override;
   virtual void Walk(float elapsedSec) override;
   virtual void Shoot(float elapsedSec) override;
   virtual void Fly(float elapsedSec) override;
};
