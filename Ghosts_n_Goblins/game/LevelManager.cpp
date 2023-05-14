#include "pch.h"
#include "LevelManager.h"

#include "GameController.h"
#include "Texture.h"
#include "engine/TextureManager.h"
#include "level/colliders/ArmorCollider.h"
#include "level/KillZone.h"
#include "level/Ladder.h"
#include "level/Level.h"
#include "level/Platform.h"
#include "level/Tombstone.h"
#include "level/Water.h"
#include "level/colliders/YashichiCollider.h"

#include <ranges>

#include "EnemyManager.h"
#include "level/Door.h"
#include "level/colliders/BonusCollider.h"
#include "level/colliders/BossCollider.h"
#include "level/colliders/CheckpointCollider.h"
#include "level/colliders/DoorCollider.h"
#include "level/colliders/EndCollider.h"
#include "level/colliders/KeyCollider.h"

LevelManager::LevelManager(GameController* pGameController)
    : IManager{pGameController}
      , m_Colliders{}
      , m_Ladders{}
      , m_Tombstones{}
      , m_Waters{}
      , m_pForeground{nullptr}
      , m_pKillZone{nullptr}
      , m_pLevel{nullptr}
      , m_pPlatform{nullptr}
    , m_CheckpointReached{false}
{
    m_pGameController->m_pLevelManager = this;
    Initialize();
}

LevelManager::~LevelManager()
{
    CleanUp();
}

void LevelManager::Initialize(bool fromCheckpoint)
{
    m_pPlatform = new Platform{Point2f{3295.0f, 28.0f}, m_pGameController};
    m_pForeground = new GameObject{Game::Label::L_FOREGROUND, m_pGameController};
    m_pKillZone = new KillZone{
        m_pGameController->m_pTextureManager->GetTexture(Game::Label::L_LEVEL)->GetWidth(), 10.0f
    };
    m_pLevel = new Level{m_pGameController};

    InitLadders();
    InitTombstones();
    InitWaters();
    InitColliders(fromCheckpoint);
    InitDoor();
}

void LevelManager::CleanUp()
{
    auto deleteGameObject = [](const GameObject* pGameObject) { delete pGameObject; };
    std::ranges::for_each(m_Colliders, deleteGameObject);
    std::ranges::for_each(m_Ladders, deleteGameObject);
    std::ranges::for_each(m_Tombstones, deleteGameObject);
    std::ranges::for_each(m_Waters, deleteGameObject);
    m_Colliders.clear();
    m_Ladders.clear();
    m_Tombstones.clear();
    m_Waters.clear();

    delete m_pForeground;
    delete m_pKillZone;
    delete m_pLevel;
    delete m_pPlatform;
    delete m_pDoor;
}

void LevelManager::DrawColliders() const
{
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    std::ranges::for_each(m_Colliders, draw);
}

void LevelManager::DrawForeGround() const
{
    m_pForeground->Draw();
}

void LevelManager::DrawKillZone() const
{
    m_pKillZone->Draw();
}

void LevelManager::DrawLadders() const
{
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    std::ranges::for_each(m_Ladders , draw);
}

void LevelManager::DrawLevel() const
{
    m_pLevel->Draw();
}

void LevelManager::DrawPlatform() const
{
    m_pPlatform->Draw();
}

void LevelManager::DrawTombstones() const
{
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    std::ranges::for_each(m_Tombstones, draw);
}

void LevelManager::DrawWaters() const
{
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    std::ranges::for_each(m_Waters, draw);
}

void LevelManager::DrawDoor() const
{
    if (m_pDoor->IsVisible()) m_pDoor->Draw();
}

