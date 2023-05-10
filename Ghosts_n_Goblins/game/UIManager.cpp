#include "pch.h"
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

UIManager::UIManager(GameController* pGameController)
    : IManager{pGameController}
    , m_pCreditManager{nullptr}
    , m_pHUD{nullptr}
    , m_pInitialDrawer{nullptr}
    , m_pInitialSaver{nullptr}
    , m_pMap{nullptr}
    , m_pRankingDrawer{nullptr}
    , m_pScoreManager{nullptr}
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
}

void UIManager::Initialize()
{
    m_pHUD = new HUD{m_pGameController};
    m_pInitialSaver = new InitialSaver{m_pGameController};
    m_pMap = new Map{m_pGameController};
    m_pScoreManager = new ScoreManager{m_pGameController};
    m_pInitialDrawer = new InitialDrawer{m_pGameController};
    m_pRankingDrawer = new RankingDrawer{m_pGameController};
    m_pCreditManager = new CreditManager{m_pGameController};
    m_pScoreManager->LoadHighScores();
}

void UIManager::Reset()
{
    IManager::Reset();
}

void UIManager::UpdateRemainingTime()
{
    
    StartTimer(120);
    const int seconds{GetSeconds()};
    const int minutes{GetMinutes()};

    int firstDigit, secondDigit, thirdDigit;
    firstDigit = minutes;
    if (seconds > 9)
    {
        secondDigit = seconds / 10;
        thirdDigit = seconds % 10;
    }
    else
    {
        secondDigit = 0;
        thirdDigit = seconds;
    }
    if (GetRemainingTime() <= 15.0f)
    {
        // m_pSoundManager->PlayStream(Game::Label::S_05_HURRY_UP, false);
    }
    m_pHUD->SetFirstDigit(firstDigit);
    m_pHUD->SetSecondDigit(secondDigit);
    m_pHUD->SetThirdDigit(thirdDigit);

    if (IsTimerFinished())
    {
        std::cout << "Time is up!\n";
        // TODO: Game over
    }
}
