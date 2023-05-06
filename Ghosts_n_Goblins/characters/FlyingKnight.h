#pragma once
#include "IEnemy.h"

/* https://strategywiki.org/wiki/Ghosts_%27n_Goblins/Enemies#Flying_Knights
 * The tortured souls of knights who died in battle have become restless and now haunt the forest that leads to the gates to the Makai village.
 * They travel in a wave-like motion, oblivious to everything around them, launching into a battle the ended eons ago.
 * They carry their shields with them, which makes them invulnerable to attacks from the front.
 * A single attack which hits them from behind will destroy them.
 * They are worth 100 points, and they can carry pots with them.
 */
class FlyingKnight : public IEnemy
{
public:
    explicit FlyingKnight(const Point2f& pos, GameController* pGameController);
   virtual ~FlyingKnight() override = default;
   FlyingKnight(const FlyingKnight& other) = delete;
   FlyingKnight(FlyingKnight&& other) noexcept = delete;
   FlyingKnight& operator=(const FlyingKnight& other) = delete;
   FlyingKnight& operator=(FlyingKnight&& other) noexcept = delete;

   virtual void Draw() const override;
   virtual void Update(float elapsedSec) override;
   virtual void HandleCollision(GameObject* other) override;
protected:
   virtual void Fly(float elapsedSec) override;
};
