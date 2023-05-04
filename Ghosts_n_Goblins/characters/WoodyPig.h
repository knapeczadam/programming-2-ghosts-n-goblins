#pragma once
#include "IEnemy.h"

class WoodyPig : IEnemy
{
public:
   WoodyPig(Sprite* pSprite, const Point2f& pos, Player* pPlayer,Sprite* pFX, SoundManager* pSoundManager);
   virtual ~WoodyPig() override = default;
   WoodyPig(const WoodyPig& other) = delete;
   WoodyPig(WoodyPig&& other) noexcept = delete;
   WoodyPig& operator=(const WoodyPig& other) = delete;
   WoodyPig& operator=(WoodyPig&& other) noexcept = delete;

   virtual void Draw() const override;
   virtual void Update(float elapsedSec) override;
   virtual void HandleCollision(GameObject* other) override;
protected:
   virtual void Shoot(float elapsedSec) override;
   virtual void Fly(float elapsedSec) override;
};
