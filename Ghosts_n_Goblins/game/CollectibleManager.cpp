#include "pch.h"
#include "CollectibleManager.h"

#include "GameController.h"
#include "collectibles/Armor.h"
#include "collectibles/Coin.h"
#include "collectibles/MoneyBag.h"
#include "collectibles/Necklace.h"
#include "collectibles/Pot.h"
#include "collectibles/Yashichi.h"

#include <ranges>

#include "EnemyManager.h"
#include "characters/IPotter.h"
#include "collectibles/Doll.h"
#include "collectibles/Key.h"
#include "collectibles/King.h"
#include "level/spawners/ISpawner.h"
#include "throwables/Dagger.h"
#include "throwables/Lance.h"
#include "throwables/Torch.h"

CollectibleManager::CollectibleManager(GameController* pGameController)
    : IManager{pGameController}
      , m_Collectibles{}
      , m_pPot{nullptr}
      , m_CurrContent{Game::Label::D_DUMMY}
      , m_ContentCount{0}
      , m_WeaponCount{0}
      , m_ContentActive{false}
{
    pGameController->m_pCollectibleManager = this;
    Initialize();
}

CollectibleManager::~CollectibleManager()
{
    CleanUp();
}

void CollectibleManager::Initialize(bool fromCheckpoint)
{
    InitArmor();
    InitDoll();
    InitCoins();
    InitKey();
    InitKing();
    InitMoneyBags();
    InitNecklace();
    InitPot();
    InitYashichi();
    InitWeapons();
}

void CollectibleManager::CleanUp()
{
    auto deleteGameObject = [](const GameObject* pGameObject) { delete pGameObject; };
    std::ranges::for_each(m_Collectibles, deleteGameObject);
    m_Collectibles.clear();
}

void CollectibleManager::UpdatePot()
{
    if (m_pGameController->m_pEnemyManager->GetZombieSpawner()->IsPlayerBetweenBoundaries())
    {
        for (GameObject* pZombie : m_pGameController->m_pEnemyManager->GetZombies())
        {
            AssignPot(pZombie);
        }
    }
    else if (m_pGameController->m_pEnemyManager->GetFlyingKnightSpawner()->IsPlayerBetweenBoundaries())
    {
        for (GameObject* pFlyingKnight : m_pGameController->m_pEnemyManager->GetFlyingKnights())
        {
            AssignPot(pFlyingKnight);
        }
    }
    else if (m_pGameController->m_pEnemyManager->GetWoodyPigSpawner()->IsPlayerBetweenBoundaries())
    {
        for (GameObject* pWoodyPog : m_pGameController->m_pEnemyManager->GetWoodyPigs())
        {
            AssignPot(pWoodyPog);
        }
    }
}

void CollectibleManager::Draw() const
{
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    static auto isVisible{[](const GameObject* pGameObject) { return pGameObject->IsVisible(); }};
    std::ranges::for_each(m_Collectibles | std::views::filter(isVisible), draw);
}

void CollectibleManager::Update(float elapsedSec)
{
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto update{[&](GameObject* pGameObject) { pGameObject->Update(elapsedSec); }};
    std::ranges::for_each(m_Collectibles | std::views::filter(isActive), update);
    UpdatePot();
}

void CollectibleManager::Reset(bool fromCheckpoint)
{
    if ( not fromCheckpoint)
    {
        m_ContentCount = 0;
        m_WeaponCount = 0;
    }
    m_ContentActive = false;
}

void CollectibleManager::LateUpdate(float elapsedSec)
{
    static const auto lateUpdate{[&](GameObject* pGameObject) { pGameObject->LateUpdate(elapsedSec); }};
    std::ranges::for_each(m_Collectibles, lateUpdate);
}

void CollectibleManager::InitArmor()
{
    GameObject* pArmor = new Armor{Point2f{0.0f, 0.0f}, m_pGameController};
    pArmor->SetActive(false);
    pArmor->SetVisible(false);
    m_Collectibles.push_back(pArmor);
}

void CollectibleManager::InitCoins()
{
    m_Collectibles.insert(m_Collectibles.end(), {
                              new Coin{Point2f{720.0f, 62.0f}, m_pGameController},
                              new Coin{Point2f{6190.0f, 72.0f}, m_pGameController},
                              new Coin{Point2f{1232.0f, 223.0f}, m_pGameController},
                              new Coin{Point2f{1616.0f, 223.0f}, m_pGameController},
                              new Coin{Point2f{2158.0f, 223.0f}, m_pGameController}
                          });
}

