﻿#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Shield : public GameObject, public ICollectible
{
public:
    Shield(Sprite* pSprite, const Point2f& pos);
    virtual ~Shield() override = default;
    Shield(const Shield& other) = delete;
    Shield(Shield&& other) noexcept = delete;
    Shield& operator=(const Shield& other) = delete;
    Shield& operator=(Shield&& other) noexcept = delete;
};