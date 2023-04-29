#pragma once
#include "IThrowable.h"
#include "collectibles/ICollectible.h"
#include "game/GameObject.h"

class Lance: public GameObject, public IThrowable, public ICollectible
{
public:
	Lance(Sprite* pSprite, const Point2f& pos, bool isFlipped);
	virtual ~Lance() override = default;
	Lance(const Lance& other) = delete;
	Lance(Lance&& other) noexcept = delete;
	Lance& operator=(const Lance& other) = delete;
	Lance& operator=(Lance&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
	
private:
	float m_Speed;
};