void CollectibleManager::InitKey()
{
    GameObject* pKey = new Key{Point2f{6716.0f, 300.0f}, m_pGameController};
    pKey->SetActive(false);
    pKey->SetVisible(false);
    m_Collectibles.push_back(pKey);
}

void CollectibleManager::InitMoneyBags()
{
    m_Collectibles.insert(m_Collectibles.end(), {
                              new MoneyBag{Point2f{2799.0f, 63.0f}, m_pGameController},
                              new MoneyBag{Point2f{4814.0f, 63.0f}, m_pGameController}
                          });
}

void CollectibleManager::InitNecklace()
{
    GameObject* pNecklace = new Necklace{Point2f{0.0f, 0.0f}, m_pGameController};
    pNecklace->SetActive(false);
    pNecklace->SetVisible(false);
    m_Collectibles.push_back(pNecklace);
}

void CollectibleManager::InitDoll()
{
    GameObject* pDoll = new Doll{Point2f{0.0f, 0.0f}, m_pGameController};
    pDoll->SetActive(false);
    pDoll->SetVisible(false);
    m_Collectibles.push_back(pDoll);
}

void CollectibleManager::InitKing()
{
    GameObject* pKing = new King{Point2f{0.0f, 0.0f}, m_pGameController};
    pKing->SetActive(false);
    pKing->SetVisible(false);
    m_Collectibles.push_back(pKing);
}

void CollectibleManager::InitPot()
{
    GameObject* pPot = new Pot{Point2f{0.0f, 0.0f}, m_pGameController};
    pPot->SetActive(false);
    pPot->SetVisible(false);
    m_pPot = pPot;
    m_Collectibles.push_back(pPot);
}

void CollectibleManager::InitYashichi()
{
    GameObject* pYashichi = new Yashichi{Point2f{0.0f, 0.0f}, m_pGameController};
    pYashichi->SetActive(false);
    pYashichi->SetVisible(false);
    m_Collectibles.push_back(pYashichi);
}

void CollectibleManager::InitWeapons()
{
    GameObject* pDagger = new Dagger{Point2f{0.0f, 0.0f}, false, true, m_pGameController};
    pDagger->SetActive(false);
    pDagger->SetVisible(false);
    m_Collectibles.push_back(pDagger);

    GameObject* pLance = new Lance{Point2f{0.0f, 0.0f}, false, true, m_pGameController};
    pLance->SetActive(false);
    pLance->SetVisible(false);
    m_Collectibles.push_back(pLance);

    GameObject* pTorch = new Torch{Point2f{0.0f, 0.0f}, false, true, m_pGameController};
    pTorch->SetActive(false);
    pTorch->SetVisible(false);
    m_Collectibles.push_back(pTorch);
}

void CollectibleManager::AssignPot(GameObject* pEnemy)
{
    if (IsContentActive()) return;
   StartTimer(8.0f);
    if (IsTimerFinished())
    {
        IPotter* pPotter = dynamic_cast<IPotter*>(pEnemy);
        if (pPotter)
        {
            pPotter->SetPot(m_pPot);
            Pot* pPot = static_cast<Pot*>(m_pPot);
            pPot->SetContent(GetNextContent());
            m_ContentActive = true;
        }
    }
}

Game::Label CollectibleManager::GetNextContent()
{
    switch (m_ContentCount++ % 4)
    {
    case 0:
        if (m_ContentCount % 17 == 0)
        {
            m_CurrContent = Game::Label::O_KING;
        }
        else
        {
            m_CurrContent = Game::Label::O_DOLL;
        }
        break;
    case 1:
        switch (m_WeaponCount++ % 3)
        {
        case 0:
            m_CurrContent = Game::Label::O_TORCH;
            break;
        case 1:
            m_CurrContent = Game::Label::T_DAGGER;
            break;
        case 2:
            m_CurrContent = Game::Label::T_LANCE;
            break;
        }
        break;
    case 2:
        m_CurrContent = Game::Label::O_DOLL;
        break;
    case 3:
        m_CurrContent = Game::Label::O_NECKLACE;
        break;
    }
    return m_CurrContent;
}

bool CollectibleManager::IsContentActive()
{
    return m_ContentActive;
}

void CollectibleManager::ActivateContent()
{
    m_ContentActive = true;
}

void CollectibleManager::DeactivateContent()
{
    m_ContentActive = false;
}

std::vector<GameObject*>& CollectibleManager::GetCollectibles()
{
    return m_Collectibles;
}
