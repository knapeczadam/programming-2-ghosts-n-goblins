﻿#include "pch.h"
#include "UIManager.h"

#include "GameController.h"
#include "ui/CreditManager.h"
#include "ui/HUD.h"
#include "ui/InitialDrawer.h"
#include "ui/InitialSaver.h"
#include "ui/Map.h"
#include "ui/RankingDrawer.h"
#include "ui/ScoreManager.h"

#include <iostream>

#include "engine/SoundManager.h"

UIManager::UIManager(GameController* pGameController)
    : IManager{pGameController}
    , m_pCreditManager{nullptr}
    , m_pHUD{nullptr}
    , m_pInitialDrawer{nullptr}
    , m_pInitialSaver{nullptr}
    , m_pMap{nullptr}
    , m_pRankingDrawer{nullptr}
    , m_pScoreManager{nullptr}
    , m_pUI{nullptr}
{
    m_pGameController->m_pUIManager = this;
    Initialize();
}

UIManager::~UIManager()
{
    delete m_pCreditManager;
    delete m_pHUD;
    delete m_pInitialDrawer;
    delete m_pInitialSaver;
    delete m_pMap;
    delete m_pRankingDrawer;
    delete m_pScoreManager;
    delete m_pUI;
}

void UIManager::Initialize()
{
    m_pCreditManager = new CreditManager{m_pGameController};
    m_pHUD = new HUD{m_pGameController};
    m_pInitialDrawer = new InitialDrawer{m_pGameController};
    m_pInitialSaver = new InitialSaver{m_pGameController};
    m_pMap = new Map{m_pGameController};
    m_pRankingDrawer = new RankingDrawer{m_pGameController};
    m_pScoreManager = new ScoreManager{m_pGameController};
    m_pUI = new UI{Game::Label::U_UI, m_pGameController};
}

void UIManager::Reset(bool fromCheckpoint)
{
}