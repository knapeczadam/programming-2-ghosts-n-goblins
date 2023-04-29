﻿#pragma once
#include "IThrowable.h"
#include "collectibles/ICollectible.h"
#include "game/GameObject.h"

class Torch : public GameObject, public IThrowable, public ICollectible
{
public:
	Torch(Sprite* pSprite, const Point2f& pos);
	virtual ~Torch() override = default;
	Torch(const Torch& other) = delete;
	Torch(Torch&& other) noexcept = delete;
	Torch& operator=(const Torch& other) = delete;
	Torch& operator=(Torch&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
};
