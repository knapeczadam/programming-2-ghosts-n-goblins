#include "pch.h"
#include "Menu.h"

#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/GameController.h"
#include "game/InputManager.h"

#include <iostream>

Menu::Menu(GameController* pGameController)
    : UI{Game::Label::U_MENU, pGameController}
      , m_pBlueChar{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_ABC)}
      , m_pRedChar{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_ABC)}
      , m_BlueCharPos{56.0f, 234.0f}
      , m_RedCharPos{56.0f, 362.0f}
      , m_NrRows{5}
      , m_NrCols{13}
      , m_Characters{}
      , m_RowIdx{m_NrRows - 1}
      , m_ColIdx{m_NrCols - 1}
      , m_Flicker{}
      , m_Initial{}
      , m_MaxLength{3}
{
    m_pBlueChar->SetPosition(m_BlueCharPos);
    InitCharacterLookup();
}

void Menu::Draw() const
{
    DrawAbc();
}

void Menu::DrawAbc() const
{
    m_pBlueChar->SetTopOffsetRows(0);
    m_pBlueChar->SetLeftOffsetCols(0);
    m_pBlueChar->SetClipWidth(m_pBlueChar->GetWidth());
    m_pBlueChar->SetClipHeight(m_pBlueChar->GetHeight() / 3);
    m_pBlueChar->UpdateSourceRect();
    m_pBlueChar->Draw();
    FlickerCharacter();
}

void Menu::InitCharacterLookup()
{
    m_Characters.insert(m_Characters.end(), {
                            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                            '!', '?', '&', ',', '.', '(', ')', '/', ':', '*', ' ', ' ', ' '
                        });
}

void Menu::FlickerCharacter() const
{
    m_pRedChar->SetTopOffsetRows(5 + m_RowIdx);
    m_pRedChar->SetLeftOffsetCols(m_ColIdx);
    m_pRedChar->UpdateSourceRect();
    if (m_Flicker)
    {
        m_pRedChar->Draw();
    }
}

char Menu::GetCharacter() const
{
    return m_Characters[m_RowIdx * m_NrCols + m_ColIdx];
}

void Menu::OnEnter()
{
    if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_START) and not m_pGameController->m_pInputManager->IsTriggered(Game::Label::I_START))
    {
        m_pGameController->m_pInputManager->SetTriggered(Game::Label::I_START, true);
        if (m_Initial.length() < m_MaxLength)
        {
            m_Initial += GetCharacter();
        }
        if (m_Initial.length() == m_MaxLength)
        {
            SaveInitial();
        }
    }
}

void Menu::SaveInitial()
{
    std::cout << m_Initial << std::endl;
    m_Initial.clear();
}

void Menu::Update(float elapsedSec)
{
    StartTimer(0.2f);
    if (IsTimerFinished())
    {
        m_Flicker = not m_Flicker;
    }

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
