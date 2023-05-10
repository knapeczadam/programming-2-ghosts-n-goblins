#include "pch.h"
#include "MenuManager.h"

#include "GameController.h"
#include "UIManager.h"
#include "ui/CreditManager.h"
#include "ui/HUD.h"
#include "ui/RankingDrawer.h"
#include "ui/ScoreManager.h"

MenuManager::MenuManager(GameController* pGameController)
    : IManager{pGameController}
      , m_MaxIdx{3}
      , m_Idx{0}
      , m_Intervals{}
{
    pGameController->m_pMenuManager = this;
    Initialize();
}

void MenuManager::Initialize()
{
    // intervals in seconds
    m_Intervals.insert(m_Intervals.end(), {
                           4, 4, 5, 4
                       });
}

void MenuManager::Draw() const
{
    switch (m_Idx)
    {
    case 0:
        m_pGameController->m_pUIManager->m_pHUD->Draw();
        m_pGameController->m_pUIManager->m_pUI->DrawTextTitle();
        m_pGameController->m_pUIManager->m_pUI->DrawTextGameOver();
        break;
    case 1:
        m_pGameController->m_pUIManager->m_pUI->DrawTextTopRow();
        m_pGameController->m_pUIManager->m_pScoreManager->DrawPlayerScore();
        m_pGameController->m_pUIManager->m_pScoreManager->DrawHighScore();
        m_pGameController->m_pUIManager->m_pUI->DrawTextTitle();
        m_pGameController->m_pUIManager->m_pUI->DrawTextDeposit();
        m_pGameController->m_pUIManager->m_pUI->DrawTextBottomRow();
        m_pGameController->m_pUIManager->m_pCreditManager->DrawCredits();
        break;
    case 2:
        m_pGameController->m_pUIManager->m_pUI->DrawTextTopRow();
        m_pGameController->m_pUIManager->m_pScoreManager->DrawPlayerScore();
        m_pGameController->m_pUIManager->m_pScoreManager->DrawHighScore();
        m_pGameController->m_pUIManager->m_pRankingDrawer->Draw(); 
        m_pGameController->m_pUIManager->m_pUI->DrawTextBottomRow();
        m_pGameController->m_pUIManager->m_pCreditManager->DrawCredits();
        break;
    case 3:
        m_pGameController->m_pUIManager->m_pUI->DrawTextTopRow();
        m_pGameController->m_pUIManager->m_pScoreManager->DrawPlayerScore();
        m_pGameController->m_pUIManager->m_pScoreManager->DrawHighScore();
        m_pGameController->m_pUIManager->m_pUI->DrawTextTitle();
        m_pGameController->m_pUIManager->m_pUI->DrawTextBonus();
        m_pGameController->m_pUIManager->m_pUI->DrawTextBottomRow();
        m_pGameController->m_pUIManager->m_pCreditManager->DrawCredits();
        break;
    }
}

void MenuManager::Update(float elapsedSec)
{
    m_pGameController->m_pUIManager->m_pUI->Update(elapsedSec);
    m_pGameController->m_pUIManager->m_pCreditManager->Update(elapsedSec);
    
    if (m_pGameController->m_pUIManager->m_pCreditManager->GetCredits())
    {
        if (not m_CreditInserted)
        {
            m_Idx = 3;
            m_CreditInserted = true;
            ResetTimer();
        }
        StartTimer(m_Intervals[m_Idx]);
        if (IsTimerFinished())
        {
            m_Idx = (m_Idx + 1) % (m_MaxIdx + 1);
        }
    }
    else
    {
        StartTimer(m_Intervals[m_Idx]);
        if (IsTimerFinished())
        {
            m_Idx = (m_Idx + 1) % m_MaxIdx;
        }
    }
}

void MenuManager::Reset()
{
    m_Idx = 0;
    m_CreditInserted = false;
}
