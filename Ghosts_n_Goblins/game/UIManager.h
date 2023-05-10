﻿#pragma once
#include "IManager.h"

class CreditManager;
class HUD;
class InitialDrawer;
class InitialSaver;
class Map;
class RankingDrawer;
class ScoreManager;

class UIManager final : public IManager
{
public:
    explicit UIManager(GameController* pGameController);
    virtual ~UIManager() override;
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;
    UIManager(UIManager&&) = delete;
    UIManager& operator=(UIManager&&) = delete;

    virtual void Reset() override;
    void UpdateRemainingTime();

protected:
    virtual void Initialize() override;

public:
    CreditManager* m_pCreditManager;
    HUD* m_pHUD;
    InitialDrawer* m_pInitialDrawer;
    InitialSaver* m_pInitialSaver;
    Map* m_pMap;
    RankingDrawer* m_pRankingDrawer;
    ScoreManager* m_pScoreManager;
};