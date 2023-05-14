#pragma once
#include "IThrowable.h"
#include "collectibles/ICollectible.h"
#include "game/GameObject.h"

/**
 * \brief 
 * Lance (aka Spear):
 * The Lance is Arthur's default weapon at the beginning of the game.
 * Lances travel straight across at a moderate speed, and are only interrupted by enemies.
 * In the Famicom/NES-based versions of the game, the Dragon is invulnerable to the Lance.
 * In addition, only two may be in the air at once.
 * <a href="https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Weapons">StrategyWiki</a>
 */
class Lance final : public GameObject, public IThrowable, public ICollectible
{
public:
	explicit Lance(const Point2f& pos, bool isFlipped, bool collectible, GameController* pGameController);
	virtual ~Lance() override = default;
	Lance(const Lance& other) = delete;
	Lance(Lance&& other) noexcept = delete;
	Lance& operator=(const Lance& other) = delete;
	Lance& operator=(Lance&& other) noexcept = delete;

	virtual void Update(float elapsedSec) override;
	virtual void Awake(float elapsedSec) override;
private:
	void SetSprite() const;
private:
	bool m_Collectible;
};
