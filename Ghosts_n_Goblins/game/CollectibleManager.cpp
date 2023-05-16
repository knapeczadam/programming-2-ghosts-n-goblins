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

#include "collectibles/Key.h"

Game::Label CollectibleManager::s_CurrContent{Game::Label::D_DUMMY};
int CollectibleManager::s_ContentCount{0};
int CollectibleManager::s_WeaponCount{0};
bool CollectibleManager::s_ContentActive{false};
int CollectibleManager::s_ContentId{0};

CollectibleManager::CollectibleManager(GameController* pGameController)
    : IManager{pGameController}
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
    InitCoins();
    InitKey();
    InitMoneyBags();
    InitNecklace();
    InitPot();
    InitYashichi();
}

void CollectibleManager::CleanUp()
{
    auto deleteGameObject = [](const GameObject* pGameObject) { delete pGameObject; };
    std::ranges::for_each(m_Collectibles, deleteGameObject);
    m_Collectibles.clear();
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

void CollectibleManager::InitPot()
{
    GameObject* pPot = new Pot{Point2f{0.0f, 0.0f}, m_pGameController};
    pPot->SetActive(false);
    pPot->SetVisible(false);
    m_Collectibles.push_back(pPot);
}

void CollectibleManager::InitYashichi()
{
    GameObject* pYashichi = new Yashichi{Point2f{0.0f, 0.0f}, m_pGameController};
    pYashichi->SetActive(false);
    pYashichi->SetVisible(false);
    m_Collectibles.push_back(pYashichi);
}

Game::Label CollectibleManager::GetNextContent()
{
    switch (s_ContentCount++ % 4)
    {
    case 0:
        if (s_ContentCount % 16 == 0)
        {
            s_CurrContent = Game::Label::O_KING;
        }
        else
        {
            s_CurrContent = Game::Label::O_DOLL;
        }
        break;
    case 1:
        switch (s_WeaponCount++ % 3)
        {
        case 0:
            s_CurrContent = Game::Label::T_TORCH;
            break;
        case 1:
            s_CurrContent = Game::Label::T_DAGGER;
            break;
        case 2:
            s_CurrContent = Game::Label::T_LANCE;
            break;
        }
        break;
    case 2:
        s_CurrContent = Game::Label::O_DOLL;
        break;
    case 3:
        s_CurrContent = Game::Label::O_NECKLACE;
        break;
    }
    return s_CurrContent;
}

bool CollectibleManager::IsContentActive()
{
    return s_ContentActive;
}

void CollectibleManager::ActivateContent()
{
    s_ContentActive = true;
}

void CollectibleManager::DeactivateContent()
{
    s_ContentActive = false;
}

void CollectibleManager::SetContentId(int id)
{
    s_ContentId = id;
}

int CollectibleManager::GetContentId()
{
    return s_ContentId;
}

std::vector<GameObject*>& CollectibleManager::GetCollectibles()
{
    return m_Collectibles;
}
