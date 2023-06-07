#include "pch.h"
#include "CreditManager.h"

#include "ScoreManager.h"
#include "engine/SoundManager.h"
#include "game/GameController.h"
#include "game/InputManager.h"

CreditManager::CreditManager(GameController* pGameController)
    : UI{Game::Label::U_CREDIT_MANAGER, pGameController}
    , m_Credits{}
    , m_MaxCredits{1}
    , m_Inserted{false}
{
}

void CreditManager::Update(float elapsedSec)
{
    if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_INSERT) and not m_pGameController->m_pInputManager
        ->IsTriggered(Game::Label::I_INSERT))
    {
        m_pGameController->m_pInputManager->SetTriggered(Game::Label::I_INSERT, true);
        if (m_Credits < m_MaxCredits)
        {
            ++m_Credits;
        }
    }
}

void CreditManager::DrawCredits() const
{
    Point2f pos{146.0f, 0.0f};
    DrawNumber(pos, m_Credits, ScoreManager::Color::DARK_TAN);
}

int CreditManager::GetCredits() const
{
    return m_Credits;
}

void CreditManager::Reset(bool fromCheckpoint)
{
    m_Credits = 0;
    m_Inserted = false;
}

bool CreditManager::CreditInserted() const
{
    return m_Inserted;
}

void CreditManager::ActivateGame()
{
    m_Inserted = true;
}
