#pragma once
#include "IThrowable.h"
#include "collectibles/ICollectible.h"
#include "game/GameObject.h"

class Torch : public GameObject, public IThrowable, public ICollectible
{
public:
	Torch(const Point2f& pos, bool isFlipped, bool collectible, SpriteFactory* pSpriteFactory);
	virtual ~Torch() override = default;
	Torch(const Torch& other) = delete;
	Torch(Torch&& other) noexcept = delete;
	Torch& operator=(const Torch& other) = delete;
	Torch& operator=(Torch&& other) noexcept = delete;

	virtual void Update(float elapsedSec) override;
private:
	void SetSprite() const;	
private:
	float m_Speed;
	bool m_Collectible;
};
