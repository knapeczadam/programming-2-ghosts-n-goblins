#include "pch.h"
#include "PlayerManager.h"

#include "GameController.h"
#include "GameObject.h"
#include "characters/Player.h"

#include <ranges>

PlayerManager::PlayerManager(GameController* pGameController)
    : IManager{pGameController}
      , m_pPlayer{nullptr}
      , m_Throwables{}
{
    m_pGameController->m_pPlayerManager = this;
    Initialize();
}

PlayerManager::~PlayerManager()
{
    auto deleteGameObject = [](const GameObject* pGameObject) { delete pGameObject; };
    std::ranges::for_each(m_Throwables, deleteGameObject);
    delete m_pPlayer;
}

std::vector<GameObject*>& PlayerManager::GetThrowables()
{
    return m_Throwables;
}

Player* PlayerManager::GetPlayer() const
{
    return m_pPlayer;
}

void PlayerManager::Initialize()
{
    m_pPlayer = new Player{Player::GetSpawnPos(), m_pGameController};
}

void PlayerManager::Reset(bool fromCheckpoint)
{
    m_pPlayer->SetHP(2);
    m_pPlayer->SetActive(true);
    m_pPlayer->SetVisible(true);
    m_pPlayer->SetPosition(Player::GetSpawnPos());
    if (fromCheckpoint)
    {
        if (m_pPlayer->GetLives() == 0)
        {
            m_pPlayer->SetLives(3);
        }
    }
    else
    {
        m_pPlayer->SetLives(3);
    }
}

void PlayerManager::DrawPlayer() const
{
    m_pPlayer->Draw();
}

void PlayerManager::DrawThrowables() const
{
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    static auto isVisible{[](const GameObject* pGameObject) { return pGameObject->IsVisible(); }};
    std::ranges::for_each(m_Throwables | std::ranges::views::filter(isVisible), draw);
}

void PlayerManager::Update(float elapsedSec)
{
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto update{[&](GameObject* pGameObject) { pGameObject->Update(elapsedSec); }};
    if (m_pPlayer->IsActive()) m_pPlayer->Update(elapsedSec);
    std::ranges::for_each(m_Throwables | std::ranges::views::filter(isActive), update);
}

void PlayerManager::UpdateLives()
{
    if (m_pPlayer->GetLives() == 0) return;
    
    if (m_pPlayer->GetHP() == 0)
    {
        m_pPlayer->SetLives(m_pPlayer->GetLives() - 1);
    }
}

void PlayerManager::LateUpdate(float elapsedSec)
{
    static const auto lateUpdate{[&](GameObject* pGameObject) { pGameObject->LateUpdate(elapsedSec); }};
    std::ranges::for_each(m_Throwables, lateUpdate);
    m_pPlayer->LateUpdate(elapsedSec);
}
