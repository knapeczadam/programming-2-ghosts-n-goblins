#include "pch.h"
#include "InitialSaver.h"

#include "InitialDrawer.h"
#include "ScoreManager.h"
#include "characters/Player.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/GameController.h"
#include "game/InputManager.h"
#include "game/PlayerManager.h"
#include "game/UIManager.h"

InitialSaver::InitialSaver(GameController* pGameController)
    : UI{Game::Label::U_MENU, pGameController}
      , m_pBlueChar{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_ABC)}
      , m_pRedChar{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_ABC)}
      , m_pTextInitial{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_INITIAL)}
      , m_BlueCharPos{56.0f, 234.0f}
      , m_RedCharPos{56.0f, 362.0f}
      , m_TextInitialPos{132.0f, 64.0f}
      , m_NrRows{5}
      , m_NrCols{13}
      , m_RowIdx{m_NrRows - 1}
      , m_ColIdx{m_NrCols - 1}
      , m_Initial{}
      , m_MaxLength{3}
{
    m_Blinking = true;
    m_BlinkingTime = 0.4f;
    m_pBlueChar->SetPosition(m_BlueCharPos);
    m_pTextInitial->SetPosition(m_TextInitialPos);
}

void InitialSaver::Draw() const
{
    DrawAbc();
    DrawInitial();
    m_pTextInitial->Draw();
}

void InitialSaver::DrawAbc() const
{
    m_pBlueChar->SetTopOffsetRows(0);
    m_pBlueChar->SetLeftOffsetCols(0);
    m_pBlueChar->SetClipWidth(m_pBlueChar->GetWidth());
    m_pBlueChar->SetClipHeight(m_pBlueChar->GetHeight() / 3);
    m_pBlueChar->UpdateSourceRect();
    m_pBlueChar->Draw();
    FlickerCharacter();
}

void InitialSaver::DrawInitial() const
{
    m_pGameController->m_pUIManager->m_pInitialDrawer->DrawInitial(Point2f{256.0f, 64.0f}, m_Initial, InitialDrawer::Color::RED);
}

void InitialSaver::FlickerCharacter() const
{
    m_pRedChar->SetTopOffsetRows(5 + m_RowIdx);
    m_pRedChar->SetLeftOffsetCols(m_ColIdx);
    m_pRedChar->UpdateSourceRect();
    if (m_Blinking)
    {
        m_pRedChar->Draw();
    }
}

void InitialSaver::OnEnter()
{
    if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_START) and not m_pGameController->m_pInputManager->
        IsTriggered(Game::Label::I_START))
    {
        m_pGameController->m_pInputManager->SetTriggered(Game::Label::I_START, true);
        if (m_Initial.length() < m_MaxLength)
        {
            m_Initial += m_pGameController->m_pUIManager->m_pInitialDrawer->GetCharacter(m_RowIdx, m_ColIdx);
        }
        if (m_Initial.length() == m_MaxLength)
        {
            SaveInitial();
        }
    }
}

void InitialSaver::SaveInitial()
{
    m_pGameController->m_pUIManager->m_pScoreManager->SetScore(m_pGameController->m_pPlayerManager->GetPlayer()->GetScore(), m_Initial);
    m_pGameController->m_pUIManager->m_pScoreManager->SaveHighScores();
}

void InitialSaver::Update(float elapsedSec)
{
    UI::Update(elapsedSec);

    if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_UP) and not m_pGameController->m_pInputManager->
        IsTriggered(Game::Label::I_UP))
    {
        m_pGameController->m_pInputManager->SetTriggered(Game::Label::I_UP, true);
        --m_RowIdx;
        if (m_RowIdx < 0)
        {
            m_RowIdx = m_NrRows - 1;
        }
    }
    else if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_DOWN) and not m_pGameController->
        m_pInputManager->IsTriggered(Game::Label::I_DOWN))
    {
        m_pGameController->m_pInputManager->SetTriggered(Game::Label::I_DOWN, true);
        m_RowIdx = (m_RowIdx + 1) % m_NrRows;
    }
    else if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_LEFT) and not m_pGameController->
        m_pInputManager->IsTriggered(Game::Label::I_LEFT))
    {
        m_pGameController->m_pInputManager->SetTriggered(Game::Label::I_LEFT, true);
        --m_ColIdx;
        if (m_ColIdx < 0)
        {
            m_ColIdx = m_NrCols - 1;
        }
    }
    else if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_RIGHT) and not m_pGameController->
        m_pInputManager->IsTriggered(Game::Label::I_RIGHT))
    {
        m_pGameController->m_pInputManager->SetTriggered(Game::Label::I_RIGHT, true);
        m_ColIdx = (m_ColIdx + 1) % m_NrCols;
    }

    Point2f pos;
    pos.x = m_RedCharPos.x + m_ColIdx * m_pRedChar->GetScaledClipWidth();
    pos.y = m_RedCharPos.y - m_RowIdx * m_pRedChar->GetScaledClipHeight();
    m_pRedChar->SetPosition(pos);
    m_pBlueChar->Update(elapsedSec);
    m_pRedChar->Update(elapsedSec);

    OnEnter();
}

void InitialSaver::Reset()
{
    m_Initial.clear();
    m_RowIdx = m_NrRows - 1;
    m_ColIdx = m_NrCols - 1;
}
