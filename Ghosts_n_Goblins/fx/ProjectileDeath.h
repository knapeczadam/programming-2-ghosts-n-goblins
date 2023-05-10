﻿#pragma once
#include "game/GameObject.h"

class ProjectileDeath final : public GameObject
{
public:
    explicit ProjectileDeath(const Point2f& pos, bool flipped, GameController* pGameController);
    virtual ~ProjectileDeath() override = default;
    ProjectileDeath(const ProjectileDeath& other) = delete;
    ProjectileDeath(ProjectileDeath&& other) noexcept = delete;
    ProjectileDeath& operator=(const ProjectileDeath& other) = delete;
    ProjectileDeath& operator=(ProjectileDeath&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
};
