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
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetGreenMonsters()  | std::views::filter(isOutOfWindow) | std::views::transform(toEnemy), sleep);
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetZombies() | std::views::filter(isOutOfWindow), deactivate);
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetFlyingKnights() | std::views::filter(isOutOfWindow), deactivate);
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetWoodyPigs() | std::views::filter(isOutOfWindow), deactivate);
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetCrows() | std::views::filter(isAwake) |  std::views::filter(isOutOfWindow), deactivate);
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