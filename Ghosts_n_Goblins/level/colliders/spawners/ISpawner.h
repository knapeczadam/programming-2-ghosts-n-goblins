#pragma once
#include "level/colliders/ICollider.h"

class GameController;

class ISpawner : public ICollider
{
public:
    explicit ISpawner(Game::Label label, const Rectf& shape, GameController* pGameController);
    virtual ~ISpawner() override = default;
    ISpawner(const ISpawner&) = delete;
    ISpawner(ISpawner&&) = delete;
    ISpawner& operator=(const ISpawner&) = delete;
    ISpawner& operator=(ISpawner&&) = delete;

    virtual void Spawn() = 0;
    virtual bool IsPlayerBetweenBoundaries() const final;
};
