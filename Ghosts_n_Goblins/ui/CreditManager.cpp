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
    m_pSprite = pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_CREDIT);
    m_pSprite->SetPosition(Point2f{32.0f, 0.0f});
}

void CreditManager::Draw() const
{
    m_pSprite->Draw();
    m_pGameController->m_pScoreManager->DrawNumber(Point2f{146.0f, 0.0f}, m_Credits, ScoreManager::Color::DARK_TAN);
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
