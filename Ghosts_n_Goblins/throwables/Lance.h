#pragma once
#include "IThrowable.h"
#include "collectibles/ICollectible.h"
#include "game/GameObject.h"

class Lance: public GameObject, public IThrowable, public ICollectible
{
public:
	explicit Lance(const Point2f& pos, bool isFlipped, bool collectible, GameController* pGameController);
	virtual ~Lance() override = default;
	Lance(const Lance& other) = delete;
	Lance(Lance&& other) noexcept = delete;
	Lance& operator=(const Lance& other) = delete;
	Lance& operator=(Lance&& other) noexcept = delete;

	virtual void Update(float elapsedSec) override;
private:
	void SetSprite() const;
private:
	float m_Speed;
	bool m_Collectible;
};
