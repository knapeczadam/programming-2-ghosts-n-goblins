#pragma once
#include "engine/ITimer.h"

class GameController;

class ISpawner : public ITimer
{
public:
    ISpawner(const Rectf& boundaries, GameController* pGameController);
    virtual ~ISpawner() = default;
    ISpawner(const ISpawner&) = delete;
    ISpawner& operator=(const ISpawner&) = delete;
    ISpawner(ISpawner&&) = delete;
    ISpawner& operator=(ISpawner&&) = delete;

    virtual void Spawn() = 0;
    
protected:
    virtual bool IsPlayerBetweenBoundaries() const final;


protected:
    Rectf m_SpawnBoundaries;
    Point2f m_SpawnPos;
    GameController* m_pGameController;
};
