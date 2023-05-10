#include "pch.h"
#include "BootManager.h"

#include "GameController.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"

BootManager::BootManager(GameController* pGameController)
    : IManager{pGameController}
    , m_Intervals{}
    , m_State{Game::Label::B_01}
{
    pGameController->m_pBootManager = this;
    Initialize();
}

void BootManager::Initialize()
{
    m_Intervals.push({Game::Label::B_01, 1.16f});
    m_Intervals.push({Game::Label::B_BLACK, 0.192f});
    m_Intervals.push({Game::Label::B_02, 0.09613f});
    m_Intervals.push({Game::Label::B_BLACK, 0.0961f});
    m_Intervals.push({Game::Label::B_03, 0.08f});
    m_Intervals.push({Game::Label::B_BLACK, 0.064f});
    m_Intervals.push({Game::Label::B_04, 0.0961f});
    m_Intervals.push({Game::Label::B_BLACK, 0.08f});
    m_Intervals.push({Game::Label::B_05, 0.016f});
    m_Intervals.push({Game::Label::B_06, 0.064f});
    m_Intervals.push({Game::Label::B_BLACK, 0.08f});
    m_Intervals.push({Game::Label::B_07, 0.07956f});
    m_Intervals.push({Game::Label::B_BLACK, 0.38445f});
    m_Intervals.push({Game::Label::B_08, 0.03201f});
    m_Intervals.push({Game::Label::B_09, 0.01f});
    m_Intervals.push({Game::Label::B_10, 0.016f});
    m_Intervals.push({Game::Label::B_11, 0.016f});
    m_Intervals.push({Game::Label::B_12, 0.016f});
    m_Intervals.push({Game::Label::B_13, 0.016f});
    m_Intervals.push({Game::Label::B_14, 0.016f});
    m_Intervals.push({Game::Label::B_15, 0.032f});
    m_Intervals.push({Game::Label::B_BLACK, 0.016f});
    m_Intervals.push({Game::Label::B_09, 0.016f});
    m_Intervals.push({Game::Label::B_BLACK, 0.16f});
    m_Intervals.push({Game::Label::B_16, 0.096f});
    m_Intervals.push({Game::Label::B_17, 0.14401f});
    m_Intervals.push({Game::Label::B_18, 1.016f});
    m_Intervals.push({Game::Label::B_19, 0.048f});
    m_Intervals.push({Game::Label::B_20, 0.032f}); // edit
    m_Intervals.push({Game::Label::B_21, 3.0f}); // blue
    m_Intervals.push({Game::Label::B_22, 0.016f}); // blue
    m_Intervals.push({Game::Label::B_23, 4.016f}); // blue
    m_Intervals.push({Game::Label::B_24, 5.0f}); // best ranking
    m_Intervals.push({Game::Label::B_25, 0.033f});
    m_Intervals.push({Game::Label::B_END, 0.0f});
}

void BootManager::Draw() const
{
    if (m_State == Game::Label::B_END) return;
    m_pGameController->m_pSpriteFactory->CreateSprite(m_State)->Draw();
}

void BootManager::Update(float elapsedSec)
{
    StartTimer(m_Intervals.front().second);
    m_State = m_Intervals.front().first;
    if (m_State == Game::Label::B_END)
    {
        return;
    }
    if (IsTimerFinished())
    {
        m_Intervals.pop();
    }
}

Game::Label BootManager::GetState() const
{
    return m_State;
}

void BootManager::Reset()
{
}
