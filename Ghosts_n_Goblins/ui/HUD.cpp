// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "HUD.h"

#include "ScoreManager.h"
#include "characters/Player.h"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"


HUD::HUD(GameController* pGameController)
    : UI{Game::Label::U_HUD, pGameController}
      , m_pTextTopRow{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_TOP_ROW)}
      , m_pLife{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_LIFE)}
      , m_pNumbers(pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_NUMBERS))
      , m_pWeapons(pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_WEAPONS))
      , m_pTextTime{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_TIME)}
      , m_pFrame{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_FRAME)}
      , m_FirstDigit{}
      , m_SecondDigit{}
      , m_ThirdDigit{}
{
    m_pTextTime->SetPosition(Point2f{32.0f, 400.0f});
    m_pTextTopRow->SetPosition(Point2f{16.0f, 432.0f});
    m_pFrame->SetPosition(Point2f{m_pGameController->m_ViewPort.width / 2 - m_pFrame->GetScaledClipWidth() / 2, 0.0f});
}

void HUD::Draw() const
{
    DrawLives();
    DrawPlayerScore();
    DrawHighScore();
    DrawTextTime();
    DrawRemainingTime();
    DrawTextTopRow();
    DrawFrame();
    DrawWeapon();
}

void HUD::SetFirstDigit(int digit)
{
    m_FirstDigit = digit;
}

void HUD::SetSecondDigit(int digit)
{
    m_SecondDigit = digit;
}

void HUD::SetThirdDigit(int digit)
{
    m_ThirdDigit = digit;
}

void HUD::DrawLives() const
{
    for (int idx{}; idx < m_pGameController->m_pPlayerManager->GetPlayer()->GetLives() - 1; ++idx)
    {
        m_pLife->SetPosition(Point2f{idx * m_pLife->GetScaledClipWidth(), 0});
        m_pLife->Draw();
    }
}

void HUD::DrawPlayerScore() const
{
    const int playerScore{m_pGameController->m_pPlayerManager->GetPlayer()->GetScore()};
    Point2f pos{128.0f, m_pGameController->m_ViewPort.height - m_pNumbers->GetScaledClipHeight() * 2};
    m_pGameController->m_pScoreManager->DrawNumber(pos, playerScore, ScoreManager::Color::WHITE_TAN);
}

void HUD::DrawHighScore() const
{
    const int highScore{m_pGameController->m_pScoreManager->GetHighScore()};
    Point2f pos{304.0f, m_pGameController->m_ViewPort.height - m_pNumbers->GetScaledClipHeight() * 2};
    m_pGameController->m_pScoreManager->DrawNumber(pos, highScore, ScoreManager::Color::WHITE_TAN);
}

void HUD::DrawRemainingTime() const
{
    Point2f pos{32, m_pGameController->m_ViewPort.height - m_pNumbers->GetScaledClipHeight() * 4};
    const float offset{m_pNumbers->GetScaledClipWidth()};
    m_pNumbers->SetTopOffsetRows(1);
    // FIRST DIGIT
    m_pNumbers->SetLeftOffsetCols(m_FirstDigit);
    m_pNumbers->SetPosition(pos);
    m_pNumbers->UpdateSourceRect();
    m_pNumbers->UpdateDestinationRect();
    m_pNumbers->Draw();

    // COLON
    pos.x += offset;
    m_pNumbers->SetLeftOffsetCols(10);
    m_pNumbers->SetPosition(pos);
    m_pNumbers->UpdateSourceRect();
    m_pNumbers->UpdateDestinationRect();
    m_pNumbers->Draw();

    // SECOND DIGIT
    pos.x += offset;
    m_pNumbers->SetLeftOffsetCols(m_SecondDigit);
    m_pNumbers->SetPosition(pos);
    m_pNumbers->UpdateSourceRect();
    m_pNumbers->UpdateDestinationRect();
    m_pNumbers->Draw();

    // THIRD DIGIT
    pos.x += offset;
    m_pNumbers->SetLeftOffsetCols(m_ThirdDigit);
    m_pNumbers->SetPosition(pos);
    m_pNumbers->UpdateSourceRect();
    m_pNumbers->UpdateDestinationRect();
    m_pNumbers->Draw();
}

void HUD::DrawTextTime() const
{
    m_pTextTime->Draw();
}

void HUD::DrawTextTopRow() const
{
    m_pTextTopRow->Draw();
}

void HUD::DrawWeapon() const
{
    Point2f pos;
    pos.x = m_pGameController->m_ViewPort.width / 2 - m_pWeapons->GetScaledClipWidth() / 2;
    pos.y = m_pWeapons->GetScaledClipHeight() / 2;

    switch (m_pGameController->m_pPlayerManager->GetPlayer()->GetWeapon())
    {
    case Game::Label::T_DAGGER:
        m_pWeapons->SetLeftOffsetCols(2);
        break;
    case Game::Label::T_LANCE:
        m_pWeapons->SetLeftOffsetCols(0);
        break;
    case Game::Label::T_TORCH:
        m_pWeapons->SetLeftOffsetCols(1);
        break;
    }
    m_pWeapons->SetPosition(pos);
    m_pWeapons->UpdateSourceRect();
    m_pWeapons->Draw();
}

void HUD::DrawFrame() const
{
    m_pFrame->Draw();
}
