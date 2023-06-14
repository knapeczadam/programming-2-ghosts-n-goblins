#include "pch.h"
#include "PlayerManager.h"

#include "GameController.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "characters/Player.h"

#include <ranges>

PlayerManager::PlayerManager(GameController* pGameController)
    : IManager{pGameController}
    , m_pPlayer{nullptr}
    , m_SpawnPos{164.0f, 64.0f}
    // , m_SpawnPos{3700.0f, 64.0f}
    , m_CheckpointPos{3820.0f, 64.0f}
    , m_Throwables{}
    , m_PrevLives{0}
    , m_PrevScore{0}
    , m_PrevWeapon{Game::Label::T_LANCE}
{
    m_pGameController->m_pPlayerManager = this;
    Initialize();
}

PlayerManager::~PlayerManager()
{
    CleanUp();
}

void PlayerManager::Initialize(bool fromCheckpoint)
{
    if (fromCheckpoint)
    {
        m_pPlayer = new Player{m_SpawnPos, m_pGameController};
        if (m_PrevLives > 0)
        {
            m_pPlayer->SetLives(m_PrevLives);
            m_pPlayer->SetScore(m_PrevScore);
        }
        m_pPlayer->SetWeapon(m_PrevWeapon);
        if (m_pGameController->m_pLevelManager->CheckpointReached())
        {
            m_pPlayer->SetPosition(m_CheckpointPos);
        }
    }
    else
    {
        m_pPlayer = new Player{m_SpawnPos, m_pGameController};
    }
}

void PlayerManager::CleanUp()
{
    static const auto deleteGameObject = [](const GameObject* pGameObject) { delete pGameObject; };
    std::ranges::for_each(m_Throwables, deleteGameObject);
    m_Throwables.clear();
    m_PrevLives = m_pPlayer->GetLives();
    m_PrevScore = m_pPlayer->GetScore();
    m_PrevWeapon = m_pPlayer->GetWeapon();
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

void PlayerManager::Reset(bool fromCheckpoint)
{
    CleanUp();
    Initialize(fromCheckpoint);
}

void PlayerManager::DrawPlayer() const
{
    m_pPlayer->Draw();
}

void PlayerManager::DrawThrowables() const
{
    static const auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    static const auto isVisible{[](const GameObject* pGameObject) { return pGameObject->IsVisible(); }};
    std::ranges::for_each(m_Throwables | std::ranges::views::filter(isVisible), draw);
}

void PlayerManager::Update(float elapsedSec)
{
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto update{[&](GameObject* pGameObject) { pGameObject->Update(elapsedSec); }};
    if (m_pPlayer->IsActive()) m_pPlayer->Update(elapsedSec);
    std::ranges::for_each(m_Throwables | std::ranges::views::filter(isActive), update);
}

void PlayerManager::UpdateColliders()
{
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto updateCollider{[&](GameObject* pGameObject) { pGameObject->UpdateCollider(); }};
    if (m_pPlayer->IsActive()) m_pPlayer->UpdateCollider();
    std::ranges::for_each(m_Throwables | std::ranges::views::filter(isActive), updateCollider);
}

void PlayerManager::LateUpdate(float elapsedSec)
{
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto lateUpdate{[&](GameObject* pGameObject) { pGameObject->LateUpdate(elapsedSec); }};
    std::ranges::for_each(m_Throwables | std::ranges::views::filter(isActive), lateUpdate);
    if (m_pPlayer->IsActive()) m_pPlayer->LateUpdate(elapsedSec);
}
