#pragma once
#include "IThrowable.h"
#include "collectibles/ICollectible.h"
#include "game/GameObject.h"

/* https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Weapons
 * Dagger (aka Knife, Sword):
 * The Dagger is very much like the Lance, in that it travels straight across and can only be interrupted by hitting an enemy.
 * However, the Dagger is much faster, allowing Arthur to throw many more of them over a period of time.
 */
class Dagger : public GameObject, public IThrowable, public ICollectible
{
public:
	explicit Dagger(const Point2f& pos, bool isFlipped, bool collectible, GameController* pGameController);
    virtual ~Dagger() override = default;
    Dagger(const Dagger& other) = delete;
    Dagger(Dagger&& other) noexcept = delete;
    Dagger& operator=(const Dagger& other) = delete;
    Dagger& operator=(Dagger&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
	
private:
	void SetSprite() const;

private:
	float m_Speed;
	bool m_Collectible;
};
