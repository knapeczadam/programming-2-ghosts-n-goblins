#pragma once
#include "engine/ITimer.h"

class GameController;

class Spawner : public ITimer
{
public:
    Spawner(const Rectf& boundaries, GameController* pGameController);
    virtual ~Spawner() = default;
    Spawner(const Spawner&) = delete;
    Spawner& operator=(const Spawner&) = delete;
    Spawner(Spawner&&) = delete;
    Spawner& operator=(Spawner&&) = delete;

    virtual void Spawn() = 0;
    
protected:
    virtual bool IsPlayerBetwwenBoundaries() const final;


protected:
    Rectf m_SpawnBoundaries;
    Point2f m_SpawnPos;
    GameController* m_pGameController;
};
