#pragma once
#include "IThrowable.h"
#include "collectibles/ICollectible.h"
#include "game/GameObject.h"

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