void LevelManager::Update(float elapsedSec)
{
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto update{[&](GameObject* pGameObject) { pGameObject->Update(elapsedSec); }};
    m_pLevel->Update(elapsedSec);
    m_pPlatform->Update(elapsedSec);
    m_pDoor->Update(elapsedSec);
    std::ranges::for_each(m_Colliders | std::views::filter(isActive), update);
    std::ranges::for_each(m_Ladders | std::views::filter(isActive), update);
    std::ranges::for_each(m_Tombstones | std::views::filter(isActive), update);
    std::ranges::for_each(m_Waters | std::views::filter(isActive), update);
    
}

void LevelManager::LateUpdate(float elapsedSec)
{
    static const auto lateUpdate{[&](GameObject* pGameObject) { pGameObject->LateUpdate(elapsedSec); }};
    std::ranges::for_each(m_Waters, lateUpdate);
    if (m_pDoor->IsActive()) m_pDoor->LateUpdate(elapsedSec);
}

void LevelManager::Reset(bool fromCheckpoint)
{
    CleanUp();
    Initialize(fromCheckpoint);
}

bool LevelManager::CheckpointReached()
{
    for (const auto& pCollider : m_Colliders)
    {
        if (pCollider->GetLabel() == Game::Label::L_CHECKPOINT)
        {
            m_CheckpointReached = not pCollider->IsActive();
        }
    }
    return m_CheckpointReached;
}

bool LevelManager::IsBossFight() const
{
    bool bossActive{false};
    for (GameObject* enemy : m_pGameController->m_pEnemyManager->GetEnemies())
    {
        if (enemy->GetLabel() == Game::Label::C_UNICORN)
        {
            bossActive = enemy->IsActive();
        }
    }
    
    for (GameObject* collider : m_Colliders)
    {
        if (collider->GetLabel() == Game::Label::L_BOSS and not collider->IsActive())
        {
            return bossActive;
        }
    }
    return false;
}

bool LevelManager::StageCleared() const
{
    for (GameObject* collider : m_Colliders)
    {
        if (collider->GetLabel() == Game::Label::L_KEY and not collider->IsActive())
        {
            return true;
        }
    }
    return false;
}

bool LevelManager::EndReached()
{
    for (GameObject* collider : m_Colliders)
    {
        if (collider->GetLabel() == Game::Label::L_END and not collider ->IsActive())
        {
            return true;
        }
    }
    return false;
}

void LevelManager::InitColliders(bool fromCheckpoint)
{
    const float bonusStart{6940.0f};
    const float bossStart{6364.0f};
    const float doorStart{6849.0f};
    const float keyStart{6575.0f};
    const float endStart{6992.0f};
    m_Colliders.insert(m_Colliders.end(), {
                                new ArmorCollider{Rectf{2868.0f, 140.0f, 30.0f, 30.0f}, m_pGameController},
                                new BonusCollider{Rectf{bonusStart, 0.0f, m_pGameController->m_pLevelManager->GetLevel()->GetBoundaries().width - bonusStart, m_pGameController->m_ViewPort.height}, m_pGameController},
                                new BossCollider{Rectf{bossStart, 0.0f, m_pGameController->m_pLevelManager->GetLevel()->GetBoundaries().width - bossStart, m_pGameController->m_ViewPort.height}, m_pGameController},
                                new DoorCollider{Rectf{doorStart, 0.0f, 30.0f, m_pGameController->m_ViewPort.height}, m_pGameController},
                                new EndCollider{Rectf{endStart, 0.0f, m_pGameController->m_pLevelManager->GetLevel()->GetBoundaries().width - endStart, m_pGameController->m_ViewPort.height}, m_pGameController},
                                new KeyCollider{Rectf{keyStart, 0.0f, m_pGameController->m_pLevelManager->GetLevel()->GetBoundaries().width - keyStart, m_pGameController->m_ViewPort.height}, m_pGameController},
                                new YashichiCollider{Rectf{5924.0f, 140.0f, 24.0f, 24.0f}, m_pGameController}
                            });
    GameObject* pCheckpoint{new CheckpointCollider{Rectf{3600.0f, 0.0f, 30.0f, m_pGameController->m_ViewPort.height}, m_pGameController}};
    if (fromCheckpoint)
    {
        pCheckpoint->SetActive(not m_CheckpointReached);
    }
    m_Colliders.push_back(pCheckpoint);
}

