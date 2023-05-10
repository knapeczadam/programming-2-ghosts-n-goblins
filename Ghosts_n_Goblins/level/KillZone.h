﻿#pragma once
#include "game/GameObject.h"

class KillZone final : public GameObject
{
public:
    explicit KillZone(float width, float height);
    virtual ~KillZone() override = default;
    KillZone(const KillZone& other) = delete;
    KillZone(KillZone&& other) noexcept = delete;
    KillZone& operator=(const KillZone& other) = delete;
    KillZone& operator=(KillZone&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
};
