#include "pch.h"
#include "CameraManager.h"

#include "Camera.h"
#include "EnemyManager.h"
#include "GameController.h"
#include "LevelManager.h"
#include "PlayerManager.h"
#include "level/Level.h"

#include <ranges>

#include "UIManager.h"
#include "characters/IEnemy.h"
#include "characters/Player.h"
#include "ui/Map.h"

class IEnemy;

CameraManager::CameraManager(GameController* pGameController)
    : IManager{pGameController}
    , m_pCamera{nullptr}
    , m_ShrinkSteps{750.0f}
    , m_ShrinkStepsCounter{1}
    , m_InitBoundaries{false}
{
    pGameController->m_pCameraManager = this;
    Initialize();
}

CameraManager::~CameraManager()
{
    CleanUp();
}

void CameraManager::Initialize(bool fromCheckpoint)
{
    m_pCamera = new Camera{m_pGameController};
    //m_pCamera->SetBoundaries(m_pGameController->m_pLevelManager->GetLevel()->GetBoundaries());
}

void CameraManager::CleanUp()
{
    delete m_pCamera;
}

void CameraManager::DoFrustumCulling()
{
    static const auto isOutOfWindow{[&](const GameObject* pGameObject) { return m_pCamera->IsOutOfWindow(pGameObject);}};
    static const auto isAwake{[](const GameObject* pEnemy) { return pEnemy->IsAwake(); }};
    static const auto sleep{[](GameObject* pEnemy) { pEnemy->SetAwake(false); }};
    static const auto toEnemy{[](GameObject* pGameObject) { return static_cast<IEnemy*>(pGameObject); }};
    static const auto deactivate{[](GameObject* pGameObject){pGameObject->SetVisible(false); pGameObject->SetActive(false);}};

    std::ranges::for_each(m_pGameController->m_pPlayerManager->GetThrowables() | std::views::filter(isOutOfWindow), deactivate);
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetThrowables() | std::views::filter(isOutOfWindow), deactivate);
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetGreenMonsters() | std::views::filter(isOutOfWindow), sleep);
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetZombies() | std::views::filter(isOutOfWindow), deactivate);
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetFlyingKnights() | std::views::filter(isOutOfWindow), deactivate);
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetWoodyPigs() | std::views::filter(isOutOfWindow), deactivate);
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetCrows() | std::views::filter(isAwake) |  std::views::filter(isOutOfWindow), deactivate);
}

void CameraManager::ShrinkBoundaries()
{
    const float playerX{m_pGameController->m_pPlayerManager->GetPlayer()->GetPosition<Point2f>().x};
    const float offset{256.0f};
    if (playerX - offset >= m_ShrinkSteps * m_ShrinkStepsCounter)
    {
        Rectf boundaries{m_pCamera->GetBoundaries()};
        boundaries.left = m_ShrinkSteps * m_ShrinkStepsCounter++;
        m_pCamera->SetBoundaries(boundaries);
    }
}

void CameraManager::Transform(Game::Label label)
{
    switch (label)
    {
    case Game::Label::C_ARTHUR:
        m_pCamera->Transform(m_pGameController->m_pPlayerManager->GetPlayer());
        break;
    case Game::Label::D_DUMMY:
        m_pCamera->Transform(m_pGameController->m_pUIManager->m_pMap->GetDummy());
        break;
    }
}

Camera* CameraManager::GetCamera() const
{
    return m_pCamera;
}

void CameraManager::Update(float elapsedSec)
{
    if (not m_InitBoundaries)
    {
        m_pCamera->SetBoundaries(m_pGameController->m_pLevelManager->GetLevel()->GetBoundaries());
        m_InitBoundaries = true;
    }
    StartTimer(1.0f);
    if (IsTimerFinished())
    {
        ShrinkBoundaries();
    }
}

void CameraManager::Reset(bool fromCheckpoint)
{
    m_InitBoundaries = false;
    m_ShrinkStepsCounter = 1;
    CleanUp();
    Initialize();
    ResetTimer();
}
