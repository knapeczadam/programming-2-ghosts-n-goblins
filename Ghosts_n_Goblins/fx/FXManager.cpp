#include "pch.h"
#include "FXManager.h"

#include "Fire.h"
#include "ProjectileBlock.h"
#include "ProjectileDeath.h"
#include "Score.h"
#include "characters/IEnemy.h"
#include "collectibles/ICollectible.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/GameController.h"

#include <ranges>

FXManager::FXManager(GameController* pGameController)
    : IManager{pGameController}
{
    pGameController->m_pFXManager = this;
    Initialize();
}

FXManager::~FXManager()
{
    CleanUp();
}

void FXManager::Initialize(bool fromCheckpoint)
{
}

void FXManager::CleanUp()
{
    auto deleteGameObject = [](const GameObject* pGameObject) { delete pGameObject; };
    std::ranges::for_each(m_Effects, deleteGameObject);
}

void FXManager::Draw() const
{
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    static auto isVisible{[](const GameObject* pGameObject) { return pGameObject->IsVisible(); }};
    std::ranges::for_each(m_Effects | std::ranges::views::filter(isVisible), draw);
}

void FXManager::Update(float elapsedSec)
{
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto update{[&](GameObject* pGameObject) { pGameObject->Update(elapsedSec); }};
    std::ranges::for_each(m_Effects | std::ranges::views::filter(isActive), update);
}

void FXManager::UpdateColliders()
{
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto updateCollider{[&](GameObject* pGameObject) { pGameObject->UpdateCollider(); }};
    std::ranges::for_each(m_Effects | std::ranges::views::filter(isActive), updateCollider);
}

void FXManager::LateUpdate(float elapsedSec)
{
    static const auto lateUpdate{[&](GameObject* pGameObject) { pGameObject->LateUpdate(elapsedSec); }};
    std::ranges::for_each(m_Effects, lateUpdate);
}

std::vector<GameObject*>& FXManager::GetEffects()
{
    return m_Effects;
}

void FXManager::PlayEffect(Game::Label label, const Point2f& pos, bool flipped, GameObject* other)
{
    for (GameObject* pEffect : m_Effects)
    {
        if (pEffect->GetLabel() == label and not pEffect->IsActive())
        {
            Point2f newPos{pos};
            if (label != Game::Label::F_FIRE_TORCH)
            {
                newPos.y -= pEffect->GetSprite()->GetScaledClipHeight() / 2.f;
            }
            newPos.x -= pEffect->GetSprite()->GetScaledClipWidth() / 2.f;
            pEffect->SetPosition(newPos);
            pEffect->SetFlipped(flipped);
            pEffect->SetActive(true);
            pEffect->SetVisible(true);
            Score* pScore{dynamic_cast<Score*>(pEffect)};
            if (pScore)
            {
                pEffect->SetVisible(false);
                const IEnemy* pEnemy{dynamic_cast<IEnemy*>(other)};
                const ICollectible* pCollectible{dynamic_cast<ICollectible*>(other)};
                const int score{pEnemy ? pEnemy->GetScore() : pCollectible->GetScore()};
                pScore->SetScore(score);
            }
            return;
        }
    }
    switch (label)
    {
    case Game::Label::F_FIRE_BOSS:
    case Game::Label::F_FIRE_ENEMY:
    case Game::Label::F_FIRE_TORCH:
        m_Effects.push_back(new Fire{label, pos, m_pGameController});
        break;
    case Game::Label::F_PROJECTILE_BLOCK_ENEMY:
    case Game::Label::F_PROJECTILE_BLOCK_BOSS:
        m_Effects.push_back(new ProjectileBlock{label, pos, flipped, m_pGameController});
        break;
    case Game::Label::F_PROJECTILE_DEATH:
        m_Effects.push_back(new ProjectileDeath{pos, flipped, m_pGameController});
        break;
    case Game::Label::F_SCORE:
        const IEnemy* pEnemy{dynamic_cast<IEnemy*>(other)};
        const ICollectible* pCollectible{dynamic_cast<ICollectible*>(other)};
        const int score{pEnemy ? pEnemy->GetScore() : pCollectible->GetScore()};
        m_Effects.push_back(new Score{other->GetColliderCenter(), score, m_pGameController});
        break;
    }
}
