#pragma once
#include "IEnemy.h"
#include "game/GameObject.h"

class WoodyPig : public GameObject, IEnemy
{
public:
   WoodyPig(Sprite* pSprite, const Point2f& pos);
   virtual ~WoodyPig() override = default;
   WoodyPig(const WoodyPig& other) = delete;
   WoodyPig(WoodyPig&& other) noexcept = delete;
   WoodyPig& operator=(const WoodyPig& other) = delete;
   WoodyPig& operator=(WoodyPig&& other) noexcept = delete;

   virtual void Draw() const override;
   virtual void Update(float elapsedSec) override;
   virtual void HandleCollision(GameObject* other) override;
};
