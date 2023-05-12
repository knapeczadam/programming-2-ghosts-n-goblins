#include "pch.h"
#include "EnemyManager.h"

#include "GameController.h"
#include "characters/Crow.h"
#include "characters/FlyingKnight.h"
#include "characters/GreenMonster.h"
#include "characters/Magician.h"
#include "characters/RedArremer.h"
#include "characters/Unicorn.h"
#include "characters/WoodyPig.h"
#include "characters/Zombie.h"
#include "level/FlyingKnightSpawner.h"
#include "level/WoodyPigSpawner.h"
#include "level/ZombieSpawner.h"

#include <ranges>

EnemyManager::EnemyManager(GameController* pGameController)
    : IManager(pGameController)
      , m_Enemies{}
      , m_Throwables{}
      , m_FlyingKnights{}
      , m_WoodyPigs{}
      , m_Zombies{}
      , m_pFlyingKnightSpawner{nullptr}
      , m_pWoodyPigSpawner{nullptr}
      , m_pZombieSpawner{nullptr}
{
    m_pGameController->m_pEnemyManager = this;
    Initialize();
}

EnemyManager::~EnemyManager()
{
    auto deleteGameObject = [](const GameObject* pGameObject) { delete pGameObject; };
    std::ranges::for_each(m_Enemies, deleteGameObject);
    std::ranges::for_each(m_Throwables, deleteGameObject);

    delete m_pFlyingKnightSpawner;
    delete m_pWoodyPigSpawner;
    delete m_pZombieSpawner;
}

void EnemyManager::Initialize()
{
    InitCrows();
    InitFlyingKnights();
    InitGreenMonsters();
    InitMagician();
    InitRedArremer();
    InitUnicorn();
    InitWoodyPigs();
    InitZombies();

    InitSpawners();
}

void EnemyManager::Reset(bool fromCheckpoint)
{
}

void EnemyManager::DrawEnemies() const
{
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    static auto isVisible{[](const GameObject* pGameObject) { return pGameObject->IsVisible(); }};
    std::ranges::for_each(m_Enemies | std::views::filter(isVisible), draw);
}

void EnemyManager::DrawThrowables() const
{
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    static auto isVisible{[](const GameObject* pGameObject) { return pGameObject->IsVisible(); }};
    std::ranges::for_each(m_Throwables | std::views::filter(isVisible), draw);
}

void EnemyManager::Update(float elapsedSec)
{
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto update{[&](GameObject* pGameObject) { pGameObject->Update(elapsedSec); }};
    std::ranges::for_each(m_Enemies | std::views::filter(isActive), update);
    std::ranges::for_each(m_Throwables | std::views::filter(isActive), update);
}

void EnemyManager::LateUpdate(float elapsedSec)
{
    static const auto lateUpdate{[&](GameObject* pGameObject) { pGameObject->LateUpdate(elapsedSec); }};
    std::ranges::for_each(m_Enemies, lateUpdate);
    std::ranges::for_each(m_Throwables, lateUpdate);
}

void EnemyManager::InitCrows()
{
    m_Enemies.insert(m_Enemies.end(), {
                         new Crow{Point2f{1505.0f, 100.0f}, m_pGameController},
                         new Crow{Point2f{2210.0f, 100.0f}, m_pGameController},
                         new Crow{Point2f{2526.0f, 100.0f}, m_pGameController},
                         new Crow{Point2f{3035.0f, 102.0f}, m_pGameController},
                         new Crow{Point2f{1724.0f, 262.0f}, m_pGameController},
                     });
}

void EnemyManager::InitFlyingKnights()
{
    FlyingKnight* pFlyingKnight1{new FlyingKnight{Point2f{500.0f, 100.0f}, m_pGameController}};
    FlyingKnight* pFlyingKnight2{new FlyingKnight{Point2f{500.0f, 100.0f}, m_pGameController}};
    FlyingKnight* pFlyingKnight3{new FlyingKnight{Point2f{500.0f, 100.0f}, m_pGameController}};

    pFlyingKnight1->SetActive(false);
    pFlyingKnight2->SetActive(false);
    pFlyingKnight3->SetActive(false);

    pFlyingKnight1->SetVisible(false);
    pFlyingKnight2->SetVisible(false);
    pFlyingKnight3->SetVisible(false);

    m_Enemies.insert(m_Enemies.end(), {pFlyingKnight1, pFlyingKnight2, pFlyingKnight3,});
    m_FlyingKnights.insert(m_FlyingKnights.end(), {pFlyingKnight1, pFlyingKnight2, pFlyingKnight3});
}

