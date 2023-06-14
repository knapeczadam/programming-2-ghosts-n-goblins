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
    , m_pFrame{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_FRAME)}
    , m_pLife{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_LIFE)}
    , m_pNumbers(pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_NUMBERS))
    , m_pTextTime(pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_TIME))
    , m_pWeapons(pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_WEAPONS))
    , m_FirstDigit{}
    , m_SecondDigit{}
    , m_ThirdDigit{}

{
    m_pFrame->SetPosition(Point2f{m_pGameController->m_ViewPort.width / 2 - m_pFrame->GetScaledClipWidth() / 2, 0.0f});
    m_pTextTime->SetPosition(Point2f{32.0f, 400.0f});
}

void HUD::Draw() const
{
    DrawLives();
    DrawPlayerScore();
    DrawTopScore();
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

void HUD::SetDigits(const Time& time)
{
    m_FirstDigit = time.firstDigit;
    m_SecondDigit = time.secondDigit;
    m_ThirdDigit = time.thirdDigit;
}

void HUD::DrawLives() const
{
    for (int idx{}; idx < m_pGameController->m_pPlayerManager->GetPlayer()->GetLives() - 1; ++idx)
    {
        m_pLife->SetPosition(Point2f{idx * m_pLife->GetScaledClipWidth(), 0});
        m_pLife->Draw();
    }
}

void HUD::DrawRemainingTime() const
{
    Point2f pos{80, m_pGameController->m_ViewPort.height - m_pNumbers->GetScaledClipHeight() * 4};
    DrawNumber(pos, m_FirstDigit, Color::SKY_BLUE);
    DrawNumber(pos, m_SecondDigit, Color::SKY_BLUE);
    DrawNumber(pos, -1, Color::SKY_BLUE);
    DrawNumber(pos, m_ThirdDigit, Color::SKY_BLUE);
}

void HUD::DrawTextTime() const
{
    m_pTextTime->Draw();
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
