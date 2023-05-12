#include "pch.h"
#include "CutsceneManager.h"

#include "GameController.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"

CutsceneManager::CutsceneManager(GameController* gameController)
    : IManager(gameController)
    , m_Intervals{}
    , m_State{Game::Label::N_01}
{
    Initialize();
}

void CutsceneManager::Initialize()
{
    m_Intervals.push({Game::Label::N_01, 1.03f});
    m_Intervals.push({Game::Label::N_02, 1.02f});
    m_Intervals.push({Game::Label::N_03, 0.09f});
    m_Intervals.push({Game::Label::N_04, 0.22f});
    m_Intervals.push({Game::Label::N_05, 0.01f});
    m_Intervals.push({Game::Label::N_06, 0.4f});
    m_Intervals.push({Game::Label::N_05, 0.01f});
    m_Intervals.push({Game::Label::N_06, 0.4f});
    m_Intervals.push({Game::Label::N_05, 0.01f});
    m_Intervals.push({Game::Label::N_06, 0.3f});
    m_Intervals.push({Game::Label::N_05, 0.01f});
    m_Intervals.push({Game::Label::N_06, 0.01f});
    m_Intervals.push({Game::Label::N_05, 0.03f});
    m_Intervals.push({Game::Label::N_06, 0.01f});
    m_Intervals.push({Game::Label::N_05, 0.02f});
    
    m_Intervals.push({Game::Label::N_07, 0.07f}); // starts flying
    m_Intervals.push({Game::Label::N_08, 0.05f});
    m_Intervals.push({Game::Label::N_09, 0.05f});
    m_Intervals.push({Game::Label::N_08, 0.07f});
    m_Intervals.push({Game::Label::N_07, 0.05f}); // 2nd iteration
    m_Intervals.push({Game::Label::N_08, 0.03f});
    m_Intervals.push({Game::Label::N_10, 0.04f});
    m_Intervals.push({Game::Label::N_11, 0.04f});
    m_Intervals.push({Game::Label::N_12, 0.02f});
    m_Intervals.push({Game::Label::N_13, 0.03f});
    m_Intervals.push({Game::Label::N_14, 0.04f});
    m_Intervals.push({Game::Label::N_15, 0.04f});
    m_Intervals.push({Game::Label::N_16, 0.02f});
    m_Intervals.push({Game::Label::N_17, 0.05f});
    m_Intervals.push({Game::Label::N_18, 0.01f});
    m_Intervals.push({Game::Label::N_19, 0.01f});
    m_Intervals.push({Game::Label::N_20, 0.01f});
    m_Intervals.push({Game::Label::N_19, 0.01f});
    m_Intervals.push({Game::Label::N_20, 0.01f});
    m_Intervals.push({Game::Label::N_19, 0.01f});
    m_Intervals.push({Game::Label::N_20, 0.01f});
    m_Intervals.push({Game::Label::N_19, 0.10f});
    m_Intervals.push({Game::Label::N_21, 0.04f});
    m_Intervals.push({Game::Label::N_22, 0.0f});
    m_Intervals.push({Game::Label::N_23, 0.01f});
    m_Intervals.push({Game::Label::N_24, 0.21f});
    m_Intervals.push({Game::Label::N_25, 0.25f});
    m_Intervals.push({Game::Label::N_26, 0.04f});
    m_Intervals.push({Game::Label::N_27, 0.03f});
    m_Intervals.push({Game::Label::N_28, 0.04f});
    m_Intervals.push({Game::Label::N_29, 0.04f});
    m_Intervals.push({Game::Label::N_30, 0.03f});
    m_Intervals.push({Game::Label::N_31, 0.02f});
    m_Intervals.push({Game::Label::N_32, 0.16f});
    m_Intervals.push({Game::Label::N_33, 0.19f});
    m_Intervals.push({Game::Label::N_END, 0.0f});
}

void CutsceneManager::DrawIntro() const
{
    if (m_State == Game::Label::N_END) return;
    m_pGameController->m_pSpriteFactory->CreateSprite(m_State)->Draw();
}

void CutsceneManager::Update(float elapsedSec)
{
    StartTimer(m_Intervals.front().second);
    m_State = m_Intervals.front().first;
    if (m_State == Game::Label::N_END)
    {
        return;
    }
    if (IsTimerFinished())
    {
        m_Intervals.pop();
    }
}

void CutsceneManager::Reset(bool fromCheckpoint)
{
    m_State = Game::Label::N_01;
}

Game::Label CutsceneManager::GetState() const
{
    return m_State;
}
