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

#include <ranges>

#include "LevelManager.h"
#include "level/colliders/spawners/ZombieSpawner.h"

EnemyManager::EnemyManager(GameController* pGameController)
    : IManager(pGameController)
    , m_Crows{}
    , m_Enemies{}
    , m_GreenMonsters{}
    , m_Throwables{}
    , m_FlyingKnights{}
    , m_WoodyPigs{}
    , m_Zombies{}
{
    m_pGameController->m_pEnemyManager = this;
    Initialize();
}

EnemyManager::~EnemyManager()
{
    CleanUp();
}

void EnemyManager::Initialize(bool fromCheckpoint)
{
    InitCrows();
    InitFlyingKnights();
    InitGreenMonsters();
    InitMagician();
    InitRedArremer();
    InitUnicorn();
    InitWoodyPigs();
    InitZombies();
}

void EnemyManager::CleanUp()
{
    auto deleteGameObject = [](const GameObject* pGameObject) { delete pGameObject; };
    std::ranges::for_each(m_Enemies, deleteGameObject);
    std::ranges::for_each(m_Throwables, deleteGameObject);
    m_Enemies.clear();
    m_Throwables.clear();
    m_FlyingKnights.clear();
    m_WoodyPigs.clear();
    m_Zombies.clear();
}

void EnemyManager::Reset(bool fromCheckpoint)
{
    CleanUp();
    Initialize(fromCheckpoint);
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
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto lateUpdate{[&](GameObject* pGameObject) { pGameObject->LateUpdate(elapsedSec); }};
    std::ranges::for_each(m_Enemies | std::views::filter(isActive), lateUpdate);
    std::ranges::for_each(m_Throwables | std::views::filter(isActive), lateUpdate);
}

void EnemyManager::InitCrows()
{
    GameObject* pCrow1{new Crow{Point2f{1505.0f, 100.0f}, m_pGameController}};
    GameObject* pCrow2{new Crow{Point2f{2210.0f, 100.0f}, m_pGameController}};
    GameObject* pCrow3{new Crow{Point2f{2526.0f, 100.0f}, m_pGameController}};
    GameObject* pCrow4{new Crow{Point2f{3035.0f, 102.0f}, m_pGameController}};
    GameObject* pCrow5{new Crow{Point2f{1724.0f, 262.0f}, m_pGameController}};
    m_Enemies.insert(m_Enemies.end(), {pCrow1, pCrow2, pCrow3, pCrow4, pCrow5});
    m_Crows.insert(m_Crows.end(), {pCrow1, pCrow2, pCrow3, pCrow4, pCrow5});
}

void EnemyManager::InitFlyingKnights()
{
    GameObject* pFlyingKnight1{new FlyingKnight{Point2f{500.0f, 100.0f}, m_pGameController}};
    GameObject* pFlyingKnight2{new FlyingKnight{Point2f{500.0f, 100.0f}, m_pGameController}};
    GameObject* pFlyingKnight3{new FlyingKnight{Point2f{500.0f, 100.0f}, m_pGameController}};

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
    GameObject* pGreenMonster1{new GreenMonster{Point2f{4622.0f, 54.0f}, m_pGameController}};
    GameObject* pGreenMonster2{new GreenMonster{Point2f{6190.0f, 54.0f}, m_pGameController}};
    GameObject* pGreenMonster3{new GreenMonster{Point2f{1615.0f, 213.0f}, m_pGameController}};
    GameObject* pGreenMonster4{new GreenMonster{Point2f{2191.0f, 213.0f}, m_pGameController}};
    m_Enemies.insert(m_Enemies.end(), {pGreenMonster1, pGreenMonster2, pGreenMonster3, pGreenMonster4});
    m_GreenMonsters.insert(m_GreenMonsters.end(), {pGreenMonster1, pGreenMonster2, pGreenMonster3, pGreenMonster4});
}

void EnemyManager::InitMagician()
{
    GameObject* pMagician{new Magician{Point2f{0.0f, 0.0f}, m_pGameController}};
    pMagician->SetActive(false);
    pMagician->SetVisible(false);
    m_Enemies.push_back(pMagician);
    m_pMagician = pMagician;
}

void EnemyManager::InitRedArremer()
{
    GameObject* pRedArremer{new RedArremer{Point2f{2929.0f, 65.0f}, m_pGameController}};
    m_Enemies.push_back(pRedArremer);
}

void EnemyManager::InitUnicorn()
{
    m_Enemies.push_back(new Unicorn{Point2f{6903.0f, LevelManager::GetGroundHeight()}, m_pGameController});
}

void EnemyManager::InitWoodyPigs()
{
    GameObject* pWoodyPig1{new WoodyPig{Point2f{1000.0f, 200.0f}, m_pGameController}};
    GameObject* pWoodyPig2{new WoodyPig{Point2f{1000.0f, 200.0f}, m_pGameController}};
    GameObject* pWoodyPig3{new WoodyPig{Point2f{1000.0f, 200.0f}, m_pGameController}};

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
    GameObject* pZombie1{new Zombie{Point2f{0.0f, 0.0f}, m_pGameController}};
    GameObject* pZombie2{new Zombie{Point2f{0.0f, 0.0f}, m_pGameController}};
    GameObject* pZombie3{new Zombie{Point2f{0.0f, 0.0f}, m_pGameController}};

    pZombie1->SetActive(false);
    pZombie2->SetActive(false);
    pZombie3->SetActive(false);

    pZombie1->SetVisible(false);
    pZombie2->SetVisible(false);
    pZombie3->SetVisible(false);

    m_Enemies.insert(m_Enemies.end(), {pZombie1, pZombie2, pZombie3});
    m_Zombies.insert(m_Zombies.end(), {pZombie1, pZombie2, pZombie3});
}

void EnemyManager::SpawnEnemies()
{
    m_pGameController->m_pLevelManager->GetFlyingKnightSpawner()->Spawn();
    m_pGameController->m_pLevelManager->GetWoodyPigSpawner()->Spawn();
    m_pGameController->m_pLevelManager->GetZombieSpawner()->Spawn();
}

std::vector<GameObject*>& EnemyManager::GetCrows()
{
    return m_Crows;
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

std::vector<GameObject*>& EnemyManager::GetGreenMonsters()
{
    return m_GreenMonsters;
}

std::vector<GameObject*>& EnemyManager::GetWoodyPigs()
{
    return m_WoodyPigs;
}

std::vector<GameObject*>& EnemyManager::GetZombies()
{
    return m_Zombies;
}

GameObject* EnemyManager::GetMagician() const
{
    return m_pMagician;
}
