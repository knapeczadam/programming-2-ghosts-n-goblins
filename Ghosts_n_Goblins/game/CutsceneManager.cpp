#include "pch.h"
#include "CutsceneManager.h"

#include "GameController.h"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"

CutsceneManager::CutsceneManager(GameController* gameController)
    : IManager(gameController)
    , m_Intervals{}
    , m_State{Game::Label::N_01}
    , m_ArmorPickedUp{false}
{
    Initialize();
}

CutsceneManager::~CutsceneManager()
{
    CleanUp();
}

void CutsceneManager::Initialize(bool fromCheckpoint)
{
    m_Intervals.push({Game::Label::N_01, 1.00f});
    m_Intervals.push({Game::Label::N_02, 1.00f});
    m_Intervals.push({Game::Label::N_03, 0.10f});
    m_Intervals.push({Game::Label::N_04, 0.10f});
    m_Intervals.push({Game::Label::N_05, 0.10f});
    
    m_Intervals.push({Game::Label::N_06, 0.02f});
    m_Intervals.push({Game::Label::N_07, 0.02f});
    m_Intervals.push({Game::Label::N_06, 0.02f});
    m_Intervals.push({Game::Label::N_07, 0.02f});
    m_Intervals.push({Game::Label::N_06, 0.02f});
    m_Intervals.push({Game::Label::N_07, 0.02f});
    m_Intervals.push({Game::Label::N_06, 0.02f});
    m_Intervals.push({Game::Label::N_07, 0.02f});
    m_Intervals.push({Game::Label::N_06, 0.02f});
    m_Intervals.push({Game::Label::N_07, 0.02f});
    m_Intervals.push({Game::Label::N_06, 0.02f});

    m_Intervals.push({Game::Label::N_07, 0.05f}); // starts flying
    m_Intervals.push({Game::Label::N_08, 0.05f});
    m_Intervals.push({Game::Label::N_09, 0.05f});
    m_Intervals.push({Game::Label::N_08, 0.05f});
    m_Intervals.push({Game::Label::N_07, 0.05f}); // 2nd iteration
    m_Intervals.push({Game::Label::N_08, 0.05f});
    m_Intervals.push({Game::Label::N_09, 0.05f});
    m_Intervals.push({Game::Label::N_08, 0.05f});
    m_Intervals.push({Game::Label::N_07, 0.05f}); // flying down
    m_Intervals.push({Game::Label::N_10, 0.02f});
    m_Intervals.push({Game::Label::N_11, 0.02f});
    m_Intervals.push({Game::Label::N_12, 0.02f});
    m_Intervals.push({Game::Label::N_13, 0.02f});
    m_Intervals.push({Game::Label::N_14, 0.02f});
    m_Intervals.push({Game::Label::N_15, 0.02f});
    m_Intervals.push({Game::Label::N_16, 0.02f});
    m_Intervals.push({Game::Label::N_17, 0.02f});
    m_Intervals.push({Game::Label::N_18, 0.01f});
    m_Intervals.push({Game::Label::N_19, 0.01f});
    m_Intervals.push({Game::Label::N_20, 0.01f});
    m_Intervals.push({Game::Label::N_21, 0.01f});
    m_Intervals.push({Game::Label::N_22, 0.01f});
    m_Intervals.push({Game::Label::N_23, 0.01f});
    m_Intervals.push({Game::Label::N_24, 0.01f});
    m_Intervals.push({Game::Label::N_25, 0.01f});
    m_Intervals.push({Game::Label::N_26, 0.01f});
    m_Intervals.push({Game::Label::N_27, 0.01f});
    m_Intervals.push({Game::Label::N_28, 0.01f});
    m_Intervals.push({Game::Label::N_29, 0.01f});
    m_Intervals.push({Game::Label::N_30, 0.01f});
    m_Intervals.push({Game::Label::N_31, 0.01f});
    m_Intervals.push({Game::Label::N_32, 0.01f});
    m_Intervals.push({Game::Label::N_33, 0.01f});
    m_Intervals.push({Game::Label::N_34, 0.01f});
    m_Intervals.push({Game::Label::N_35, 0.01f});
    m_Intervals.push({Game::Label::N_36, 0.01f});
    m_Intervals.push({Game::Label::N_37, 0.01f});
    m_Intervals.push({Game::Label::N_38, 0.01f});
    m_Intervals.push({Game::Label::N_39, 0.01f});
    m_Intervals.push({Game::Label::N_40, 0.01f});
    m_Intervals.push({Game::Label::N_41, 0.01f});
    m_Intervals.push({Game::Label::N_42, 0.01f});
    m_Intervals.push({Game::Label::N_43, 0.01f});
    m_Intervals.push({Game::Label::N_44, 0.01f});
    m_Intervals.push({Game::Label::N_45, 0.01f});
    m_Intervals.push({Game::Label::N_46, 0.02f}); // 1st iteration
    m_Intervals.push({Game::Label::N_47, 0.02f});
    m_Intervals.push({Game::Label::N_46, 0.02f}); // 2nd iteration
    m_Intervals.push({Game::Label::N_47, 0.02f});
    m_Intervals.push({Game::Label::N_46, 0.02f}); // 3rd iteration
    m_Intervals.push({Game::Label::N_47, 0.02f});
    m_Intervals.push({Game::Label::N_46, 0.80f});
    m_Intervals.push({Game::Label::N_48, 0.01f});
    m_Intervals.push({Game::Label::N_49, 0.01f});
    m_Intervals.push({Game::Label::N_50, 0.01f});
    m_Intervals.push({Game::Label::N_51, 0.01f});
    m_Intervals.push({Game::Label::N_52, 0.01f});
    m_Intervals.push({Game::Label::N_53, 0.01f});
    m_Intervals.push({Game::Label::N_54, 0.01f});
    m_Intervals.push({Game::Label::N_55, 0.01f});
    m_Intervals.push({Game::Label::N_56, 0.01f});
    m_Intervals.push({Game::Label::N_57, 0.01f});
    m_Intervals.push({Game::Label::N_58, 0.01f});
    m_Intervals.push({Game::Label::N_59, 0.01f});
    m_Intervals.push({Game::Label::N_60, 0.01f});
    m_Intervals.push({Game::Label::N_61, 0.01f});
    m_Intervals.push({Game::Label::N_62, 0.01f});
    m_Intervals.push({Game::Label::N_63, 0.01f});
    m_Intervals.push({Game::Label::N_64, 0.01f});
    m_Intervals.push({Game::Label::N_65, 0.60f});
    m_Intervals.push({Game::Label::N_66, 0.01f});
    m_Intervals.push({Game::Label::N_67, 0.01f});
    m_Intervals.push({Game::Label::N_68, 0.01f});
    m_Intervals.push({Game::Label::N_69, 0.01f});
    m_Intervals.push({Game::Label::N_70, 0.01f});
    m_Intervals.push({Game::Label::N_71, 0.01f});
    m_Intervals.push({Game::Label::N_72, 0.01f});
    m_Intervals.push({Game::Label::N_73, 0.01f});
    m_Intervals.push({Game::Label::N_74, 0.01f});
    m_Intervals.push({Game::Label::N_75, 0.01f});
    m_Intervals.push({Game::Label::N_76, 0.01f});
    m_Intervals.push({Game::Label::N_77, 0.01f});
    m_Intervals.push({Game::Label::N_78, 0.01f});
    m_Intervals.push({Game::Label::N_79, 0.01f});
    m_Intervals.push({Game::Label::N_80, 0.01f});
    m_Intervals.push({Game::Label::N_81, 0.01f});
    m_Intervals.push({Game::Label::N_82, 0.01f});
    m_Intervals.push({Game::Label::N_83, 0.01f});
    m_Intervals.push({Game::Label::N_84, 0.01f});
    m_Intervals.push({Game::Label::N_85, 0.01f});
    m_Intervals.push({Game::Label::N_86, 0.01f});
    m_Intervals.push({Game::Label::N_87, 0.01f});
    m_Intervals.push({Game::Label::N_88, 0.01f});
    m_Intervals.push({Game::Label::N_89, 0.01f});
    m_Intervals.push({Game::Label::N_90, 0.01f});
    m_Intervals.push({Game::Label::N_91, 0.01f});
    m_Intervals.push({Game::Label::N_92, 0.01f});
    m_Intervals.push({Game::Label::N_93, 0.01f});
    m_Intervals.push({Game::Label::N_94, 0.01f});
    m_Intervals.push({Game::Label::N_95, 0.01f});
    m_Intervals.push({Game::Label::N_96, 0.01f});
    m_Intervals.push({Game::Label::N_97, 0.01f});
    m_Intervals.push({Game::Label::N_98, 0.01f});
    m_Intervals.push({Game::Label::N_99, 0.01f});
    m_Intervals.push({Game::Label::N_100, 0.01f});
    m_Intervals.push({Game::Label::N_101, 0.01f});
    m_Intervals.push({Game::Label::N_102, 0.01f});
    m_Intervals.push({Game::Label::N_103, 1.70f});
    m_Intervals.push({Game::Label::N_104, 0.01f});
    m_Intervals.push({Game::Label::N_END, 0.0f});
}

void CutsceneManager::CleanUp()
{
    std::queue<std::pair<Game::Label, float>> empty;
    std::swap(m_Intervals, empty);
    m_ArmorPickedUp = false;
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
    if (m_State == Game::Label::N_65 and not m_ArmorPickedUp)
    {
        m_ArmorPickedUp = true;
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ARMOR_PICKUP);    
    }
    if (IsTimerFinished())
    {
        m_Intervals.pop();
    }
}

void CutsceneManager::Reset(bool fromCheckpoint)
{
    CleanUp();
    Initialize();
    m_State = Game::Label::N_01;
}

Game::Label CutsceneManager::GetState() const
{
    return m_State;
}
