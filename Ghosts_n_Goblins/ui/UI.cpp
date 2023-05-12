#include "pch.h"
#include "UI.h"

#include "ScoreManager.h"
#include "characters/Player.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"
#include "game/UIManager.h"

UI::UI(Game::Label label, GameController* pGameController)
    : m_Label{label}
    , m_pGameController{pGameController}
    , m_Active{true}
    , m_Visible{true}
    , m_Blinking{false}
    , m_BlinkingTime{0.0f}
    , m_pNumbers{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_NUMBERS)}
    , m_pTextBonus{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_BONUS)}
    , m_pTextBottomRow{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_BOTTOM_ROW)}
    , m_pTextContinue{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_CONTINUE)}
    , m_pTextDeposit{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_DEPOSIT)}
    , m_pTextGameOver{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_GAME_OVER)}
    , m_pTextGameOverPlayerOne(pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_GAME_OVER_PLAYER_ONE))
    , m_pTextTitle{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_TITLE)}
    , m_pTextTopRow{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_TOP_ROW)}
{
    m_pTextBonus->SetPosition(Point2f{80.0f, 112.0f});
    m_pTextBottomRow->SetPosition(Point2f{32.0f, 0.0f});
    m_pTextContinue->SetPosition(Point2f{160.0f, 288.0f});
    m_pTextDeposit->SetPosition(Point2f{112.0f, 224.0f});
    m_pTextGameOver->SetPosition(Point2f{192.0f, 224.0f});
    m_pTextGameOverPlayerOne->SetPosition(Point2f{96.0f, 240.0f});
    m_pTextTitle->SetPosition(Point2f{96.0f, 304.0f});
    m_pTextTopRow->SetPosition(Point2f{16.0f, 432.0f});
}

void UI::Draw() const
{
}

void UI::Reset(bool fromCheckpoint)
{
    
}

void UI::Update(float elapsedSec)
{
    m_pTextGameOver->Update(elapsedSec);
    
    if (m_BlinkingTime > 0.0f)
    {
        StartTimer(m_BlinkingTime);
        if (IsTimerFinished())
        {
            m_Blinking = not m_Blinking;
        }
    }
}

bool UI::IsActive() const
{
    return m_Active;
}

bool UI::IsVisible() const
{
    return m_Visible;
}

void UI::DrawPlayerScore() const
{
    const int playerScore{m_pGameController->m_pPlayerManager->GetPlayer()->GetScore()};
    Point2f pos{128.0f, m_pGameController->m_ViewPort.height - m_pNumbers->GetScaledClipHeight() * 2};
    m_pGameController->m_pUIManager->m_pScoreManager->DrawNumber(pos, playerScore, ScoreManager::Color::WHITE_TAN);
}

void UI::DrawHighScore() const
{
    const int highScore{m_pGameController->m_pUIManager->m_pScoreManager->GetHighScore()};
    Point2f pos{304.0f, m_pGameController->m_ViewPort.height - m_pNumbers->GetScaledClipHeight() * 2};
    m_pGameController->m_pUIManager->m_pScoreManager->DrawNumber(pos, highScore, ScoreManager::Color::WHITE_TAN);
}

void UI::DrawTextBonus() const
{
    m_pTextBonus->Draw();
}

void UI::DrawTextBottomRow() const
{
    m_pTextBottomRow->Draw();
}

void UI::DrawTextContinue() const
{
    m_pTextContinue->Draw();
}

void UI::DrawTextDeposit() const
{
    m_pTextDeposit->Draw();
}

void UI::DrawTextGameOver() const
{
    m_pTextGameOver->Draw();
}

void UI::DrawTextGameOverPlayerOne() const
{
    m_pTextGameOverPlayerOne->Draw();
}

void UI::DrawTextTitle() const
{
    m_pTextTitle->Draw();
}

void UI::DrawTextTopRow() const
{
    m_pTextTopRow->Draw();
}

void UI::DrawNumber(Point2f& pos, int number, Color color) const
{
    const float offset{m_pNumbers->GetScaledClipWidth()};
    m_pNumbers->SetTopOffsetRows(int(color));
    if (number == 0)
    {
        m_pNumbers->SetLeftOffsetCols(0);
        m_pNumbers->SetPosition(pos);
        m_pNumbers->UpdateSourceRect();
        m_pNumbers->UpdateDestinationRect();
        m_pNumbers->Draw();
        pos.x -= offset;
    }
    if (number == -1) // colon
    {
        m_pNumbers->SetLeftOffsetCols(10);
        m_pNumbers->SetPosition(pos);
        m_pNumbers->UpdateSourceRect();
        m_pNumbers->UpdateDestinationRect();
        m_pNumbers->Draw();
        pos.x -= offset;
    }
    for (int tempScore = number; tempScore > 0; tempScore /= 10)
    {
        const int digit{tempScore % 10};
        m_pNumbers->SetLeftOffsetCols(digit);
        m_pNumbers->SetPosition(pos);
        m_pNumbers->UpdateSourceRect();
        m_pNumbers->UpdateDestinationRect();
        m_pNumbers->Draw();
        pos.x -= offset;
    }
    
}
