// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "HUD.h"
#include "characters/Player.h"
#include "engine/Sprite.h"

#include <iostream>

#include "engine/SoundManager.h"


HUD::HUD(Sprite* pSprite, Player* pPlayer, const Rectf& viewPort, SoundManager* pSoundManager)
    : UI{Game::Label::U_HUD, pSprite, viewPort, pSoundManager}
      , m_pPlayer{pPlayer}
      , m_FirstDigit{}
      , m_SecondDigit{}
      , m_ThirdDigit{}
{
}

void HUD::Draw()
{
    DrawLives();
    DrawPlayerScore();
    DrawHighScore();
    DrawTopScore();
    DrawTime();
    DrawRemainingTime();
    DrawFrame();
    DrawWeapon();
    DrawPlayer1();
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

void HUD::DrawLives()
{
    m_pSprite->SetTopOffsetRows(3);
    m_pSprite->UpdateSourceRect();
    for (int idx{}; idx < m_pPlayer->GetLives() - 1; ++idx)
    {
        m_pSprite->SetPosition(Point2f{idx * m_pSprite->GetScaledClipWidth(), 0});
        m_pSprite->Draw();
    }
    ResetSprite();
}

void HUD::DrawPlayerScore()
{
    m_pSprite->SetClipWidth(8);
    m_pSprite->SetClipHeight(8);
    const int playerScore{m_pPlayer->GetScore()};
    Point2f pos{128.0f, m_ViewPort.height - m_pSprite->GetScaledClipHeight() * 2};
    const float offset{m_pSprite->GetScaledClipWidth()};
    if (playerScore == 0)
    {
        m_pSprite->SetTopOffsetRows(1);
        m_pSprite->SetLeftOffsetCols(0);
        m_pSprite->SetPosition(pos);
        m_pSprite->UpdateSourceRect();
        m_pSprite->UpdateDestinationRect();
        m_pSprite->Draw();
    }
    for (int score = playerScore; score > 0; score /= 10)
    {
        const int digit{score % 10};
        m_pSprite->SetTopOffsetRows(1);
        m_pSprite->SetLeftOffsetCols(digit);
        m_pSprite->SetPosition(pos);
        m_pSprite->UpdateSourceRect();
        m_pSprite->UpdateDestinationRect();
        m_pSprite->Draw();
        pos.x -= offset;
    }
    ResetSprite();
}

void HUD::DrawHighScore()
{
    m_pSprite->SetClipWidth(8);
    m_pSprite->SetClipHeight(8);
    const int testHighScore{10000};
    Point2f pos{304.0f, m_ViewPort.height - m_pSprite->GetScaledClipHeight() * 2};
    const float offset{m_pSprite->GetScaledClipWidth()};
    for (int score = testHighScore; score > 0; score /= 10)
    {
        const int digit{score % 10};
        m_pSprite->SetTopOffsetRows(1);
        m_pSprite->SetLeftOffsetCols(digit);
        m_pSprite->SetPosition(pos);
        m_pSprite->UpdateSourceRect();
        m_pSprite->UpdateDestinationRect();
        m_pSprite->Draw();
        pos.x -= offset;
    }
    ResetSprite();
}

void HUD::DrawTopScore()
{
    m_pSprite->SetClipHeight(8);
    m_pSprite->SetClipWidth(80);
    m_pSprite->SetTopOffsetRows(12);
    m_pSprite->SetLeftOffsetCols(1);
    m_pSprite->SetPosition(Point2f{176.0f, m_ViewPort.height - m_pSprite->GetScaledClipHeight()});
    m_pSprite->UpdateSourceRect();
    m_pSprite->UpdateDestinationRect();
    m_pSprite->Draw();
    ResetSprite();
}

void HUD::DrawTime()
{
    m_pSprite->SetClipHeight(8);
    m_pSprite->SetClipWidth(32);
    m_pSprite->SetTopOffsetRows(13);
    m_pSprite->SetPosition(Point2f{32.0f, m_ViewPort.height - m_pSprite->GetScaledClipHeight() * 3});
    m_pSprite->UpdateSourceRect();
    m_pSprite->UpdateDestinationRect();
    m_pSprite->Draw();
    ResetSprite();
}

void HUD::DrawRemainingTime()
{
    m_pSprite->SetClipWidth(8);
    m_pSprite->SetClipHeight(8);
    Point2f pos{32, m_ViewPort.height - m_pSprite->GetScaledClipHeight() * 4};
    const float offset{m_pSprite->GetScaledClipWidth()};
    // FIRST DIGIT
    m_pSprite->SetLeftOffsetCols(m_FirstDigit);
    m_pSprite->SetPosition(pos);
    m_pSprite->UpdateSourceRect();
    m_pSprite->UpdateDestinationRect();
    m_pSprite->Draw();

    // COLON
    pos.x += offset;
    m_pSprite->SetLeftOffsetCols(10);
    m_pSprite->SetPosition(pos);
    m_pSprite->UpdateSourceRect();
    m_pSprite->UpdateDestinationRect();
    m_pSprite->Draw();

    // SECOND DIGIT
    pos.x += offset;
    m_pSprite->SetLeftOffsetCols(m_SecondDigit);
    m_pSprite->SetPosition(pos);
    m_pSprite->UpdateSourceRect();
    m_pSprite->UpdateDestinationRect();
    m_pSprite->Draw();

    // THIRD DIGIT
    pos.x += offset;
    m_pSprite->SetLeftOffsetCols(m_ThirdDigit);
    m_pSprite->SetPosition(pos);
    m_pSprite->UpdateSourceRect();
    m_pSprite->UpdateDestinationRect();
    m_pSprite->Draw();

    ResetSprite();
}

void HUD::DrawFrame() const
{
    m_pSprite->SetClipWidth(m_pSprite->GetClipWidth() * 2);
    m_pSprite->SetClipHeight(m_pSprite->GetClipHeight() * 2);
    m_pSprite->SetTopOffsetRows(2);
    Point2f pos;
    pos.x = m_ViewPort.width / 2 - m_pSprite->GetScaledClipWidth() / 2;
    m_pSprite->SetPosition(pos);
    m_pSprite->UpdateSourceRect();
    m_pSprite->UpdateDestinationRect();
    m_pSprite->Draw();
    ResetSprite();
}

void HUD::DrawWeapon() const
{
    const Point2f offset{0.0f, 20.0f};
    Point2f pos;
    pos.x = m_ViewPort.width / 2 - m_pSprite->GetScaledClipWidth() / 2;
    pos.y = m_pSprite->GetScaledClipHeight() / 2;

    m_pSprite->SetTopOffsetRows(2);
    switch (m_pPlayer->GetWeapon())
    {
    case Game::Label::W_DAGGER:
        m_pSprite->SetLeftOffsetCols(2);
        break;
    case Game::Label::W_LANCE:
        break;
    case Game::Label::W_TORCH:
        m_pSprite->SetLeftOffsetCols(1);
        break;
    }
    m_pSprite->SetPosition(pos);
    m_pSprite->UpdateSourceRect();
    m_pSprite->Draw();
    ResetSprite();
}

void HUD::DrawPlayer1() const
{
    m_pSprite->SetClipHeight(8);
    m_pSprite->SetClipWidth(64);
    m_pSprite->SetTopOffsetRows(12);
    m_pSprite->SetPosition(Point2f{16.0f, m_ViewPort.height - m_pSprite->GetScaledClipHeight()});
    m_pSprite->UpdateSourceRect();
    m_pSprite->UpdateDestinationRect();
    m_pSprite->Draw();
    ResetSprite();
}

void HUD::ResetSprite() const
{
    m_pSprite->ResetOriginalClipSize();
    m_pSprite->SetTopOffsetRows(0);
    m_pSprite->SetLeftOffsetCols(0);
    m_pSprite->SetSubCols(0);
    m_pSprite->SetSubRows(0);
    m_pSprite->UpdateSourceRect();
    m_pSprite->UpdateDestinationRect();
}
