#include "pch.h"
#include "LevelManager.h"

#include "GameController.h"
#include "Texture.h"
#include "engine/TextureManager.h"
#include "level/ArmorCollisionBox.h"
#include "level/KillZone.h"
#include "level/Ladder.h"
#include "level/Level.h"
#include "level/Platform.h"
#include "level/Tombstone.h"
#include "level/Water.h"
#include "level/YashichiCollisionBox.h"

#include <ranges>

LevelManager::LevelManager(GameController* pGameController)
    : IManager{pGameController}
      , m_CollisionBoxes{}
      , m_Ladders{}
      , m_Tombstones{}
      , m_Waters{}
      , m_pForeground{nullptr}
      , m_pKillZone{nullptr}
      , m_pLevel{nullptr}
      , m_pPlatform{nullptr}
{
    m_pGameController->m_pLevelManager = this;
    Initialize();
}

LevelManager::~LevelManager()
{
    auto deleteGameObject = [](const GameObject* pGameObject) { delete pGameObject; };
    std::ranges::for_each(m_CollisionBoxes, deleteGameObject);
    std::ranges::for_each(m_Ladders, deleteGameObject);
    std::ranges::for_each(m_Tombstones, deleteGameObject);
    std::ranges::for_each(m_Waters, deleteGameObject);

    delete m_pForeground;
    delete m_pKillZone;
    delete m_pLevel;
    delete m_pPlatform;
}

void LevelManager::Initialize()
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
    InitCollisionBoxes();
}

void LevelManager::Reset()
{
}

void LevelManager::DrawCollisionBoxes() const
{
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    std::ranges::for_each(m_CollisionBoxes, draw);
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

void LevelManager::Update(float elapsedSec)
{
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto update{[&](GameObject* pGameObject) { pGameObject->Update(elapsedSec); }};
    m_pLevel->Update(elapsedSec);
    m_pPlatform->Update(elapsedSec);
    std::ranges::for_each(m_CollisionBoxes | std::views::filter(isActive), update);
    std::ranges::for_each(m_Ladders | std::views::filter(isActive), update);
    std::ranges::for_each(m_Tombstones | std::views::filter(isActive), update);
    std::ranges::for_each(m_Waters | std::views::filter(isActive), update);
    
}

void LevelManager::LateUpdate(float elapsedSec)
{
    static const auto lateUpdate{[&](GameObject* pGameObject) { pGameObject->LateUpdate(elapsedSec); }};
    std::ranges::for_each(m_Waters, lateUpdate);
}

void LevelManager::InitCollisionBoxes()
{
    m_CollisionBoxes.insert(m_CollisionBoxes.end(), {
                                new ArmorCollisionBox{Rectf{2868.0f, 140.0f, 30.0f, 30.0f}, m_pGameController},
                                new YashichiCollisionBox{Rectf{5924.0f, 140.0f, 24.0f, 24.0f}, m_pGameController},
                            });
}

void LevelManager::InitLadders()
{
    m_Ladders.insert(m_Ladders.end(), {
                         new Ladder{Rectf{1424.0f, 62.0f, 32.0f, 158.0f}},
                         new Ladder{Rectf{1808.0f, 62.0f, 32.0f, 158.0f}},
                         new Ladder{Rectf{2128.0f, 62.0f, 32.0f, 158.0f}},
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

std::vector<GameObject*>& LevelManager::GetCollisionBoxes()
{
    return m_CollisionBoxes;
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

Platform* LevelManager::GetPlatform() const
{
    return m_pPlatform;
}

GameObject* LevelManager::GetKillZone() const
{
    return m_pKillZone;
}
