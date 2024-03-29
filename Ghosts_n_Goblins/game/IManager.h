﻿#pragma once
#include "engine/ITimer.h"

class GameController;

class IManager : public ITimer
{
public:
    explicit IManager(GameController* pGameController);
    virtual ~IManager() override = default;
    IManager(const IManager& other) = delete;
    IManager(IManager&& other) = delete;
    IManager& operator=(const IManager& other) = delete;
    IManager& operator=(IManager&& other) = delete;

    virtual void Update(float elapsedSec);
    virtual void Reset(bool fromCheckpoint = false);

protected:
    virtual void Initialize(bool fromCheckpoint) = 0;
    virtual void CleanUp() = 0;

protected:
    GameController* m_pGameController;
};
