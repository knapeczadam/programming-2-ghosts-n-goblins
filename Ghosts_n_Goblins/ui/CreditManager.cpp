#include "pch.h"
#include "CreditManager.h"

#include "ScoreManager.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/GameController.h"
#include "game/InputManager.h"

CreditManager::CreditManager(GameController* pGameController)
    : UI{Game::Label::U_CREDIT_MANAGER, pGameController}
    , m_Credits{}
    , m_MaxCredits{5}
{
}

void CreditManager::Update(float elapsedSec)
{
    if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_SELECT) and not m_pGameController->m_pInputManager->IsTriggered(Game::Label::I_SELECT))
    {
        m_pGameController->m_pInputManager->SetTriggered(Game::Label::I_SELECT, true);
        if (m_Credits < m_MaxCredits)
        {
            ++m_Credits;
        }
    }
}

void CreditManager::DrawCredit() const
{
    Point2f pos{146.0f, 0.0f};
    DrawNumber(pos, m_Credits, ScoreManager::Color::DARK_TAN);
}

int CreditManager::GetCredits() const
{
    return m_Credits;
}