void LevelManager::InitLadders()
{
    m_Ladders.insert(m_Ladders.end(), {
                         new Ladder{Rectf{1424.0f, 62.0f, 32.0f, 158.0f}, m_pGameController},
                         new Ladder{Rectf{1808.0f, 62.0f, 32.0f, 158.0f}, m_pGameController},
                         new Ladder{Rectf{2128.0f, 62.0f, 32.0f, 158.0f}, m_pGameController},
                     });
}

void LevelManager::InitTombstones()
{
    // BOTTOM
    m_Tombstones.insert(m_Tombstones.end(), {
                            new Tombstone{Rectf{83.0f, 66.0f, 30.0f, 30.0f}, m_pGameController},
                            new Tombstone{Rectf{499.0f, 66.0f, 30.0f, 30.0f}, m_pGameController},
                            new Tombstone{Rectf{817.0f, 66.0f, 30.0f, 30.0f}, m_pGameController},
                            new Tombstone{Rectf{1044.0f, 66.0f, 30.0f, 30.0f}, m_pGameController},
                            new Tombstone{Rectf{1490.0f, 66.0f, 30.0f, 30.0f}, m_pGameController},
                            new Tombstone{Rectf{1903.0f, 66.0f, 30.0f, 30.0f}, m_pGameController},
                            new Tombstone{Rectf{2191.0f, 66.0f, 30.0f, 30.0f}, m_pGameController},
                            new Tombstone{Rectf{2516.0f, 66.0f, 30.0f, 30.0f}, m_pGameController},
                            new Tombstone{Rectf{3028.0f, 66.0f, 30.0f, 30.0f}, m_pGameController},

                        });

    // TOP
    m_Tombstones.insert(m_Tombstones.end(), {
                            new Tombstone{Rectf{1519.0f, 221.0f, 30.0f, 30.0f}, m_pGameController},
                            new Tombstone{Rectf{1716.0f, 221.0f, 30.0f, 30.0f}, m_pGameController},
                            new Tombstone{Rectf{1909.0f, 221.0f, 30.0f, 30.0f}, m_pGameController},
                        });
}

void LevelManager::InitWaters()
{
    m_Waters.insert(m_Waters.end(), {
                        new Water{Point2f{3295.0f, 0.0f}, m_pGameController},
                        new Water{Point2f{3903.0f, 0.0f}, 64.0f, m_pGameController},
                        new Water{Point2f{4031.0f, 0.0f}, 64.0f, m_pGameController},
                        new Water{Point2f{4927.0f, 0.0f}, 64.0f, m_pGameController},
                        new Water{Point2f{5566.0f, 0.0f}, 64.0f, m_pGameController},
                    });
}

void LevelManager::InitDoor()
{
    m_pDoor = new Door{Point2f{6941.0f, 64.0f}, m_pGameController};
    m_pDoor->SetActive(false);
    m_pDoor->SetVisible(false);
}

std::vector<GameObject*>& LevelManager::GetColliders()
{
    return m_Colliders;
}

std::vector<GameObject*>& LevelManager::GetLadders()
{
    return m_Ladders;
}

std::vector<GameObject*>& LevelManager::GetTombstones()
{
    return m_Tombstones;
}

std::vector<GameObject*>& LevelManager::GetWaters()
{
    return m_Waters;
}

Level* LevelManager::GetLevel() const
{
    return m_pLevel;
}

GameObject* LevelManager::GetDoor()
{
   return m_pDoor; 
}

Platform* LevelManager::GetPlatform() const
{
    return m_pPlatform;
}

GameObject* LevelManager::GetKillZone() const
{
    return m_pKillZone;
}
