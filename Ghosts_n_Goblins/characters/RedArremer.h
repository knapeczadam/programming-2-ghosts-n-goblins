#pragma once
#include "IEnemy.h"
#include "game/GameObject.h"

class RedArremer : public GameObject, public IEnemy
{
public:
   RedArremer(Sprite* pSprite, const Point2f& pos);
   virtual ~RedArremer() override = default;
   RedArremer(const RedArremer& other) = delete;
   RedArremer(RedArremer&& other) noexcept = delete;
   RedArremer& operator=(const RedArremer& other) = delete;
   RedArremer& operator=(RedArremer&& other) noexcept = delete;

   virtual void Draw() const override;
   virtual void Update(float elapsedSec) override;
   virtual void HandleCollision(GameObject* other) override;
};
