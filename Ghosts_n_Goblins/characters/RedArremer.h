#pragma once
#include "IEnemy.h"

/*
 * The Red Arremer is possibly one of the most frustating enemies in Ghosts 'n Goblins, second only to the Satans.
 * They are found in every stage but the second stage and the final stage. They are intense guardians that rarely allow intruders past their posted position.
 * They begin on the ground, and leap into the air when fired upon.
 * They can spit balls of fire at you, and they like to maintain their aerial dominance as long as you are chucking weapons about.
 * After staying in the air for a while, they begin to swoop down on Arthur with deadly accuracy.
 * Only the fastest players will be able to outrun their dive. Red Arremers take three hits to destroy, and are worth 1000 points.
 * They may also be holding pots. Players rarely see the same Arremer for 60 seconds, as they usually destroy them, or get destroyed by them before that time.
 * However, if you do deal with the same Arremer for around 60 seconds, they turn white and become even more aggressive.
 */
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
