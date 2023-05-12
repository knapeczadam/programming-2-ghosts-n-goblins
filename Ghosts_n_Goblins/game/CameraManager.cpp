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
    static const auto isOutOfWindow{
        [&](const GameObject* pGameObject) { return m_pCamera->IsOutOfWindow(pGameObject); }
    };
    static const auto isAwake{[&](const IEnemy* pEnemy) { return pEnemy->IsAwake(); }};
    static const auto deactivate{
        [&](GameObject* pGameObject)
        {
            pGameObject->SetVisible(false);
            pGameObject->SetActive(false);
        }
    };

    std::ranges::for_each(m_pGameController->m_pPlayerManager->GetThrowables() | std::views::filter(isOutOfWindow),
                          deactivate);
    std::ranges::for_each(m_pGameController->m_pEnemyManager->GetThrowables() | std::views::filter(isOutOfWindow),
                          deactivate);

    for (GameObject* pGameObject : m_pGameController->m_pEnemyManager->GetEnemies())
    {
        IEnemy* pEnemy{dynamic_cast<IEnemy*>(pGameObject)};
        if (pEnemy)
        {
            switch (pEnemy->GetLabel())
            {
            case Game::Label::C_GREEN_MONSTER:
                pEnemy->SetAwake(false);
                break;
            }
        }
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