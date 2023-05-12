#include "pch.h"
#include "MenuManager.h"

#include "Camera.h"
#include "CameraManager.h"
#include "GameController.h"
#include "UIManager.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "ui/CreditManager.h"
#include "ui/HUD.h"
#include "ui/InitialSaver.h"
#include "ui/Map.h"
#include "ui/RankingDrawer.h"
#include "ui/ScoreManager.h"

MenuManager::MenuManager(GameController* pGameController)
    : IManager{pGameController}
      , m_MaxIdx{3}
      , m_Idx{0}
      , m_Intervals{}
      , m_CreditInserted{false}
      , m_pBackground1{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_MENU_BACKGROUND_1)}
      , m_pBackground2{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_MENU_BACKGROUND_2)}
      , m_pBackground3{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_MENU_BACKGROUND_3)}
      , m_pBackground4{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_MENU_BACKGROUND_4)}
      , m_Time{}
{
    pGameController->m_pMenuManager = this;
    Initialize();
}

void MenuManager::Initialize()
{
    // intervals in seconds
    m_Intervals.insert(m_Intervals.end(), {
                           4.0f, 4.0f, 5.0f, 4.0f
                       });
}

void MenuManager::DrawMenu() const
{
    switch (m_Idx)
    {
    case 0:
        m_pBackground2->Draw();
        m_pGameController->m_pUIManager->m_pHUD->Draw();
        m_pGameController->m_pUIManager->m_pUI->DrawTextTitle();
        m_pGameController->m_pUIManager->m_pUI->DrawTextGameOver();
        break;
    case 1:
        m_pBackground3->Draw();
        m_pGameController->m_pUIManager->m_pUI->DrawTextTopRow();
        m_pGameController->m_pUIManager->m_pScoreManager->DrawPlayerScore();
        m_pGameController->m_pUIManager->m_pScoreManager->DrawHighScore();
        m_pGameController->m_pUIManager->m_pUI->DrawTextTitle();
        m_pGameController->m_pUIManager->m_pUI->DrawTextDeposit();
        m_pGameController->m_pUIManager->m_pUI->DrawTextBottomRow();
        m_pGameController->m_pUIManager->m_pCreditManager->DrawCredits();
        break;
    case 2:
        m_pBackground4->Draw();
        m_pGameController->m_pUIManager->m_pUI->DrawTextTopRow();
        m_pGameController->m_pUIManager->m_pScoreManager->DrawPlayerScore();
        m_pGameController->m_pUIManager->m_pScoreManager->DrawHighScore();
        m_pGameController->m_pUIManager->m_pRankingDrawer->Draw();
        m_pGameController->m_pUIManager->m_pUI->DrawTextBottomRow();
        m_pGameController->m_pUIManager->m_pCreditManager->DrawCredits();
        break;
    case 3:
        m_pBackground1->Draw();
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

void MenuManager::DrawRanking() const
{
    m_pGameController->m_pUIManager->m_pRankingDrawer->Draw();
}

void MenuManager::DrawSaveScore() const
{
    m_pGameController->m_pUIManager->m_pInitialSaver->Draw();
}

void MenuManager::UpdateContinue(float elapsedSec)
{
    m_Time = GetRemainingTimeDigits(10);
}

void MenuManager::UpdateGameOver(float elapsedSec)
{ 
}

void MenuManager::UpdateMap(float elapsedSec)
{
    m_pGameController->m_pCameraManager->GetCamera()->SetBoundaries(m_pGameController->m_pUIManager->m_pMap->GetBoundaries());
    m_pGameController->m_pUIManager->m_pMap->Update(elapsedSec);
}

void MenuManager::DrawContinue() const
{
    m_pGameController->m_pUIManager->m_pUI->DrawTextTopRow();
    m_pGameController->m_pUIManager->m_pScoreManager->DrawPlayerScore();
    m_pGameController->m_pUIManager->m_pScoreManager->DrawHighScore();
    m_pGameController->m_pUIManager->m_pUI->DrawTextContinue();
    Point2f pos{258.0f, 224.0f};
    m_pGameController->m_pUIManager->m_pUI->DrawNumber(pos, m_Time.firstDigit, UI::Color::RED);
    m_pGameController->m_pUIManager->m_pUI->DrawNumber(pos, m_Time.secondDigit, UI::Color::RED);
}

void MenuManager::DrawGameOver() const
{
    m_pGameController->m_pUIManager->m_pUI->DrawTextGameOverPlayerOne();
}

void MenuManager::DrawMap() const
{
    glPushMatrix();
    m_pGameController->m_pCameraManager->Transform(Game::Label::D_DUMMY);
    m_pGameController->m_pUIManager->m_pMap->Draw();
    glPopMatrix();
    m_pGameController->m_pUIManager->m_pUI->DrawTextTopRow();
    m_pGameController->m_pUIManager->m_pMap->DrawTextPlayerOneReady();
    m_pGameController->m_pUIManager->m_pScoreManager->DrawPlayerScore();
    m_pGameController->m_pUIManager->m_pScoreManager->DrawHighScore();
}

void MenuManager::UpdateMenu(float elapsedSec)
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

void MenuManager::UpdateRanking(float elapsedSec)
{
}

void MenuManager::UpdateSaveScore(float elapsedSec)
{
   m_pGameController->m_pUIManager->m_pInitialSaver->Update(elapsedSec); 
}

void MenuManager::Reset(bool fromCheckpoint)
{
    m_Idx = 0;
    m_CreditInserted = false;
    m_pGameController->m_pUIManager->m_pCreditManager->Reset();
    m_pGameController->m_pUIManager->m_pInitialSaver->Reset();
    ResetTimer();
}
