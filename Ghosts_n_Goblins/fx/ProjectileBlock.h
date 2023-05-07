#pragma once
#include "game/GameObject.h"

class ProjectileBlock : public GameObject
{
public:
    explicit ProjectileBlock(Game::Label label, const Point2f& pos, bool flipped, GameController* pGameController);
    virtual ~ProjectileBlock() override = default;
    ProjectileBlock(const ProjectileBlock& other) = delete;
    ProjectileBlock(ProjectileBlock&& other) noexcept = delete;
    ProjectileBlock& operator=(const ProjectileBlock& other) = delete;
    ProjectileBlock& operator=(ProjectileBlock&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
};