void EnemyManager::InitGreenMonsters()
{
    m_Enemies.insert(m_Enemies.end(), {
                         new GreenMonster{Point2f{4622.0f, 54.0f}, m_pGameController},
                         new GreenMonster{Point2f{6190.0f, 54.0f}, m_pGameController},
                         new GreenMonster{Point2f{1615.0f, 213.0f}, m_pGameController},
                         new GreenMonster{Point2f{2191.0f, 213.0f}, m_pGameController},
                     });
}

void EnemyManager::InitMagician()
{
    Magician* pMagician{new Magician{Point2f{600.0f, 62.0f}, m_pGameController}};
    m_Enemies.push_back(pMagician);
}

void EnemyManager::InitRedArremer()
{
    RedArremer * pRedArremer{new RedArremer{Point2f{2929.0f, 65.0f}, m_pGameController}};
    m_Enemies.push_back(pRedArremer);
}

void EnemyManager::InitUnicorn()
{
    m_Enemies.push_back(new Unicorn{Point2f{6903.0f, 62.0f}, m_pGameController});
}

void EnemyManager::InitWoodyPigs()
{
    WoodyPig* pWoodyPig1{new WoodyPig{Point2f{1000.0f, 200.0f}, m_pGameController}};
    WoodyPig* pWoodyPig2{new WoodyPig{Point2f{1000.0f, 200.0f}, m_pGameController}};
    WoodyPig* pWoodyPig3{new WoodyPig{Point2f{1000.0f, 200.0f}, m_pGameController}};

    pWoodyPig1->SetActive(false);
    pWoodyPig2->SetActive(false);
    pWoodyPig3->SetActive(false);

    pWoodyPig1->SetVisible(false);
    pWoodyPig2->SetVisible(false);
    pWoodyPig3->SetVisible(false);

    m_Enemies.insert(m_Enemies.end(), {pWoodyPig1, pWoodyPig2, pWoodyPig3});
    m_WoodyPigs.insert(m_WoodyPigs.end(), {pWoodyPig1, pWoodyPig2, pWoodyPig3});
}

void EnemyManager::InitZombies()
{
    Zombie* pZombie1{new Zombie{Point2f{1000.0f, 62.0f}, m_pGameController}};
    Zombie* pZombie2{new Zombie{Point2f{1000.0f, 62.0f}, m_pGameController}};
    Zombie* pZombie3{new Zombie{Point2f{1000.0f, 62.0f}, m_pGameController}};

    pZombie1->SetActive(false);
    pZombie2->SetActive(false);
    pZombie3->SetActive(false);

    pZombie1->SetVisible(false);
    pZombie2->SetVisible(false);
    pZombie3->SetVisible(false);

    m_Enemies.insert(m_Enemies.end(), {pZombie1, pZombie2, pZombie3});
    m_Zombies.insert(m_Zombies.end(), {pZombie1, pZombie2, pZombie3});
}

void EnemyManager::InitSpawners()
{
    m_pFlyingKnightSpawner = new FlyingKnightSpawner{
        Rectf{0.0f, 0.0f, 0.0f, m_pGameController->m_ViewPort.height}, m_pGameController
    };
    m_pWoodyPigSpawner = new WoodyPigSpawner{
        Rectf{0.0f, 0.0f, 0.0f, m_pGameController->m_ViewPort.height}, m_pGameController
    };
    m_pZombieSpawner = new ZombieSpawner{
        Rectf{0.0f, 0.0f, 2485.0f, m_pGameController->m_ViewPort.height}, m_pGameController
    };
}

void EnemyManager::SpawnEnemies()
{
    m_pFlyingKnightSpawner->Spawn();
    m_pWoodyPigSpawner->Spawn();
    m_pZombieSpawner->Spawn();
}

std::vector<GameObject*>& EnemyManager::GetEnemies()
{
    return m_Enemies;
}

std::vector<GameObject*>& EnemyManager::GetThrowables()
{
    return m_Throwables;
}

std::vector<GameObject*>& EnemyManager::GetFlyingKnights()
{
    return m_FlyingKnights;
}

std::vector<GameObject*>& EnemyManager::GetWoodyPigs()
{
    return m_WoodyPigs;
}

std::vector<GameObject*>& EnemyManager::GetZombies()
{
    return m_Zombies;
}
